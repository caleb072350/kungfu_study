/**
 * Page Header
 * Provide necessary information for this page file.
*/

#ifndef YIJINJING_PAGEHEADER_H
#define YIJINJING_PAGEHEADER_H

#include "YJJ_DECLARE.h"
#include "constants.h"

YJJ_NAMESPACE_START

/** reserve space for page header (long) */
#define PAGE_HEADER_RESERVE 10
////////////////////////////////////////////////////
/// (byte) JournalPageStatus
////////////////////////////////////////////////////
#define JOURNAL_PAGE_STATUS_RAW    0
#define JOURNAL_PAGE_STATUS_INITED 1

struct PageHeader
{
    /** JournalPageStatus */
    byte status;
    /** journal name */
    char journal_name[JOURNAL_SHORT_NAME_MAX_LENGTH];
    /** number of this page in journal */
    short page_num;
    /** nano time of when the page started */
    long start_nano;
    /** nano time of when the page closed */
    long close_nano;
    /** how many frame in this page (only filled when closed) */
    int frame_num;
    /** pos of last frame */
    int last_pos;
    /** version of frame header (using reserve)*/
    short frame_version;
    /** reserve space */
    short reserve_short[3];
    long reserve_long[PAGE_HEADER_RESERVE - 1];
} __attribute__((packed));

enum PageStatus
{
    PAGE_RAW = 0,
    PAGE_INITED = 1,
};

YJJ_NAMESPACE_END

#endif