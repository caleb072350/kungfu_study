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


#endif