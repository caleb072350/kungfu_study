#ifndef LONGFIST_CONSTANTS_H
#define LONGFIST_CONSTANTS_H

#include <memory.h>
#include <cstdlib>
#include <stdio.h>

// Index for Sources...
const short SOURCE_CTP = 1;
const short SOURCE_LTS = 2;
const short SOURCE_FEMAS = 3;
const short SOURCE_XONE = 4;
const short SOURCE_XSPEED = 5;
const short SOURCE_XELE = 6;
const short SOURCE_XSPEEDL2 = 7;
const short SOURCE_YISHENG = 8;
const short SOURCE_HUNDSUN  = 10;
const short SOURCE_SOCKETSNIFFER = 11;
const short SOURCE_EXANICSNIFFER = 12;
const short SOURCE_OES = 13;
const short SOURCE_SANDBOX = 14;

// Exchange names
#define EXCHANGE_SSE "SSE" //上海证券交易所
#define EXCHANGE_SZE "SZE" // 深圳证券交易所
#define EXCHANGE_CFFEX "CFFEX" // 中国金融期货交易所
#define EXCHANGE_SHFE "SHFE" //上海期货交易所
#define EXCHANGE_DCE "DCE" // 大连商品交易所
#define EXCHANGE_CZCE "CZCE" // 郑州商品交易所

// Exchange ids
#define EXCHANGE_ID_SSE 1 // 上海证券交易所
#define EXCHANGE_ID_SZE 2 // 深圳证券交易所
#define EXCHANGE_ID_CFFEX 11 //中国金融期货交易所
#define EXCHANGE_ID_SHFE 12 //上海期货交易所
#define EXCHANGE_ID_DCE 13 // 大连商品交易所
#define EXCHANGE_ID_CZCE 14 // 郑州商品交易所

// MsgTypes that used for LF data structure...
const short MSG_TYPE_LF_MD              = 101;
const short MSG_TYPE_LF_L2_MD           = 102;
const short MSG_TYPE_LF_L2_INDEX        = 103;
const short MSG_TYPE_LF_L2_ORDER        = 104;
const short MSG_TYPE_LF_L2_TRADE        = 105;
const short MSG_TYPE_LF_BAR_MD          = 110;
const short MSG_TYPE_LF_QRY_POS         = 201;
const short MSG_TYPE_LF_RSP_POS         = 202;
const short MSG_TYPE_LF_ORDER           = 204;
const short MSG_TYPE_LF_RTN_ORDER       = 205;
const short MSG_TYPE_LF_RTN_TRADE       = 206;
const short MSG_TYPE_LF_ORDER_ACTION    = 207;
const short MSG_TYPE_LF_QRY_ACCOUNT     = 208;
const short MSG_TYPE_LF_RSP_ACCOUNT     = 209;

// MsgTypes that from origianl data structures...
// ctp, idx=1
const short MSG_TYPE_LF_MD_CTP          = 1101; // CThostFtdcDepthMarketDataField from ctp/ThostFtdcUserApiStruct.h
const short MSG_TYPE_LF_QRY_POS_CTP     = 1201; // CThostFtdcQryInvestorPositionField from ctp/ThostFtdcUserApiStruct.h
const short MSG_TYPE_LF_RSP_POS_CTP     = 1202; // CThostFtdcInvestorPositionField from ctp/ThostFtdcUserApiStruct.h
const short MSG_TYPE_LF_ORDER_CTP       = 1204; // CThostFtdcInputOrderField from ctp/ThostFtdcUserApiStruct.h
const short MSG_TYPE_LF_RTN_ORDER_CTP   = 1205; // CThostFtdcOrderField from ctp/ThostFtdcUserApiStruct.h
const short MSG_TYPE_LF_RTN_TRADE_CTP   = 1206; // CThostFtdcTradeField from ctp/ThostFtdcUserApiStruct.h
const short MSG_TYPE_LF_ORDER_ACTION_CTP= 1207; // CThostFtdcInputOrderActionField from ctp/ThostFtdcUserApiStruct.h   
const short MSG_TYPE_LF_QRY_ACCOUNT_CTP = 1208; // CThostFtdcQryTradingAccountField from ctp/ThostFtdcUserApiStruct.h
const short MSG_TYPE_LF_RSP_ACCOUNT_CTP = 1209; // CThostFtdcTradingAccountField from ctp/ThostFtdcUserApiStruct.h

