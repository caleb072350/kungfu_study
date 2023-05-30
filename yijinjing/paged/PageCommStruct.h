/**
 * Struct for page engine page communication.
*/

#ifndef YIJINJING_PAGECOMMSTRUCT_H
#define YIJINJING_PAGECOMMSTRUCT_H

#include "constants.h"
#include "longfist/sys_messages.h"
#include <string.h>


YJJ_NAMESPACE_START

/**
* PROCESS:
* 
*      * default:                            -- PAGE_COMM RAW
*      
*      user: socket request
*      server: allocate idx                  -> PAGE_COMM_ALLOCATED
*      user:  setup folder / shortName       -> PAGE_HOLDING
*      
*      user:  fill in page_num               -> PAGE_REQUESTING
*      server: find requesting, allocate
*              finish allocating             -> PAGE_ALLOCATED(success)
*                                            -> PAGE_NON_EXIST (reader wants a not existing page)
*                                            -> PAGE_MEM_OVERFLOW (current locking memory overflows)
*/
//////////////////////////////////////////////////
/// (byte) PagedCommTypeConstants
//////////////////////////////////////////////////
// status in process 0 ~ 9
#define PAGED_COMM_RAW            0     /**< this msg block is not allocated (default) */
#define PAGED_COMM_OCCUPIED        1     /**< comm msg idx occupied (by server) */
#define PAGED_COMM_HOLDING         2     /**< folder / name ready (by client) */
#define PAGED_COMM_REQUESTING      3     /**< page number specified (by client) */
#define PAGED_COMM_ALLOCATED       4     /**< finish allocated, user may getPage (by server) */
// failures 10 ~ 19
struct PageCommMsg
{
    /** PageCommTypeConstants (by both server and client) */
    byte status;
    /** journal folder (by client) */
    char folder[JOURNAL_FOLDER_MAX_LENGTH];
    /** journal name (by client) */
    char name[JOURNAL_SHORT_NAME_MAX_LENGTH];
    /** return true if the client is writer (by client) */
    bool is_writer;
    /** page number to request (by client) )*/
    short page_num;
    /** page number requested (by server) */
    short last_page_num;

    // operator for map key
    bool const operator == (const PageCommMsg& p) const
    {
        return page_num == p.page_num && strcmp(folder, p.folder) == 0 && strcmp(name, p.name) == 0;
    }

    bool const operator < (const PageCommMsg& p) const
    {
        return (strcmp(folder, p.folder) != 0) ? strcmp(folder, p.folder) < 0 : 
                strcmp(name, p.name) != 0 ? strcmp(name, p.name) < 0 : page_num < p.page_num;
    }
} __attribute__((packed));

/** max number of communication users in the same time */
#define MAX_COMM_USER_NUMBER 1000
/** REQUEST_ID_RANGE * MAX_COMM_USER_NUMBER < 2147483647(max num of int) */
#define REQUEST_ID_RANGE 1000000
/** based on the max number, the comm file size is determined */
const int COMM_SIZE = MAX_COMM_USER_NUMBER * sizeof(PageCommMsg) + 1024;
/** fast type convert */
#define GET_COMM_MSG(buffer, idx) ((PageCommMsg*)(ADDRESS_ADD(buffer, idx * sizeof(PageCommMsg))))

YJJ_NAMESPACE_END

#endif // YIJINJING_PAGECOMMSTRUCT_H