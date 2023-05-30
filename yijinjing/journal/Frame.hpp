/**
 * Frame
 * basic memory uint in  yjj
*/

#ifndef YIJINJING_FRAME_HPP
#define YIJINJING_FRAME_HPP

#include "YJJ_DECLARE.h"
#include "FrameHeader.h"
#include <string.h>   // memcpy

#ifdef RFAME_AUTO_SET_HASHCODE
#include "Hash.hpp"
#endif 

YJJ_NAMESPACE_START

/**
 * Basic memory unit,
 * holds header / data / errorMsg (if needs)
*/
class Frame
{
private:
    /** address  with type,
     * will keep moving forward until change page */
    FrameHeader *frame;
public:
    /** default constructor */
    Frame(void*);
    /** setup basic frame address */
    void set_address(void*);
    /** get current address */
    void* get_address() const;

    // get fields of header from frame
    FH_TYPE_STATUS getStatus() const;
    FH_TYPE_SOURCE getSource() const;
    FH_TYPE_NANOTM getNano() const;
    FH_TYPE_LENGTH getFrameLength() const;
    FH_TYPE_LENGTH getHeaderLength() const;
    FH_TYPE_LENGTH getDataLength() const;
    FH_TYPE_HASHNM getHashCode() const;
    FH_TYPE_MSG_TP getMsgType() const;
    FH_TYPE_LASTFG getLastFlag() const;
    FH_TYPE_REQ_ID getRequestId() const;
    FH_TYPE_NANOTM getExtraNano() const;
    FH_TYPE_ERR_ID getErrorId() const;
    /** return null if errorId == 0 */
    char* getErrorMsg() const;
    /** get address of data field */
    void* getData() const;
    /** parse data content as string with char */
    string getStr() const;
    /** utilized in python, get data address as uintptr */
    uintptr_t getPyData() const;
    /** utilized in python, return empty string if errorID == 0 */
    string getPyErrorMsg() const;

    // set fields of header 
    void setSource(FH_TYPE_SOURCE);
    void setNano(FH_TYPE_NANOTM);
    void setExtraNano(FH_TYPE_NANOTM);
    void setMsgType(FH_TYPE_MSG_TP);
    void setLastFlag(FH_TYPE_LASTFG);
    void setRequestId(FH_TYPE_REQ_ID);
    /** set error msg with its length and errorid */
    void setErrorData(FH_TYPE_ERR_ID, const char* errorMsg, const void* data, size_t datalen);
    /** set data with length */
    void setData(const void*, size_t);
    /** mark status as written */
    void setStatusWritten();
    /** mark status as page closed */
    void setStatusPageClosed();
    /** move the frame forward by length */
    FH_TYPE_LENGTH next();

private:
    /** return address of next frame header */
    FrameHeader* getNextEntry() const;
    /** set status, internally used */
    void setStatus(FH_TYPE_STATUS);
    /** set hash code, internally used */
    void setHashCode(FH_TYPE_HASHNM);
    /** set length, internally used */
    void setFrameLength(FH_TYPE_LENGTH);

};

DECLARE_PTR(Frame);

inline Frame::Frame(void* fm)
{
    set_address(fm);
}

inline void Frame::set_address(void* fm) {
    frame = (FrameHeader*)fm;
}

inline void* Frame::get_address() const {
    return frame;
}

inline FH_TYPE_LENGTH Frame::getHeaderLength() const
{
    if (getErrorId() == 0)
        return BASIC_FRAME_HEADER_LENGTH;
    else
        return ERROR_FRAME_HEADER_LENGTH;
}

inline FH_TYPE_STATUS Frame::getStatus() const
{
    return frame->status;
}

inline FH_TYPE_SOURCE Frame::getSource() const
{
    return frame->source;
}

inline FH_TYPE_NANOTM Frame::getNano() const
{
    return frame->nano;
}

inline FH_TYPE_LENGTH Frame::getFrameLength() const
{
    return frame->length;
}

inline FH_TYPE_HASHNM Frame::getHashCode() const
{
    return frame->hash;
}

inline FH_TYPE_MSG_TP Frame::getMsgType() const
{
    return frame->msg_type;
}