// lts, idx=2
const short MSG_TYPE_LF_MD_LTS          = 2101; // CSecurityFtdcDepthMarketDataField from lts/SecurityFtdcUserApiStruct.h
const short MSG_TYPE_LF_L2_MD_LTS       = 2102; // _LTS_::CSecurityFtdcL2MarketDataField from lts/SecurityFtdcL2MDUserApiStruct.h
const short MSG_TYPE_LF_L2_INDEX_LTS    = 2103; // _LTS_::CSecurityFtdcL2IndexField from lts/SecurityFtdcL2MDUserApiStruct.h
const short MSG_TYPE_LF_L2_ORDER_LTS    = 2104; // _LTS_::CSecurityFtdcL2OrderField from lts/SecurityFtdcL2MDUserApiStruct.h
const short MSG_TYPE_LF_L2_TRADE_LTS    = 2105; // _LTS_::CSecurityFtdcL2TradeField from lts/SecurityFtdcL2MDUserApiStruct.h
const short MSG_TYPE_LF_QRY_POS_LTS     = 2201; // CSecurityFtdcQryInvestorPositionField from lts/SecurityFtdcUserApiStruct.h
const short MSG_TYPE_LF_RSP_POS_LTS     = 2202; // CSecurityFtdcInvestorPositionField from lts/SecurityFtdcUserApiStruct.h
const short MSG_TYPE_LF_ORDER_LTS       = 2204; // CSecurityFtdcInputOrderField from lts/SecurityFtdcUserApiStruct.h
const short MSG_TYPE_LF_RTN_ORDER_LTS   = 2205; // CSecurityFtdcOrderField from lts/SecurityFtdcUserApiStruct.h
const short MSG_TYPE_LF_RTN_TRADE_LTS   = 2206; // CSecurityFtdcTradeField from lts/SecurityFtdcUserApiStruct.h
const short MSG_TYPE_LF_ORDER_ACTION_LTS = 2207; // CSecurityFtdcInputOrderActionField from lts/SecurityFtdcUserApiStruct.h
const short MSG_TYPE_LF_QRY_ACCOUNT_LTS = 2208; // CSecurityFtdcQryTradingAccountField from lts/SecurityFtdcUserApiStruct.h
const short MSG_TYPE_LF_RSP_ACCOUNT_LTS = 2209; // CSecurityFtdcTradingAccountField from lts/SecurityFtdcUserApiStruct.h

// femas, idx=3
const short MSG_TYPE_LF_MD_FEMAS      = 3101; // CUstpFtdcDepthMarketDataField from femas/USTPFtdcUserApiStruct.h
const short MSG_TYPE_LF_QRY_POS_FEMAS = 3201; // CUstpFtdcQryInvestorPositionField from femas/USTPFtdcUserApiStruct.h
const short MSG_TYPE_LF_RSP_POS_FEMAS = 3202; // CUstpFtdcRspInvestorPositionField from femas/USTPFtdcUserApiStruct.h
const short MSG_TYPE_LF_ORDER_FEMAS   = 3204; // CUstpFtdcInputOrderField from femas/USTPFtdcUserApiStruct.h
const short MSG_TYPE_LF_RTN_ORDER_FEMAS = 3205; // CUstpFtdcOrderField from femas/USTPFtdcUserApiStruct.h
const short MSG_TYPE_LF_RTN_TRADE_FEMAS = 3206; // CUstpFtdcTradeField from femas/USTPFtdcUserApiStruct.h
const short MSG_TYPE_LF_ORDER_ACTION_FEMAS = 3207; // CUstpFtdcOrderActionField from femas/USTPFtdcUserApiStruct.h
const short MSG_TYPE_LF_QRY_ACCOUNT_FEMAS = 3208; // CUstpFtdcQryInvestorAccountField from femas/USTPFtdcUserApiStruct.h
const short MSG_TYPE_LF_RSP_ACCOUNT_FEMAS = 3209; // CUstpFtdcRspInvestorAccountField from femas/USTPFtdcUserApiStruct.h

