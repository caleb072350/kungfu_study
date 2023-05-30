#ifndef WINGCHUN_ITDENGINE_H
#define WINGCHUN_ITDENGINE_H

#include "IEngine.h"
#include "PosHandler.hpp"
#include "Timer.h"
#include "TDUserStruct.h"
#include "longfist/LFDataStruct.h"

#define ORDER_MISC_INFO_SIZE 29

WC_NAMESPACE_START

using kungfu::yijinjing::PosHandlerPtr;
using kungfu::yijinjing::PosHandler;

/**
 * client info, store in trade engine
*/
struct ClientInfoUnit {
    bool is_alive;
    int  journal_index;
    int  account_index;
    int  rid_start;
    int  rid_end;
    PosHandlerPtr pos_handler;
};

/**
 * Trade account information,
 * used when connect or login
*/
struct TradeAccount
{
    char BrokerID[19];
    char UserID[16];
    char InvestorID[19];
    char BussinessUnit[21];
    char Password[21];
};

/**
 * Base class of all trade engines
*/
class ITDEngine : public IEngine 
{
protected:
    /** writer on td_send records all messages to send */
    yijinjing::JournalWriterPtr send_writer;
    /** information about all existing clients */
    map<string, ClientInfoUnit> clients; // clientName: (exist, idx)
    /** trade account */
    vector<TradeAccount> accounts;
    /** -1 if do not accept unregistered account, else return index of accounts */
    int default_account_index;
    /** trade engine user info helper */
    TDUserInfoHelperPtr user_helper;
    /** trade engine user info helper */
    TDEngineInfoHelperPtr td_helper;
    /** request_id, incremental */
    int request_id;
    /** local id, incremental */
    int local_id;
    /** current nano time */
    long cur_time;

protected:
    // add strategy, return true if added successfully
    bool add_client(const string& name, const json& j_request);
    // remove strategy
    bool remove_client(const string& name, const json& j_request);

protected:
    /** default constructor */
    ITDEngine(short source);
    /** setup reader thread */
    virtual void set_reader_thread();
    /** keep listening to system journal */
    void listening();
    /** load config information */
    virtual void load(const json& j_config);
    /** init reader and writer */
    virtual void init();
    /** load TradeAccount from json */
    virtual TradeAccount load_account(int idx, const json& j_account);

public:
    // config and account related
    /** resize account number */
    virtual void resize_accounts(int account_num) = 0;
    /** connect each account and api with timeout as wait interval*/
    virtual void connect(long timeout_nsec) = 0;
    /** login all account and api with timeout as wait interval*/
    virtual void login(long timeout_nsec) = 0;
    /** send logout request for each api*/
    virtual void logout() = 0;
    /** release api items */
    virtual void release_api() = 0;
    /** is every accounts connected?*/
    virtual bool is_connected() const = 0;
    /** is every accounts logged in?*/
    virtual bool is_logged_in() const = 0;

public:
    /** some clean up when day switch */
    virtual void on_switch_day();
    /** on market data */
    virtual void on_market_data(const LFMarketDataField* data, long rcv_time) {}

    // virtual interfaces for all trade engines
    /** request investor's existing position */
    virtual void req_investor_position(const LFQryPositionField* data, int account_index, int request_id) = 0;
    /** request account info */
    virtual void req_qry_account(const LFQryAccountField* data, int account_index, int request_id) = 0;
    /** insert order */
    virtual void req_order_insert(const LFInputOrderField* data, int account_index, int request_id, long rcv_time) = 0;
    /** request order action (only cancle is accomplished)*/
    virtual void req_order_action(const LFOrderActionField* data, int account_index, int request_id, long rcv_time) = 0;
    /** on investor position, engine (on_data)*/
    void on_rsp_position(const LFRspPositionField* pos, bool isLast, int requestID, int errorID = 0, const char* errorMsg = nullptr);
    /** on rsp order insert, engine (on_data)*/
    void on_rsp_order_insert(const LFInputOrderField* order, int requestID, int errorID = 0, const char* errorMsg = nullptr);
    /** on rsp order action, engine (on_data)*/
    void on_rsp_order_action(const LFOrderActionField* action, int requestID, int errorID = 0, const char* errorMsg = nullptr);
    /** on rsp account info, engine (on_data)*/
    void on_rsp_account(const LFRspAccountField* account, int requestID, int errorID = 0, const char* errorMsg = nullptr);
    /** on rtn order, engine (on_data)*/
    void on_rtn_order(const LFRtnOrderField* rtn_order);
    /** on rtn trade, engine (on_data)*/
    void on_rtn_trade(const LFRtnTradeField* rtn_trade);

};

DECLARE_PTR(ITDEngine);

WC_NAMESPACE_END

#endif