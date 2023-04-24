#!/usr/bin/env python
# -*- coding: utf-8 -*-

class SOURCE:
    CTP = 1
    LTS = 2
    FEMAS = 3
    XONE = 4
    XSPEED = 5
    XELE = 6
    XSPEEDL2 = 7
    YISHENG = 8
    HUNGSUN = 10
    SOCKETSNIFFER = 11
    EXANICSNIFFER = 12
    OES = 13
    SANDBOX = 14

class EXCHANGE:
    SSE = 'SSE' # 上海证券交易所
    SZE = 'SZE' # 深圳证券交易所
    CFFEX = 'CFFEX' #中国金融期货交易所

class EXCHANGE_ID:
    SSE = 1    # 上海证券交易所
    SZE = 2    # 深圳证券交易所
    CFFEX = 11 # 中国金融期货交易所

class MsgTypes:
    MD = 101
    L2_MD = 102
    L2_INDEX = 103
    L2_ORDER = 104
    L2_TRADE = 105
    BAR_MD = 110
    QRY_POS = 201
    RSP_POS = 202
    ORDER = 204
    RTN_ORDER = 205
    RTN_TRADE = 206
    ORDER_ACTION = 207
    QRY_ACCOUNT = 208
    RSP_ACCOUNT = 209

#################################################
#   LfActionFlagType: 报单操作标志
#################################################
class LfActionFlagType:
    Delete = '0' # 删除
    Suspend = '1' # 挂起
    Active = '2' # 激活
    Modify = '3' # 修改