// xone, idx=4
const short MSG_TYPE_LF_QRY_POS_XONE  = 4201; // CX1FtdcQryPositionField from xone/X1FtdcApiStruct.h
const short MSG_TYPE_LF_ORDER_XONE    = 4204; // CX1FtdcInsertOrderField from xone/X1FtdcApiStruct.h
const short MSG_TYPE_LF_RTN_ORDER_XONE = 4205; // CX1FtdcRspPriOrderField from xone/X1FtdcApiStruct.h
const short MSG_TYPE_LF_RTN_TRADE_XONE = 4206; // CX1FtdcRspPriMatchInfoField from xone/X1FtdcApiStruct.h
const short MSG_TYPE_LF_RSP_ACCOUNT_XONE = 4209; // CX1FtdcRspCapitalField from xone/X1FtdcApiStruct.h
// extra messages...
const short MSG_TYPE_LF_RTN_CANCEL_XONE = 4801; // CX1FtdcRspPriCancelOrderField from xone/X1FtdcApiStruct.h
const short MSG_TYPE_LF_RSP_OPER_ORDER_XONE = 4802; // CX1FtdcRspOperOrderField from xone/X1FtdcApiStruct.h
const short MSG_TYPE_LF_REQ_CANCEL_ORDER_XONE = 4803; // CX1FtdcCancelOrderField from xone/X1FtdcApiStruct.h
const short MSG_TYPE_LF_RSP_POSITION_XONE = 4804; // CX1FtdcRspPositionField from xone/X1FtdcApiStruct.h

// xspeed, idx=5
const short MSG_TYPE_LF_MD_XSPEED     = 5101; // DFITCDepthMarketDataField from xspeed/DFITCApiStruct.h

// xele, idx=6
const short MSG_TYPE_LF_MD_XELE       = 6101; // CXeleMdFtdcDepthMarketDataField from xele/XeleMdFtdcUserApiStruct.h
// extra messages...
const short MSG_TYPE_LF_SHFE_MARKET_DATA_UNION_XELE = 6901; // CXeleShfeMarketDataUnion from xele/XeleMdFtdcUserApiStruct.h

// xspeedl2, idx=7
const short MSG_TYPE_LF_MD_XSPEEDL2   = 7101; // DFITC_L2::MDBestAndDeep from xspeed/DFITCL2ApiDataType.h

// yisheng, idx=8
const short MSG_TYPE_LF_MD_YISHENG    = 8101; // TapAPIQuoteWhole from yisheng/TapQuoteAPIDataType.h
const short MSG_TYPE_LF_QRY_POS_YISHENG = 8201; // TapAPIPositionQryReq from yisheng/TapTradeAPIDataType.h
const short MSG_TYPE_LF_RSP_POS_YISHENG = 8202; // TapAPIPositionInfo from yisheng/TapTradeAPIDataType.h
const short MSG_TYPE_LF_ORDER_YISHENG = 8204; // TapAPINewOrder from yisheng/TapTradeAPIDataType.h
const short MSG_TYPE_LF_RTN_ORDER_YISHENG = 8205; // TapAPIOrderInfo from yisheng/TapTradeAPIDataType.h
const short MSG_TYPE_LF_RTN_TRADE_YISHENG = 8206; // TapAPIFillInfo from yisheng/TapTradeAPIDataType.h
const short MSG_TYPE_LF_ORDER_ACTION_YISHENG = 8207; // TapAPIOrderCancelReq from yisheng/TapTradeAPIDataType.h
const short MSG_TYPE_LF_QRY_ACCOUNT_YISHENG = 8208; // TapAPIFundReq from yisheng/TapTradeAPIDataType.h
const short MSG_TYPE_LF_RSP_ACCOUNT_YISHENG = 8209; // TapAPIFundData from yisheng/TapTradeAPIDataType.h

