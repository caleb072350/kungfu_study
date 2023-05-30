/**
 * IPageProvider.
 * Provide page, mainly utilized by journal
*/

#ifndef YIJINJING_IPAGEPROVIDER_H
#define YIJINJING_IPAGEPROVIDER_H

#include "YJJ_DECLARE.h"

YJJ_NAMESPACE_START

FORWARD_DECLARE_PTR(Page)

// abstract interface class.
class IPageProvider
{
public:
    /** return wrapped Page via directory / journal short name / serviceIdx assigned / page number */
    virtual PagePtr getPage(const string& dir, const string& jname, int serviceIdx, short pageNum) = 0;
    /** release page after using */
    virtual void releasePage(void* buffer, int size, int serviceIdx) = 0;
    /** return true if this is for writing */
    virtual bool isWriter() const = 0;
};

DECLARE_PTR(IPageProvider)

YJJ_NAMESPACE_END

#endif