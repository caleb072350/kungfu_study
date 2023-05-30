/**
 * EngineUtil
 * Some useful / common util functions.
 * Some definitions
*/

#ifndef WINGCHUN_ENGINEUTIL_H
#define WINGCHUN_ENGINEUTIL_H

#include "WC_DECLARE.h"

/*                                                                  +------------+
 *                                                        (Fail) -> | ConnectFail|
 *                                                       /          +------------+
 * +------+                                             /
 * | Idle | - (page engine control / auto ) -> connecting   <-- (auto retry) $RECONNECT_UPPER_LIMIT
 * +------+                                             |
 *                                                    (Success)                              +----------+
 *                                                      |                          (Fail) -> | LoginFail|
 *                                                      v                         /          +----------+
 *                                                     Connected - (auto login) ->     
 *                                                                                \             +---------+
 *                                                                                 (Success) -> | LoginSuc|  
 *                                                                                              +---------+                     
*/                    

////////////////////////////////////////////////
/// (String) WingchunEngineStatusMsg
////////////////////////////////////////////////
#define WC_ENGINE_STATUS_IDLE                    "Idle"
#define WC_ENGINE_STATUS_CONNECTING             "Connecting"
#define WC_ENGINE_STATUS_CONNECTED              "Connected"
#define WC_ENGINE_STATUS_CONNECT_FAIL           "ConnectFail"
#define WC_ENGINE_STATUS_LOGIN_SUCCESS          "LoginSuc"
#define WC_ENGINE_STATUS_LOGIN_FAIL             "LoginFail"
#define WC_ENGINE_STATUS_STOPPED                "Stopped"
#define WC_ENGINE_STATUS_STOP_FAIL              "StopFail"

/////////////////////////////////////////////////
/// (String) WingchunConfigKey
/////////////////////////////////////////////////
#define WC_CONFIG_KEY_PASSWORD                   "Password"
#define WC_CONFIG_KEY_AUTH_CODE                  "AuthCode"
#define WC_CONFIG_KEY_NEED_AUTH                  "NeedAuth"
#define WC_CONFIG_KEY_NEED_SETTLE_CONFIRM        "NeedSettleConfirm"
#define WC_CONFIG_KEY_BROKER_ID                  "BrokerID"
#define WC_CONFIG_KEY_USER_ID                    "UserID"
#define WC_CONFIG_KEY_EXCHANGE_ID                "ExchangeID"
#define WC_CONFIG_KEY_INVESTOR_ID                "InvestorID"
#define WC_CONFIG_KEY_FRONT_URL                  "FrontURL"
#define WC_CONFIG_KEY_FRONT_URL_Q                "FrontURLQ"
#define WC_CONFIG_KEY_USER_PRODUCT_INFO          "UserProductInfo"
#define WC_CONFIG_KEY_MCAST_ADDRESS              "McastAddress"
#define WC_CONFIG_KEY_NIC                        "Nic"
#define WC_CONFIG_KEY_PROTOCOL_INFO              "ProtocolInfo"

WC_NAMESPACE_START

class EngineUtil {
public:
    static inline void splitTicker(const char* ticker, char* commodityNo, char* contractNo);
    static const char* gbkErrorMsg2utf8(const char* msg);
};

inline void EngineUtil::splitTicker(const char* ticker, char* commodityNo, char* contractNo) {
    size_t i = 0;
    while (i < strlen(ticker)) {
        if (ticker[i] <= '9' && ticker[i] >= '0')
            break;
        i++;
    }
    strncpy(commodityNo, ticker, i);
    strcpy(contractNo, &ticker[i]);
}


WC_NAMESPACE_END
#endif //WINGCHUN_ENGINEUTIL_H