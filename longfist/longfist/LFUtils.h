#ifndef LONGFIST_UTILS_H
#define LONGFIST_UTILS_H


#include "LFDataStruct.h"

#include <string>

inline std::string getExchangeName(short exchange_id) {
    switch (exchange_id)
    {
    case 2:    // 深圳证券交易所
        return "SZE";
    case 11:   // 中国金融期货交易所
        return "CFFEX";
    case 1:   // 上海证券交易所 
        return "SSE";
    case 12:  // 上海期货交易所
			return "SHFE";
    case 13:  // 大连商品交易所
        return "DCE";
    case 14:  // 郑州商品交易所
        return "CZCE";
    }
}

inline int getExchangeId(std::string exchange_name) {
    if (exchange_name.compare("SZE") == 0 || exchange_name.compare("sze") == 0) // 深圳证券交易所
        return 2;
    if (exchange_name.compare("CFFEX") == 0 || exchange_name.compare("cffex")==0) // 中国金融期货交易所
        return 11;
    if (exchange_name.compare("SSE") == 0 || exchange_name.compare("sse") == 0) // 上海证券交易所
        return 1;
    if (exchange_name.compare("DCE") == 0 || exchange_name.compare("dce") == 0) // 大连商品交易所
        return 13;
    if (exchange_name.compare("SHFE") == 0 || exchange_name.compare("shfe") == 0) // 上海期货交易所
        return 12;
    if (exchange_name.compare("CZCE") == 0 || exchange_name.compare("czce") == 0) // 郑州商品交易所
        return 14;
    return -1;
}

typedef std::pair<std::string, std::string> JournalPair;

inline JournalPair getMdJournalPair(short source)
{
    switch (source)
    {
    case 2:
        return {"/shared/kungfu/journal/MD/LTS/", "MD_LTS"};
    case 6:
        return {"/shared/kungfu/journal/MD/XELE/", "MD_XELE"};
    default:
        return {"", ""};
    }
}

inline JournalPair getTdJournalPair(short source)
{
    switch (source) 
    {
        case 2:
            return {"/shared/kungfu/journal/TD/LTS/", "TD_LTS"};
        case 6:
            return {"/shared/kungfu/journal/TD/XELE/", "TD_XELE"};
        case 1:
            return {"/shared/kungfu/journal/TD/CTP/", "TD_CTP"};
        case 5:
            return {"/shared/kungfu/journal/TD/XSPEED/", "TD_XSPEED"};
        case 13:
            return {"/shared/kungfu/journal/TD/OES/", "TD_OES"};
        case 8:
            return {"/shared/kungfu/journal/TD/YISHENG/", "TD_YISHENG"};
        case 11:
			return {"/shared/kungfu/journal/TD/SOCKETSNIFFER/", "TD_SOCKETSNIFFER"};
		case 4:
			return {"/shared/kungfu/journal/TD/XONE/", "TD_XONE"};
		case 14:
			return {"/shared/kungfu/journal/TD/SANDBOX/", "TD_SANDBOX"};
		case 10:
			return {"/shared/kungfu/journal/TD/HUNDSUN/", "TD_HUNDSUN"};
		case 7:
			return {"/shared/kungfu/journal/TD/XSPEEDL2/", "TD_XSPEEDL2"};
		case 3:
			return {"/shared/kungfu/journal/TD/FEMAS/", "TD_FEMAS"};
		case 12:
			return {"/shared/kungfu/journal/TD/EXANICSNIFFER/", "TD_EXANICSNIFFER"};
		default:
			return {"", ""};
        
    }
}

inline JournalPair getTdSendJournalPair(short source) {
    switch(source)
	{
		case 2:
			return {"/shared/kungfu/journal/TD_SEND/LTS/", "TD_SEND_LTS"};
		case 6:
			return {"/shared/kungfu/journal/TD_SEND/XELE/", "TD_SEND_XELE"};
		case 1:
			return {"/shared/kungfu/journal/TD_SEND/CTP/", "TD_SEND_CTP"};
		case 5:
			return {"/shared/kungfu/journal/TD_SEND/XSPEED/", "TD_SEND_XSPEED"};
		case 13:
			return {"/shared/kungfu/journal/TD_SEND/OES/", "TD_SEND_OES"};
		case 8:
			return {"/shared/kungfu/journal/TD_SEND/YISHENG/", "TD_SEND_YISHENG"};
		case 11:
			return {"/shared/kungfu/journal/TD_SEND/SOCKETSNIFFER/", "TD_SEND_SOCKETSNIFFER"};
		case 4:
			return {"/shared/kungfu/journal/TD_SEND/XONE/", "TD_SEND_XONE"};
		case 14:
			return {"/shared/kungfu/journal/TD_SEND/SANDBOX/", "TD_SEND_SANDBOX"};
		case 10:
			return {"/shared/kungfu/journal/TD_SEND/HUNDSUN/", "TD_SEND_HUNDSUN"};
		case 7:
			return {"/shared/kungfu/journal/TD_SEND/XSPEEDL2/", "TD_SEND_XSPEEDL2"};
		case 3:
			return {"/shared/kungfu/journal/TD_SEND/FEMAS/", "TD_SEND_FEMAS"};
		case 12:
			return {"/shared/kungfu/journal/TD_SEND/EXANICSNIFFER/", "TD_SEND_EXANICSNIFFER"};
		default:
			return {"", ""};
	}
}


#endif