// hundsun, idx=10

// socketsniffer, idx=11
// extra messages...
const short MSG_TYPE_LF_XSPEED_L1_SOCKETSNIFFER = 11901; // XSPEED_L1 from sniffer/MdStruct.h
const short MSG_TYPE_LF_XSPEED_L2_SOCKETSNIFFER = 11902; // XSPEED_L2 from sniffer/MdStruct.h
const short MSG_TYPE_LF_XSPEED_L1_ANLIANG_SOCKETSNIFFER = 11903; // XSPEED_L1_ANLIANG from sniffer/MdStruct.h
const short MSG_TYPE_LF_XSPEED_L2_ANLIANG_SOCKETSNIFFER = 11904; // XSPEED_L2_ANLIANG from sniffer/MdStruct.h
const short MSG_TYPE_LF_XSPEED_L2_ENTRUST_TEN_SOCKETSNIFFER = 11905; // XSPEED_L2_ORDER10 from sniffer/MdStruct.h
const short MSG_TYPE_LF_XSPEED_L2_MATCH_BY_PRICE_SOCKETSNIFFER = 11906; // XSPEED_L2_MATCH_BY_PRICE from sniffer/MdStruct.h
const short MSG_TYPE_LF_XSPEED_L2_ORDER_STATISTICS_SOCKETSNIFFER = 11907; // XSPEED_L2_ORDER_STATISTICS from sniffer/MdStruct.h
const short MSG_TYPE_LF_XSPEED_L2_CURRENT_SETTLE_SOCKETSNIFFER = 11908; // XSPEED_L2_CURRENT_SETTLE from sniffer/MdStruct.h
const short MSG_TYPE_LF_XSPEED_L2_ARB_SOCKETSNIFFER = 11909; // XSPEED_L2_ARB from sniffer/MdStruct.h
const short MSG_TYPE_LF_USTP_L2_SOCKETSNIFFER = 11910; // USTP_L2 from sniffer/MdStruct.h
const short MSG_TYPE_LF_GUAVA_L1_SOCKETSNIFFER = 11911; // GUAVA_L1 from sniffer/MdStruct.h

// exanicsniffer, idx=12
// extra messages...
const short MSG_TYPE_LF_XSPEED_L1_EXANICSNIFFER = 12901; // XSPEED_L1 from sniffer/MdStruct.h
const short MSG_TYPE_LF_XSPEED_L2_EXANICSNIFFER = 12902; // XSPEED_L2 from sniffer/MdStruct.h
const short MSG_TYPE_LF_XSPEED_L1_ANLIANG_EXANICSNIFFER = 12903; // XSPEED_L1_ANLIANG from sniffer/MdStruct.h
const short MSG_TYPE_LF_XSPEED_L2_ANLIANG_EXANICSNIFFER = 12904; // XSPEED_L2_ANLIANG from sniffer/MdStruct.h
const short MSG_TYPE_LF_XSPEED_L2_ENTRUST_TEN_EXANICSNIFFER = 12905; // XSPEED_L2_ORDER10 from sniffer/MdStruct.h
const short MSG_TYPE_LF_XSPEED_L2_MATCH_BY_PRICE_EXANICSNIFFER = 12906; // XSPEED_L2_MATCH_BY_PRICE from sniffer/MdStruct.h
const short MSG_TYPE_LF_XSPEED_L2_ORDER_STATISTICS_EXANICSNIFFER = 12907; // XSPEED_L2_ORDER_STATISTICS from sniffer/MdStruct.h
const short MSG_TYPE_LF_XSPEED_L2_CURRENT_SETTLE_EXANICSNIFFER = 12908; // XSPEED_L2_CURRENT_SETTLE from sniffer/MdStruct.h
const short MSG_TYPE_LF_XSPEED_L2_ARB_EXANICSNIFFER = 12909; // XSPEED_L2_ARB from sniffer/MdStruct.h
const short MSG_TYPE_LF_USTP_L2_EXANICSNIFFER = 12910; // USTP_L2 from sniffer/MdStruct.h
const short MSG_TYPE_LF_GUAVA_L1_EXANICSNIFFER = 12911; // GUAVA_L1 from sniffer/MdStruct.h