inline FH_TYPE_LASTFG Frame::getLastFlag() const
{
    return frame->last_flag;
}

inline FH_TYPE_REQ_ID Frame::getRequestId() const
{
    return frame->req_id;
}

inline FH_TYPE_NANOTM Frame::getExtraNano() const
{
    return frame->extra_nano;
}

inline FH_TYPE_ERR_ID Frame::getErrorId() const
{
    return frame->err_id;
}

inline char* Frame::getErrorMsg() const
{
    if (getErrorId() == 0)
        return NULL;
    else
        return (char*)ADDRESS_ADD(frame, BASIC_FRAME_HEADER_LENGTH);
}

inline FH_TYPE_LENGTH Frame::getDataLength() const
{
    return getFrameLength() - getHeaderLength();
}

inline void* Frame::getData() const
{
    return ADDRESS_ADD(frame, getHeaderLength());
}

inline string Frame::getStr() const
{
    return string((char*)getData());
}

inline uintptr_t Frame::getPyData() const
{
    return (uintptr_t)getData();
}

inline string Frame::getPyErrorMsg() const
{
    return string(getErrorMsg());
}

inline void Frame::setStatus(FH_TYPE_STATUS status)
{
    frame->status = status;
}

inline void Frame::setSource(FH_TYPE_SOURCE source)
{
    frame->source = source;
}

inline void Frame::setNano(FH_TYPE_NANOTM nano)
{
    frame->nano = nano;
}

inline void Frame::setFrameLength(FH_TYPE_LENGTH length)
{
    frame->length = length;
}

inline void Frame::setHashCode(FH_TYPE_HASHNM hash)
{
    frame->hash = hash;
}

inline void Frame::setMsgType(FH_TYPE_MSG_TP msg_type)
{
    frame->msg_type = msg_type;
}

inline void Frame::setLastFlag(FH_TYPE_LASTFG last_flag)
{
    frame->last_flag = last_flag;
}

inline void Frame::setRequestId(FH_TYPE_REQ_ID req_id)
{
    frame->req_id = req_id;
}

inline void Frame::setExtraNano(FH_TYPE_NANOTM extra_nano)
{
    frame->extra_nano = extra_nano;
}

inline void Frame::setErrorData(FH_TYPE_ERR_ID err_id, const char* errorMsg, const void* data, size_t datalen)
{
    if (err_id == 0) {
        setData(data, datalen);
    } else {
        frame->err_id = err_id;
        char* errorMsgStartAddr = (char*)ADDRESS_ADD(frame, BASIC_FRAME_HEADER_LENGTH);
        strncpy(errorMsgStartAddr, errorMsg, ERROR_MSG_MAX_LENGTH - 1);
        errorMsgStartAddr[ERROR_MSG_MAX_LENGTH - 1] = '\0';
        memcpy(ADDRESS_ADD(frame, ERROR_FRAME_HEADER_LENGTH), data, datalen);
        setFrameLength(ERROR_FRAME_HEADER_LENGTH + datalen);
    }
}

inline void Frame::setData(const void* data, size_t datalen)
{
    frame->err_id = 0;
    memcpy(ADDRESS_ADD(frame, BASIC_FRAME_HEADER_LENGTH), data, datalen);
    setFrameLength(BASIC_FRAME_HEADER_LENGTH + datalen);
}

inline void Frame::setStatusWritten()
{
    /** just make sure next frame won't be wrongly read */
    getNextEntry()->status = JOURNAL_FRAME_STATUS_RAW;
    setStatus(JOURNAL_FRAME_STATUS_WRITTEN);
}

inline void Frame::setStatusPageClosed()
{
    frame->status = JOURNAL_FRAME_STATUS_PAGE_END;
}

inline FH_TYPE_LENGTH Frame::next()
{
    FH_TYPE_LENGTH len = getFrameLength();
    frame = getNextEntry();
    return len;
}

inline FrameHeader* Frame::getNextEntry() const
{
    return (FrameHeader*)ADDRESS_ADD(frame, getFrameLength());
}

YJJ_NAMESPACE_END
#endif // YIJINJING_FRAME_HPP