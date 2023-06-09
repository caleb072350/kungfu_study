#include "Page.h"
#include "PageHeader.h"
#include "PageUtil.h"
#include "Timer.h"
#include <sstream>

USING_YJJ_NAMESPACE 

#define PAGE_INIT_POSITION sizeof(PageHeader)

Page::Page(void* buffer) : buffer(buffer), frame(ADDRESS_ADD(buffer, PAGE_INIT_POSITION)), position(PAGE_INIT_POSITION), frameNum(0), pageNum(0) {}

void Page::finishPage()
{
    PageHeader* header = (PageHeader*) buffer;
    header->close_nano = getNanoTime();
    header->frame_num = frameNum;
    header->last_pos = position;
    frame.setStatusPageClosed();
}

PagePtr Page::load(const string &dir, const string &jname, short pageNum, bool isWriting, bool quickMode)
{
    string path = PageUtil::GenPageFullPath(dir, jname, pageNum);
    void* buffer = PageUtil::LoadPageBuffer(path, JOURNAL_PAGE_SIZE, isWriting, quickMode /*from local then we need to de mlock manually*/);
    if (buffer == nullptr)
        return PagePtr();
    PageHeader* header = (PageHeader*) buffer;
    if (header->status == JOURNAL_PAGE_STATUS_RAW)
    {
        if (!isWriting)
            return PagePtr();
        // initialize page
        memcpy(header->journal_name, jname.c_str(), jname.length() + 1);
        header->start_nano = getNanoTime();
        header->close_nano = -1;
        header->page_num = pageNum;
        // then set back status
        header->status = JOURNAL_PAGE_STATUS_INITED;
        // write current frame header version inside
        header->frame_version = __FRAME_HEADER_VERSION__;
    }
    else if (header->frame_version > 0 && header->frame_version != __FRAME_HEADER_VERSION__)
    {
        // if this is an existing page (status != JOURNAL_PAGE_STATUS_RAW)
        // and frame_version is set
        // (previous we have some page without frame_version set properly)
        // we need to check header version no matter reader or writer
        std::stringstream ss;
        ss << "header version mismatch: " << header->frame_version << " vs " << __FRAME_HEADER_VERSION__;
        throw std::runtime_error(ss.str().c_str());
    }

    PagePtr page = PagePtr(new Page(buffer));
    page->pageNum = pageNum;
    return page;
}