// oes, idx=13
const short MSG_TYPE_LF_MD_OES        = 13101; // _MdsMktDataSnapshot from oes/mds_api/mds_api.h
const short MSG_TYPE_LF_ORDER_OES     = 13204; // _OesOrdBaseInfo from oes/oes_global/oes_base_model.h
const short MSG_TYPE_LF_RTN_ORDER_OES = 13205; // _OesOrdCnfm from oes/oes_global/oes_base_model.h
const short MSG_TYPE_LF_RTN_TRADE_OES = 13206; // _OesTrdCnfm from oes/oes_global/oes_base_model.h
const short MSG_TYPE_LF_QRY_ACCOUNT_OES = 13208; // _OesQryCashAssetFilter from oes/oes_global/oes_qry_packets.h
const short MSG_TYPE_LF_RSP_ACCOUNT_OES = 13209; // _OesCashAssetItem from oes/oes_global/oes_qry_packets.h

// sandbox, idx=14

///////////////////////////////////
// LfActionFlagType: 报单操作标志
///////////////////////////////////
//删除
#define LF_CHAR_Delete          '0'
//挂起
#define LF_CHAR_Suspend         '1'
//激活
#define LF_CHAR_Active          '2'
//修改
#define LF_CHAR_Modify          '3'

typedef char LfActionFlagType;

///////////////////////////////////
// LfContingentConditionType: 触发条件
///////////////////////////////////
//立即
#define LF_CHAR_Immediately     '1'
//止损
#define LF_CHAR_Touch           '2'
//止赢
#define LF_CHAR_TouchProfit     '3'
//预埋单
#define LF_CHAR_ParkedOrder     '4'
//最新价大于条件价
#define LF_CHAR_LastPriceGreaterThanStopPrice '5'
//最新价大于等于条件价
#define LF_CHAR_LastPriceGreaterEqualStopPrice '6'
//最新价小于条件价
#define LF_CHAR_LastPriceLesserThanStopPrice '7'
//最新价小于等于条件价
#define LF_CHAR_LastPriceLesserEqualStopPrice '8'
//卖一价大于条件价
#define LF_CHAR_AskPriceGreaterThanStopPrice '9'
//卖一价大于等于条件价
#define LF_CHAR_AskPriceGreaterEqualStopPrice 'A'
//卖一价小于条件价
#define LF_CHAR_AskPriceLesserThanStopPrice 'B'
//卖一价小于等于条件价
#define LF_CHAR_AskPriceLesserEqualStopPrice 'C'
//买一价大于条件价
#define LF_CHAR_BidPriceGreaterThanStopPrice 'D'
//买一价大于等于条件价
#define LF_CHAR_BidPriceGreaterEqualStopPrice 'E'
//买一价小于条件价
#define LF_CHAR_BidPriceLesserThanStopPrice 'F'
//买一价小于等于条件价
#define LF_CHAR_BidPriceLesserEqualStopPrice 'H'

typedef char LfContingentConditionType;

///////////////////////////////////
// LfDirectionType: 买卖方向
///////////////////////////////////
//买
#define LF_CHAR_Buy             '0'
//卖
#define LF_CHAR_Sell            '1'

typedef char LfDirectionType;

