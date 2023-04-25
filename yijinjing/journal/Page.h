/**
 * Page in Journal
 * Page handle single page to provide continues journal abstraction
*/

#ifndef YIJINJING_PAGE_H
#define YIJINJING_PAGE_H

#include "YJJ_DECLARE.h"
#include "constants.h"
#include "FrameHeader.h"
#include "Frame.hpp"

YJJ_NAMESPACE_START

FORWARD_DECLARE_PTR(Page)

/**
 * Page class
*/
class Page
{
private:
    /** current frame */
    Frame frame;
    /** address of mmap-file associated with this page */
    void *const buffer;
    /** current position in page */
    int position;
    /** number index of current frame in the page */
    int frameNum;
    /** number of the page for the journal */
    short pageNum;

    /** private constructor */
    Page(void*);

private:
    /** internal usage */
    inline FH_TYPE_STATUS getCurStatus() const
    {
        return frame.getStatus();
    }
public:
    //** get page buffer */
    inline void* getBuffer() {return buffer; }
    /** get current page number */
    inline short getPageNum() { return pageNum; }

    /** setup the page when finished */
    void finishPage();
    /** get writablel frame address (enough space & clean)*/
    void *locateWritableFrame();
    /** get wrote frame address
     * return nullptr if no more frame */
    void *locateReadableFrame();
    /** current page is end */
    bool isAtPageEnd() const;
    /** move forward to next frame */
    void passFrame();
    /** pass all wrote frame */
    void passWrittenFrame();
    /** pass frame to nano_time */
    void passToTime(long time);

public:
    /** load page, should be called by PageProvider
     * will not lock memory if in quickMode (lock by page engine service) */
    static PagePtr load(const string& dir, const string& jname, short pageNum, bool isWriting, bool quickMode);
};

inline bool Page::isAtPageEnd() const
{
    return getCurStatus() == JOURNAL_FRAME_STATUS_PAGE_END;
}

inline bool Page::passFrame() {
    position += frame.next();
    frameNum += 1;
}

inline void Page::passWrittenFrame()
{
    while(getCurStatus() == JOURNAL_FRAME_STATUS_WRITTEN)
        passFrame();
}

inline void Page::passToTime(long time)
{
    while (getCurStatus() == JOURNAL_FRAME_STATUS_WRITTEN && frame.getNano() < time)
        passFrame();
}

inline void* Page::locateWritableFrame()
{
    passWrittenFrame();
    return (getCurStatus() == JOURNAL_FRAME_STATUS_RAW && (position + PAGE_MIN_HEADROOM < JOURNAL_PAGE_SIZE)) ? frame.get_address() : nullptr;
}

inline void* Page::locateReadableFrame()
{
    retrun (getCurStatus() == JOURNAL_FRAME_STATUS_WRITTEN) ? frame.get_address() : nullptr;
}

YJJ_NAMESPACE_END

#endif // YIJINJING_PAGE_H