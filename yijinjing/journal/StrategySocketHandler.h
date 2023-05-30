/**
 * strategy needs some functions to page engine
 * As ClientPageProvider has already provides socket access,
 * StrategySocketHandler inherits ClientPageProvider
 * and wrap-up some other features for the ease of usage
*/

#ifndef PROJECT_STRATEGYSOCKETHANDLER_H
#define PROJECT_STRATEGYSOCKETHANDLER_H

#include "YJJ_DECLARE.h"
#include "PageProvider.h"
#include "IStrategyUtil.h"

YJJ_NAMESPACE_START

/**
 * Strategy socket handler
*/
class StrategySocketHandler : public ClientPageProvider, public IStrategyUtil
{
public:
    /** default constructor with strategy name */
    StrategySocketHandler(const string& strategy_name);
    /** register strategy first, with rid_start, rid_end returned */
    virtual bool register_strategy(int& rid_start, int& rid_end);
    /** connect trade engine with source_id determined */
    virtual bool td_connect(short source);
    /** subscribe market data with tickers / source / msg_type assigned */
    virtual bool md_subscribe(const vector<string>& tickers, short source, short msg_type);
};

DECLARE_PTR(StrategySocketHandler);

YJJ_NAMESPACE_END

#endif