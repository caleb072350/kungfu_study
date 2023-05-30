/**
 * Page Service Tasks
 * Page engine needs several tasks to be done in schedule
 * here we define tasks which can be implemented in page engine
*/
#include "PageServiceTask.h"
#include "PageEngine.h"
#include "PageUtil.h"
#include "Timer.h"

USING_YJJ_NAMESPACE

#define TEMP_PAGE KUNGFU_JOURNAL_FOLDER "TEMP_PAGE"

const string PstTempPage::PageFullPath = TEMP_PAGE;

PstPidCheck::PstPidCheck(PageEngine *pe): engine(pe) {}

void PstPidCheck::go()
{
    vector<string> clientsToRemove;
    {
        for (auto const &item : engine->pidClient)
        {
            
        }
    }
}