///////////////////////////////////
// LfForceCloseReasonType: 强平原因
///////////////////////////////////
//非强平
#define LF_CHAR_NotForceClose   '0'
//资金不足
#define LF_CHAR_LackDeposit     '1'
//客户超仓
#define LF_CHAR_ClientOverPositionLimit '2'
//会员超仓
#define LF_CHAR_MemberOverPositionLimit '3'
//持仓非整数倍
#define LF_CHAR_NotMultiple     '4'
//违规
#define LF_CHAR_Violation       '5'
//其它
#define LF_CHAR_Other           '6'
//自然人临近交割
#define LF_CHAR_PersonDeliv     '7'

typedef char LfForceCloseReasonType;

///////////////////////////////////
// LfHedgeFlagType: 投机套保标志
///////////////////////////////////
//投机
#define LF_CHAR_Speculation     '1'
//套利
#define LF_CHAR_Argitrage       '2'
//套保
#define LF_CHAR_Hedge           '3'
//做市商(femas)
#define LF_CHAR_MarketMaker     '4'
//匹配所有的值(femas)
#define LF_CHAR_AllValue        '9'

typedef char LfHedgeFlagType;

///////////////////////////////////
// LfOffsetFlagType: 开平标志
///////////////////////////////////
//开仓
#define LF_CHAR_Open            '0'
//平仓
#define LF_CHAR_Close           '1'
//强平
#define LF_CHAR_ForceClose      '2'
//平今
#define LF_CHAR_CloseToday      '3'
//平昨
#define LF_CHAR_CloseYesterday  '4'
//强减
#define LF_CHAR_ForceOff        '5'
//本地强平
#define LF_CHAR_LocalForceClose '6'
//不分开平
#define LF_CHAR_Non             'N'

typedef char LfOffsetFlagType;

///////////////////////////////////
// LfOrderPriceTypeType: 报单价格条件
///////////////////////////////////
//任意价
#define LF_CHAR_AnyPrice        '1'
//限价
#define LF_CHAR_LimitPrice      '2'
//最优价
#define LF_CHAR_BestPrice       '3'

typedef char LfOrderPriceTypeType;

///////////////////////////////////
// LfOrderStatusType: 报单状态
///////////////////////////////////
//全部成交（最终状态）
#define LF_CHAR_AllTraded       '0'
//部分成交还在队列中
#define LF_CHAR_PartTradedQueueing '1'
//部分成交不在队列中（部成部撤， 最终状态）
#define LF_CHAR_PartTradedNotQueueing '2'
//未成交还在队列中
#define LF_CHAR_NoTradeQueueing '3'
//未成交不在队列中（被拒绝，最终状态）
#define LF_CHAR_NoTradeNotQueueing '4'
//撤单
#define LF_CHAR_Canceled        '5'
//订单已报入交易所未应答
#define LF_CHAR_AcceptedNoReply '6'
//未知
#define LF_CHAR_Unknown         'a'
//尚未触发
#define LF_CHAR_NotTouched      'b'
//已触发
#define LF_CHAR_Touched         'c'
//废单错误（最终状态）
#define LF_CHAR_Error           'd'
//订单已写入
#define LF_CHAR_OrderInserted   'i'
//前置已接受
#define LF_CHAR_OrderAccepted   'j'

typedef char LfOrderStatusType;

///////////////////////////////////
// LfPosiDirectionType: 持仓多空方向
///////////////////////////////////
//净
#define LF_CHAR_Net             '1'
//多头
#define LF_CHAR_Long            '2'
//空头
#define LF_CHAR_Short           '3'

typedef char LfPosiDirectionType;

///////////////////////////////////
// LfPositionDateType: 持仓日期
///////////////////////////////////
//今日持仓
#define LF_CHAR_Today           '1'
//历史持仓
#define LF_CHAR_History         '2'
//两种持仓
#define LF_CHAR_Both            '3'

typedef char LfPositionDateType;

///////////////////////////////////
// LfTimeConditionType: 有效期类型
///////////////////////////////////
//立即完成，否则撤销
#define LF_CHAR_IOC             '1'
//本节有效
#define LF_CHAR_GFS             '2'
//当日有效
#define LF_CHAR_GFD             '3'
//指定日期前有效
#define LF_CHAR_GTD             '4'
//撤销前有效
#define LF_CHAR_GTC             '5'
//集合竞价有效
#define LF_CHAR_GFA             '6'
//FAK或IOC(yisheng)
#define LF_CHAR_FAK             'A'
//FOK(yisheng)
#define LF_CHAR_FOK             'O'

