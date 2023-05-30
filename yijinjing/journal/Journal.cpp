/**
 * Journal
 * An abstraction of one continuous and infinite memory.
 * may write / read through page.
*/
#include "Journal.h"
#include "PageUtil.h"
#include "IPageProvider.h"


USING_YJJ_NAMESPACE

JournalPtr Journal::create(const string &dir, const string &jname, int serviceIdx, IPageProviderPtr provider)
{
    JournalPtr jp = JournalPtr(new Journal());
    jp->pageProvider = provider;
    jp->directory = dir;
    jp->shortName = jname;
    jp->serviceIdx = serviceIdx;
    jp->isWriting = provider->isWriter();
    return jp;
}

void Journal::seekTime(long time)
{
    //before seek to time, should release current page first
    if (curPage.get() != nullptr)
        pageProvider->releasePage(curPage->getBuffer(), JOURNAL_PAGE_SIZE, serviceIdx);
    
    if (time == TIME_TO_LAST)
    {
        vector<short> pageNums = PageUtil::GetPageNums(directory, shortName);
        curPage = pageProvider->getPage(directory, shortName, serviceIdx, (pageNums.size() > 0) ? pageNums.back() : 1);
        if (curPage.get() != nullptr)
            curPage->passWrittenFrame();
    }
    else if (time == TIME_FROM_FIRST)
    {
        vector<short> pageNums = PageUtil::GetPageNums(directory, shortName);
        curPage = pageProvider->getPage(directory, shortName, serviceIdx, (pageNums.size() > 0) ? pageNums.front() : 1);
    }
    else
    {
        short pageNum = PageUtil::GetPageNumWithTime(directory, shortName, time);
        curPage = pageProvider->getPage(directory, shortName, serviceIdx, pageNum);
        if (curPage.get() != nullptr)
            curPage->passToTime(time);
    }
    // if the page is inited with null, means reader and no journal at all
    // as keep loading next page may cause huge load of page engine, we simply skip this
    expired = (curPage.get() == nullptr);
}

void Journal::loadNextPage()
{
    if (expired) return;
    if (curPage.get() == nullptr)
    {
        curPage = pageProvider->getPage(directory, shortName, serviceIdx, 1);
    } 
    else
    {
        // allocate new page
        PagePtr newPage = pageProvider->getPage(directory, shortName, serviceIdx, curPage->getPageNum() + 1);
        // stop current page
        if (isWriting)
        {
            curPage->finishPage();
        }
        pageProvider->releasePage(curPage->getBuffer(), JOURNAL_PAGE_SIZE, serviceIdx);
        // reset current page
        curPage = newPage;
    }
}

void Journal::expire()
{
    if (!expired)
    {
        expired = true;
        if (curPage.get() != nullptr)
        {
            pageProvider->releasePage(curPage->getBuffer(), JOURNAL_PAGE_SIZE, serviceIdx);
            curPage.reset();
        }
        // set page expire in page engine
        pageProvider->getPage(directory, shortName, serviceIdx, -1);
    }
}