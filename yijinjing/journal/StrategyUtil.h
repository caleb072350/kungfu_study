#ifndef YIJINJING_PAGEUTIL_H
#define YIJINJING_PAGEUTIL_H

#include "IStrategyUtil.h"
#include "JournalWriter.h"

YJJ_NAMESPACE_START

FORWARD_DECLARE_PTR(StrategySocketHandler);
FORWARD_DECLARE_PTR(JournalWriter);
FORWARD_DECLARE_PTR(StrategyUtil);

/**
 * Wrapper class of strategy utilities
*/
class StrategyUtil : public IStrategyUtil
{
protected:
    // start rid, allocated by page service
    int rid_start;
    // end rid, allocated by page service
    int rid_end;
    // current rid
    int cur_rid;

private:
    // handler for socket stuff 
    StrategySocketHandlerPtr handler;
    // wrap-up writer's features
    JournalWriterPtr writer;

protected:
    // initialization, register strategy to page engine.
    void init();
public:
    // override IStrategyUtil
    bool td_connect(short source);
    // override IStrategyUtil
    bool md_subscribe(const vector<string>& tickers, short source, short msg_type);
    // override IStrategyUtil
    bool register_strategy(int& requestIdStart, int& requestIdEnd);

    /** writer feature may used by strategy */
    long writeStr(const string& str);
    /** writer feature may used by strategy (python) */
    long writePyData(uintptr_t data, FH_TYPE_LENGTH length, FH_TYPE_SOURCE source, FH_TYPE_MSG_TP msgType,
                        FH_TYPE_LASTFG lastFlag, FH_TYPE_REQ_ID reqId);
    
    /** writer feature may used by strategy */
    long write_frame(const void* data, FH_TYPE_LENGTH length, FH_TYPE_SOURCE source, FH_TYPE_MSG_TP msgType,
                        FH_TYPE_LASTFG lastFlag, FH_TYPE_REQ_ID reqId);

    /** writer feature may used by strategy */
    long write_frame_extra(const void* data, FH_TYPE_LENGTH length, FH_TYPE_SOURCE source, FH_TYPE_MSG_TP msgType,
                        FH_TYPE_LASTFG lastFlag, FH_TYPE_REQ_ID reqId, FH_TYPE_NANOTM extraNano);

    /** subscribe md with MARKET_DATA flag */
    bool subscribeMarketData(const vector<string>& tickers, short source);
    /** subscribe md with L2_MD flag */
    bool subscribeL2MD(const vector<string>& tickers, short source);

    /** subscribe md with INDEX flag */
    bool subscribeIndex(const vector<string>& tickers, short source);

    /** subscribe md with ORDER_TRADER flag */
    bool subscribeOrderTrade(const vector<string>& tickers, short source);

    /** get current rid, sequentially increment */
    int get_rid();
    /** get request id range */
    IntPair getRequestIds() const;
    /** get request id (python) */
    boost::python::tuple getPyRids() const;
    /** python interface for subscription */
    bool pySubscribe(boost::python::list tickers, int source);

public:
    /** destructor */
    ~StrategyUtil();
    /** constructor */
    StrategyUtil(const string& strategyName, bool isReplay=false);
    /** create method, only strategy name is  enough 
     * folder and journal name is determined
    */
    static StrategyUtilPtr create(const string& strategyName, bool isReplay=false);
};

YJJ_NAMESPACE_END
#endif