typedef char LfTimeConditionType;

///////////////////////////////////
// LfVolumeConditionType: 成交量类型
///////////////////////////////////
//任何数量
#define LF_CHAR_AV              '1'
//最小数量
#define LF_CHAR_MV              '2'
//全部数量
#define LF_CHAR_CV              '3'

typedef char LfVolumeConditionType;

///////////////////////////////////
// LfYsHedgeFlagType: 易盛投机保值类型
///////////////////////////////////
//保值
#define LF_CHAR_YsB             'B'
//套利
#define LF_CHAR_YsL             'L'
//无
#define LF_CHAR_YsNon           'N'
//投机
#define LF_CHAR_YsT             'T'

typedef char LfYsHedgeFlagType;

///////////////////////////////////
// LfYsOrderStateType: 易盛委托状态类型
///////////////////////////////////
//终端提交
#define LF_CHAR_YsSubmit        '0'
//已受理
#define LF_CHAR_YsAccept        '1'
//策略待触发
#define LF_CHAR_YsTriggering    '2'
//交易所待触发
#define LF_CHAR_YsExctriggering '3'
//已排队
#define LF_CHAR_YsQueued        '4'
//部分成交
#define LF_CHAR_YsPartFinished  '5'
//完全成交
#define LF_CHAR_YsFinished      '6'
//待撤消(排队临时状态)
#define LF_CHAR_YsCanceling     '7'
//待修改(排队临时状态)
#define LF_CHAR_YsModifying     '8'
//完全撤单
#define LF_CHAR_YsCanceled      '9'
//已撤余单
#define LF_CHAR_YsLeftDeleted   'A'
//指令失败
#define LF_CHAR_YsFail          'B'
//策略删除
#define LF_CHAR_YsDeleted       'C'
//已挂起
#define LF_CHAR_YsSuppended     'D'
//到期删除
#define LF_CHAR_YsDeletedForExpire 'E'
//已生效——询价成功
#define LF_CHAR_YsEffect        'F'
//已申请——行权、弃权、套利等申请成功
#define LF_CHAR_YsApply         'G'

typedef char LfYsOrderStateType;

///////////////////////////////////
// LfYsOrderTypeType: 易盛委托类型
///////////////////////////////////
//市价
#define LF_CHAR_YsMarket        '1'
//限价
#define LF_CHAR_YsLimit         '2'

typedef char LfYsOrderTypeType;

///////////////////////////////////
// LfYsPositionEffectType: 易盛开平类型
///////////////////////////////////
//平仓
#define LF_CHAR_YsClose         'C'
//不分开平
#define LF_CHAR_YsNon           'N'
//开仓
#define LF_CHAR_YsOpen          'O'
//平当日
#define LF_CHAR_YsCloseToday    'T'

typedef char LfYsPositionEffectType;

///////////////////////////////////
// LfYsSideTypeType: 易盛买卖类型
///////////////////////////////////
//双边
#define LF_CHAR_YsAll           'A'
//买入
#define LF_CHAR_YsBuy           'B'
//无
#define LF_CHAR_YsNon           'N'
//卖出
#define LF_CHAR_YsSell          'S'

typedef char LfYsSideTypeType;

///////////////////////////////////
// LfYsTimeConditionType: 易盛委托有效类型
///////////////////////////////////
//当日有效
#define LF_CHAR_YsGFD           '0'
//撤销前有效
#define LF_CHAR_YsGTC           '1'
//指定日期前有效
#define LF_CHAR_YsGTD           '2'
//FAK或IOC
#define LF_CHAR_YsFAK           '3'
//FOK
#define LF_CHAR_YsFOK           '4'

typedef char LfYsTimeConditionType;


#endif