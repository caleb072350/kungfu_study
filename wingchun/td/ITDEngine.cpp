#include "ITDEngine.h"
#include "PageCommStruct.h" /** REQUEST_ID_RANGE */
#include "longfist/LFConstants.h"
#include "longfist/LFUtils.h"
#include "longfist/sys_messages.h"
#include <algorithm>

USING_WC_NAMESPACE

class RidClientManager
{
private:
    /** rid, strategy_name map */
    map<int, string> rid2client;
public:
    inline void set(int rid_start, string name) {
        rid2client[rid_start / REQUEST_ID_RANGE] = name;
    }
    
    inline string get(int rid) {
        auto iter = rid2client.find(rid / REQUEST_ID_RANGE);
        if (iter == rid2client.end()) {
            return "";
        } else {
            return iter->second;
        }
    }
};

/** manage rid and client_name matching */
RidClientManager rid_manager;

ITDEngine::ITDEngine(short source) : IEngine(source), default_account_index(-1), local_id(0), request_id(1) {
    
}

void ITDEngine::set_reader_thread() {
    reader_thread = ThreadPtr(new std::thread(boost::bind(&ITDEngine::listening, this)));
}

void ITDEngine::init() {
    reader = yijinjing::JournalReader::createRevisableReader(name());
    JournalPair tdPair = getTdJournalPair(source_id);
    writer = yijinjing::JournalSafeWriter::create(tdPair.first, tdPair.second, name());
    JournalPair tdSendPair = getTdSendJournalPair(source_id);
    send_writer = yijinjing::JournalWriter::create(tdSendPair.first, tdSendPair.second, "SEND_" + name());
    user_helper = TDUserInfoHelperPtr(new TDUserInfoHelper(source_id));
    td_helper = TDEngineInfoHelperPtr(new TDEngineInfoHelper(source_id, name()));
}

void ITDEngine::listening() {
    yijinjing::FramePtr frame;
    while (isRunning && signal_received < 0) {
        frame = reader->getNextFrame();
        if (frame.get() != nullptr) {
            short msg_type = frame->getMsgType();
            short msg_source = frame->getSource();
            cur_time = frame->getNano();
            if (msg_type == MSG_TYPE_LF_MD) {
                void* fdata = frame->getData();
                LFMarketDataField* md = (LFMarketDataField*)fdata;
                on_market_data(md, cur_time);
                continue;
            } else if (msg_type < 200) {
                // system related...
                if (msg_type == MSG_TYPE_TRADE_ENGINE_LOGIN && msg_source == source_id)
                {
                    try {
                        string  content((char*)frame->getData());
                        json j_request = json::parse(content);
                        string client_name = j_request["name"].get<string>();
                        if (add_client(client_name, j_request))
                            KF_LOG_INFO(logger, "[user] Accepted: " << client_name);
                        else
                            KF_LOG_INFO(logger, "[user] Rejected: " << client_name);
                    }
                    catch (...) {
                        KF_LOG_ERROR(logger, "error in parsing TRADE_ENGINE_LOGIN: " << (char*)frame->getData());
                    }
                }
                else if (msg_type == MSG_TYPE_STRATEGY_END)
                {
                    try {
                        string content((char*)frame->getData());
                        json j_request = json::parse(content);
                    }
                }
            }
        }
    }
}