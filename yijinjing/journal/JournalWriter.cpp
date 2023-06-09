/** Journal Writer
 * enable user to write in journal.
 * one journal writer can only write one journal,
 * and meanwhile this journal cannot be linked by other writer.
*/

#include "JournalWriter.h"
#include "Journal.h"
#include "PageProvider.h"
#include "Timer.h"
#include "longfist/sys_messages.h"
#include <mutex> // used by JournalSafeWriter

USING_YJJ_NAMESPACE

const string JournalWriter::PREFIX = "writer";

void JournalWriter::init(const string& dir, const string& jname)
{
    addJournal(dir, jname);
    journal = journals[0];
    seekEnd();
}

short JournalWriter::getPageNum() const
{
    return journal->getCurPageNum();
}

long JournalWriter::writeStr(const string& str)
{
    return write_frame(str.c_str(), str.length() + 1, 0, MSG_TYPE_PYTHON_OBJ, 1, -1);
}

long JournalWriter::write_frame_full(const void* data, FH_TYPE_LENGTH length, FH_TYPE_SOURCE source,
                        FH_TYPE_MSG_TP msgType, FH_TYPE_LASTFG lastFlag, FH_TYPE_REQ_ID requestId,
                        FH_TYPE_NANOTM extraNano, FH_TYPE_ERR_ID errorId, const char* errorMsg)
{
    void* buffer = journal->locateFrame();
    Frame frame(buffer);
    frame.setSource(source);
    frame.setMsgType(msgType);
    frame.setLastFlag(lastFlag);
    frame.setRequestId(requestId);
    frame.setErrorData(errorId, errorMsg, data, length);
    frame.setExtraNano(extraNano);
    long nano = getNanoTime();
    frame.setNano(nano);
    frame.setStatusWritten();
    journal->passFrame();
    return nano;
}

JournalWriterPtr JournalWriter::create(const string& dir, const string& jname, const string& writerName)
{
    PageProviderPtr provider = PageProviderPtr(new LocalPageProvider(true));
    return JournalWriter::create(dir, jname, provider);
}

JournalWriterPtr JournalWriter::create(const string& dir, const string& jname, PageProviderPtr provider)
{
    JournalWriterPtr jwp = JournalWriterPtr(new JournalWriter(provider));
    jwp->init(dir, jname);
    return jwp;
}

JournalWriterPtr JournalWriter::create(const string& dir, const string& jname)
{
    return JournalWriter::create(dir, jname, getDefaultName(JournalWriter::PREFIX));
}

void JournalWriter::seekEnd()
{
    journal->seekTime(TIME_TO_LAST);
    journal->locateFrame();
}

std::mutex safe_writer_mtx;

long JournalSafeWriter::write_frame_full(const void* data, FH_TYPE_LENGTH length, FH_TYPE_SOURCE source, FH_TYPE_MSG_TP msgType,
                                FH_TYPE_LASTFG lastFlag, FH_TYPE_REQ_ID requestId, FH_TYPE_NANOTM extraNano,
                                FH_TYPE_ERR_ID errorId, const char* errorMsg)
{
    std::lock_guard<std::mutex> lck(safe_writer_mtx);
    return this->JournalWriter::write_frame_full(data, length, source, msgType, lastFlag, requestId, extraNano, errorId, errorMsg);
}

JournalWriterPtr JournalSafeWriter::create(const string& dir, const string& jname, const string& writerName)
{
    PageProviderPtr provider = PageProviderPtr(new ClientPageProvider(writerName, true));
    JournalWriterPtr jwp = JournalWriterPtr(new JournalSafeWriter(provider));
    jwp->init(dir, jname);
    return jwp;
}