/**
 * Wrap up all functions into StrategyUtil for wingchun strategy
*/
#include "StrategyUtil.h"
#include "StrategySocketHandler.h"
#include "TypeConvert.hpp"
#include "PageCommStruct.h"
#include "longfist/sys_messages.h"

USING_YJJ_NAMESPACE

#define BL_BASE_FOLDER KUNGFU_JOURNAL_FOLDER "strategy/"
#define BL_REPLAY_FOLDER KUNGFU_JOURNAL_FOLDER "strategy_replay/"

StrategyUtil::StrategyUtil(const string& strategyName, bool isReplay)
{
    if (isReplay) {
        throw std::runtime_error("replay mode is not fully supported yet!");
        writer = JournalWriter::create(BL_REPLAY_FOLDER, strategyName, handler);
    } else {
        handler = StrategySocketHandlerPtr(new StrategySocketHandler(strategyName));
        writer = JournalWriter::create(BL_BASE_FOLDER, strategyName, handler);
        init();
    }
}

StrategyUtilPtr StrategyUtil::create(const string& strategyName, bool isReplay)
{
#ifndef USE_PAGED_SERVICE
    throw std::runtime_error("strategy utilities cannot be utilized without paged");
#endif
    StrategyUtilPtr util = StrategyUtilPtr(new StrategyUtil(strategyName, isReplay));
    return util;
}

StrategyUtil::~StrategyUtil()
{
    writer.reset();
    handler.reset();
}

void StrategyUtil::init() {
    register_strategy(rid_start, rid_end);
    cur_rid = 0;
}

bool StrategyUtil::td_connect(short source) {
    if (handler.get() != nullptr) {
        return handler->td_connect(source);
    } else {
        return false;
    }
}

IntPair StrategyUtil::getRequestIds() const
{
    return std::make_pair(rid_start, rid_end);
}

boost::python::tuple StrategyUtil::getPyRids() const
{
    return boost::python::make_tuple(rid_start, rid_end);
}

bool StrategyUtil::pySubscribe(boost::python::list pyTickers, int source) {
    vector<string> tickers = py_list_to_std_vector<string>(pyTickers);
    return subscribeMarketData(tickers, source);
}

bool StrategyUtil::md_subscribe(const vector<string>& tickers, short source, short msg_type) {
    if (handler.get() != nullptr) {
        return handler->md_subscribe(tickers, source, msg_type);
    } else {
        return false;
    }
}

bool StrategyUtil::register_strategy(int& requestIdStart, int& requestIdEnd) {
    if (handler.get() != nullptr) {
        return handler->register_strategy(requestIdStart, requestIdEnd);
    } else {
        return false;
    }
}

long StrategyUtil::writeStr(const string& str) {
    return writer->writeStr(str);
}