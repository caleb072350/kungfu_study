#ifndef LONGFIST_UTILS_H
#define LONGFIST_UTILS_H

#include "LFUtils.h"

#include <iostream>
#include <iomanip>
#include <utility>


namespace LF_UTIL_PRINTER_CTP
{
    #include "../api/ctp/v6.3.6_20160606/include/ThostFtdcUserApiStruct.h"
}

// Macro to print struct content
#define PRINT_MD(ptr) ""\
    << std::setw(20) << "TradingDay:" << std::setw(6) << "(c13)" << " " <<  ptr->TradingDay << std::endl \

#endif