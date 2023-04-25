#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from ctypes import *

import longfist_constants as lf

from longfist_structs_sniffer import *

class LFMarketDataField(Structure):
    _fields_ = [
        ("TradingDay", c_char * 13), #交易日
        ("InstrumentID", c_char * 31), #合约代码
        ("ExchangeID", c_char * 9), #交易所代码
        ("ExchangeInstID", c_char * 64), #合约在交易所代码
        ("LastPrice", c_double), #最新价
        ("PreSettlementPrice", c_double), #上次结算价
        
    ]