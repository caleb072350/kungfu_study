#include "MDEngineCTP.h"
#include "TypeConvert.hpp"
#include "Timer.h"
#include "longfist/ctp.h"
#include "longfist/LFUtils.h"

USING_WC_NAMESPACE

MDEngineCTP::MDEngineCTP() : IMDEngine(SOURCE_CTP), api(nullptr), connected(false), logged_in(false), reqId(0){
    logger = yijinjing::KfLog::getLogger("MDEngineCTP");
}

void MDEngineCTP::load(const json& j_config) {
    broker_id = j_config[WC_CONFIG_KEY_BROKER_ID].get<string>();
    user_id = j_config[WC_CONFIG_KEY_USER_ID].get<string>();
    password = j_config[WC_CONFIG_KEY_PASSWORD].get<string>();
    front_url = j_config[WC_CONFIG_KEY_FRONT_URL].get<string>();
}

void MDEngineCTP::connect(long timeout_nsec) {
    if (api == nullptr) {
        api = CThostFtdcMdApi::CreateFtdcMdApi();
        if (!api) {
            throw std::runtime_error("CTP_MD failed to create api");
        }
        api->RegisterSpi(this);
    }
    if (!connected) {
        api->RegisterFront((char*)front_url.c_str());
        api->Init();
        long start_time = yijinjing::getNanoTime();
        while (!connected && yijinjing::getNanoTime() - start_time < timeout_nsec) {
        }
    }
}

void MDEngineCTP::login(long timeout_nsec) {
    if (!logged_in) {
        CThostFtdcReqUserLoginField req = {};
        strcpy(req.BrokerID, broker_id.c_str());
        strcpy(req.UserID, user_id.c_str());
        strcpy(req.Password, password.c_str());
        if (api->ReqUserLogin(&req, reqId++)) {
            KF_LOG_ERROR(logger, "[reqest] login failed!" << " (Bid)" << req.BrokerID << " (UserID)" << req.UserID);
        }
        long start_time = yijinjing::getNanoTime();
        while (!logged_in && yijinjing::getNanoTime() - start_time < timeout_nsec) {
        }
    }
}

void MDEngineCTP::logout() {
    if (logged_in) {
        CThostFtdcUserLogoutField req = {};
        strcpy(req.BrokerID, broker_id.c_str());
        strcpy(req.UserID, user_id.c_str());
        if (api->ReqUserLogout(&req, reqId++)) {
            KF_LOG_ERROR(logger, "[reqest] logout failed!" << " (Bid)" << req.BrokerID << " (UserID)" << req.UserID);
        }
    }
    connected = false;
    logged_in = false;
}

void MDEngineCTP::release_api() {
    if (api != nullptr) {
        api->Release();
        api = nullptr;
    }
}

void MDEngineCTP::subscribeMarketData(const vector<string>& instruments, const vector<string>& markets) {
    int nCount = instruments.size();
    char* insts[nCount];
    for (int i = 0; i < nCount; ++i) {
        insts[i] = (char*)instruments[i].c_str();
    }
    api->SubscribeMarketData(insts, nCount);
}

/* SPI functions
*/
void MDEngineCTP::OnFrontConnected() {
    KF_LOG_INFO(logger, "[OnFrontConnected]");
    connected = true;
}

void MDEngineCTP::OnFrontDisconnected(int reason) {
    KF_LOG_INFO(logger, "[OnFrontDisconnected] reason=" << reason);
    connected = false;
    logged_in = false;
}

#define GBK2UTF8(msg) kungfu::yijinjing::gbk2utf8(string(msg))

void MDEngineCTP::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    if (pRspInfo != nullptr && pRspInfo->ErrorID != 0) {
        KF_LOG_ERROR(logger, "[OnRspUserLogin]" << " (errID)" << pRspInfo->ErrorID
            << " (errMsg)" << GBK2UTF8(pRspInfo->ErrorMsg));
    } else {
        KF_LOG_INFO(logger, "[OnRspUserLogin]" << " (Bid)" << pRspUserLogin->BrokerID << " (UserID)" << pRspUserLogin->UserID
            << " (SName)" << pRspUserLogin->SystemName);
        logged_in = true;
    }
}

void MDEngineCTP::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    if (pRspInfo != nullptr && pRspInfo->ErrorID != 0) {
        KF_LOG_ERROR(logger, "[OnRspUserLogout]" << " (errID)" << pRspInfo->ErrorID << " (errMsg)" << GBK2UTF8(pRspInfo->ErrorMsg));
    } else {
        KF_LOG_INFO(logger, "[OnRspUserLogout]" << " (Bid)" << pUserLogout->BrokerID << " (UserID)" << pUserLogout->UserID);
        logged_in = false;
    }
}

void MDEngineCTP::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    if (pRspInfo != nullptr && pRspInfo->ErrorID != 0) {
        KF_LOG_ERROR(logger, "[OnRspSubMarketData]" << " (errID)" << pRspInfo->ErrorID << " (errMsg)" << GBK2UTF8(pRspInfo->ErrorMsg)
            << " (Tid)" << ((pSpecificInstrument != nullptr) ? pSpecificInstrument->InstrumentID : "null"));
    }
}

void MDEngineCTP::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {
    auto data = parseFrom(*pDepthMarketData);
    on_market_data(&data);
    // if need to write raw data...
    // raw_writer->write_frame(pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField),
    //     source_id, MSG_TYPE_LF_MD_CTP, 1/*islast*/, -1/*invalidRid*/);
}

BOOST_PYTHON_MODULE(libctpmd)
{
    using namespace boost::python;
    class_<MDEngineCTP, boost::shared_ptr<MDEngineCTP> >("Engine")
    .def(init<>())
    .def("init", &MDEngineCTP::initialize)
    .def("start", &MDEngineCTP::start)
    .def("stop", &MDEngineCTP::stop)
    .def("logout", &MDEngineCTP::logout)
    .def("wait_for_stop", &MDEngineCTP::wait_for_stop);
}