/**
 * Page Utility functions
 * for memory access, yjj-format file name, page number, etc.
*/


#ifndef YIJINJING_PAGEUTIL_H
#define YIJINJING_PAGEUTIL_H

#include "YJJ_DECLARE.h"

YJJ_NAMESPACE_START

class PageHeader;

/**
 * PageUtil is more likely a namespace for utility functions
 * more details are provided for each function
 * all functions are open for usage
*/
class PageUtil
{
public:
    // memory access
    /** direct memory manipulation without service
     *  load page buffer, return address of the file-mapped memory
     *  whether to write has to be specified in "isWriting"
     *  if quickMode == true, no locking; if quickMode == false, mlock
     *  the memory for performance, the address of memory is returned
    */
   static void* LoadPageBuffer(const string& path, int size, bool isWriting, bool quickMode);

   /** direct memory manipulation without service
    *  release page buffer, buffer and size needs to be specified.
    *  if quickMode == true, no unlocking; if quickMode == false, munlock the memory.
   */
   static void ReleasePageBuffer(void* buffer, int size, bool quickMode);

   // name / pattern
   /** generate proper yjj file name by necessary information */
   static string GenPageFileName(const string& jname, short pageNum);

   /** generate proper yjj page full path by necessary information */
   static string GenPageFullPath(const string& dir, const string& jname, short pageNum);

   /** get the proper yjj file name pattern */
   static string GetPageFileNamePattern(const string& jname);

   // page number

   /** extract page number from file name */
   static short ExtractPageNum(const string& fileName, const string& jname);

   /** select page number from existing pages in directory which contains the nano time */
   static short GetPageNumWithTime(const string& dir, const string& jname, long time);
   
   /** get existing page numbers in directory with jname. */
   static vector<short> GetPageNums(const string& dir, const string& jname);

   // header
   /** get header from necessary information */
   static PageHeader GetPageHeader(const string& dir, const string& jname, short pageNum);

   // file
   static bool FileExists(const string& pathname);
};

YJJ_NAMESPACE_END

#endif