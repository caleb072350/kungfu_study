#ifndef LONGFIST_SYS_MESSAGES_H
#define LONGFIST_SYS_MESSAGES_H

/* system message types 0~99 */
// 0 - 9 for test
const short MSG_TYPE_PYTHON_OBJ = 0;
// 10 - 19 strategy
const short MSG_TYPE_STRATEGY_START = 10;
const short MSG_TYPE_STRATEGY_END = 11;
const short MSG_TYPE_TRADE_ENGINE_LOGIN = 12; // we don't need logout, just use strateg_end
const short MSG_TYPE_TRADE_ENGINE_ACK = 13;
const short MSG_TYPE_TRADE_ENGINE_POS_SET = 14;

// 20 - 29 service



// 30 -39 control
const short MSG_TYPE_TRADE_ENGINE_OPEN = 30;
const short MSG_TYPE_TRADE_ENGINE_CLOSE = 31;
const short MSG_TYPE_MD_ENGINE_OPEN = 32;
const short MSG_TYPE_MD_ENGINE_CLOSE = 33;
const short MSG_TYPE_SWITCH_TRADING_DAY = 34;
const short MSG_TYPE_STRING_COMMAND = 35;





//50 - 89 utilities
const short MSG_TYPE_TIME_TICK = 50;
const short MSG_TYPE_SUBSCRIBE_MARKET_DATA = 51;
const short MSG_TYPE_SUBSCRIBE_L2_MD = 52;
const short MSG_TYPE_SUBSCRIBE_INDEX = 53;
const short MSG_TYPE_SUBSCRIBE_ORDER_TRADE = 54;
const short MSG_TYPE_ENGINE_STATUS = 60;

#endif