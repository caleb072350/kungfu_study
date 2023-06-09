#ifndef LONGFIST_UTIL_CTP_H
#define LONGFIST_UTIL_CTP_H

#include "../api/ctp/v6.3.6_20160606/include/ThostFtdcUserApiStruct.h"
#include "LFDataStruct.h"
#define KUNGFU_LF_CTP
#include "longfist/transfer_m.h"

inline struct LFMarketDataField parseFrom(const struct CThostFtdcDepthMarketDataField& ori)
{
    struct LFMarketDataField res = {};
    memcpy(res.TradingDay, ori.TradingDay, 9);
    memcpy(res.InstrumentID, ori.InstrumentID, 31);
    memcpy(res.ExchangeID, ori.ExchangeID, 9);
    memcpy(res.ExchangeInstID, ori.ExchangeInstID, 64);
    res.LastPrice = ori.LastPrice;
    res.PreSettlementPrice = ori.PreSettlementPrice;
    res.PreClosePrice = ori.PreClosePrice;
    res.PreOpenInterest = ori.PreOpenInterest;
    res.OpenPrice = ori.OpenPrice;
    res.HighestPrice = ori.HighestPrice;
    res.LowestPrice = ori.LowestPrice;
    res.Volume = ori.Volume;
    res.Turnover = ori.Turnover;
    res.OpenInterest = ori.OpenInterest;
    res.ClosePrice = ori.ClosePrice;
    res.SettlementPrice = ori.SettlementPrice;
    res.UpperLimitPrice = ori.UpperLimitPrice;
    res.LowerLimitPrice = ori.LowerLimitPrice;
    res.PreDelta = ori.PreDelta;
    res.CurrDelta = ori.CurrDelta;
    memcpy(res.UpdateTime, ori.UpdateTime, 9);
    res.UpdateMillisec = ori.UpdateMillisec;
    res.BidPrice1 = ori.BidPrice1;
    res.BidVolume1 = ori.BidVolume1;
    res.AskPrice1 = ori.AskPrice1;
    res.BidPrice2 = ori.BidPrice2;
    res.BidVolume2 = ori.BidVolume2;
    res.AskPrice2 = ori.AskPrice2;
    res.AskVolume2 = ori.AskVolume2;
    res.BidPrice3 = ori.BidPrice3;
    res.BidVolume3 = ori.BidVolume3;
    res.AskPrice3 = ori.AskPrice3;
    res.AskVolume3 = ori.AskVolume3;
    res.BidPrice4 = ori.BidPrice4;
    res.BidVolume4 = ori.BidVolume4;
    res.AskPrice4  = ori.AskPrice4;
    res.AskVolume4 = ori.AskVolume4;
    res.BidPrice5 = ori.BidPrice5;
    res.BidVolume5 = ori.BidVolume5;
    res.AskPrice5 = ori.AskPrice5;
    res.AskVolume5 = ori.AskVolume5;
    return res;
}

inline struct CThostFtdcQryInvestorPositionField parseTo(const struct LFQryPositionField& lf) {
    struct CThostFtdcQryInvestorPositionField res = {};
    memcpy(res.BrokerID, lf.BrokerID, 11);
    memcpy(res.InvestorID, lf.InvestorID, 13);
    memcpy(res.InstrumentID, lf.InstrumentID, 31);
    return res;
}

inline struct LFRspPositionField parseFrom(const struct CThostFtdcInvestorPositionField& ori) {
    struct LFRspPositionField res = {};
    memcpy(res.InstrumentID, ori.InstrumentID, 31);
    res.YdPosition = (int)(ori.Position - ori.TodayPosition);
    res.Position = ori.Position;
    memcpy(res.BrokerID, ori.BrokerID, 11);
    memcpy(res.InvestorID, ori.InvestorID, 13);
    res.PositionCost = ori.PositionCost;
    res.HedgeFlag = ori.HedgeFlag;
    res.PosiDirection = ori.PosiDirection;
    return res;
}


inline struct LFInputOrderField parseFrom(const struct CThostFtdcInputOrderField& ori) {
    struct LFInputOrderField res = {};
    memcpy(res.BrokerID, ori.BrokerID, 11);
    memcpy(res.UserID, ori.UserID, 16);
    memcpy(res.InvestorID, ori.InvestorID, 13);
    memcpy(res.BusinessUnit, ori.BusinessUnit, 21);
    memcpy(res.ExchangeID, ori.ExchangeID, 9);
    memcpy(res.InstrumentID, ori.InstrumentID, 31);
    memcpy(res.OrderRef, ori.OrderRef, 13);
    res.LimitPrice = ori.LimitPrice;
    res.Volume = ori.VolumeTotalOriginal;
    res.MinVolume = ori.MinVolume;
    res.TimeCondition = ori.TimeCondition;
    res.VolumeCondition = ori.VolumeCondition;
    res.OrderPriceType= ori.OrderPriceType;
    res.Direction = ori.Direction;
    res.OffsetFlag = ori.CombHedgeFlag[0];
    res.HedgeFlag = ori.CombHedgeFlag[0];
    res.ForceCloseReason = ori.ForceCloseReason;
    res.StopPrice = ori.StopPrice;
    res.IsAutoSuspend = ori.IsAutoSuspend;
    res.ContingentCondition = ori.ContingentCondition;
    return res;
}

inline struct CThostFtdcInputOrderField parseTo(const struct LFInputOrderField& lf) {
    struct CThostFtdcInputOrderField res = {};
    memcpy(res.BrokerID, lf.BrokerID, 11);
    memcpy(res.UserID, lf.UserID, 16);
    memcpy(res.InvestorID, lf.InvestorID, 13);
    memcpy(res.BusinessUnit, lf.BusinessUnit, 21);
    memcpy(res.ExchangeID, lf.ExchangeID, 9);
    memcpy(res.InstrumentID, lf.InstrumentID, 31);
    memcpy(res.OrderRef, lf.OrderRef, 13);
    res.LimitPrice = lf.LimitPrice;
    res.VolumeTotalOriginal = lf.Volume;
    res.MinVolume = lf.MinVolume;
    res.TimeCondition = lf.TimeCondition;
    res.VolumeCondition = lf.VolumeCondition;
    res.OrderPriceType = lf.OrderPriceType;
    res.Direction = lf.Direction;
    res.CombOffsetFlag[0] = lf.OffsetFlag;
    res.CombHedgeFlag[0] = lf.HedgeFlag;
    res.ForceCloseReason = lf.ForceCloseReason;
    res.StopPrice = lf.StopPrice;
    res.IsAutoSuspend = lf.IsAutoSuspend;
    res.ContingentCondition = lf.ContingentCondition;
    return res;
}

inline struct LFRtnOrderField parseFrom(const struct CThostFtdcOrderField& ori) {
    struct LFRtnOrderField res = {};
    memcpy(res.BrokerID, ori.BrokerID, 11);
    memcpy(res.UserID, ori.UserID, 16);
    memcpy(res.ParticipantID, ori.ParticipantID, 11);
    memcpy(res.InvestorID, ori.InvestorID, 13);
    memcpy(res.BusinessUnit, ori.BusinessUnit, 21);
    memcpy(res.InstrumentID, ori.InstrumentID, 31);
    memcpy(res.OrderRef, ori.OrderRef, 13);
    memcpy(res.ExchangeID, ori.ExchangeID, 9);
    res.LimitPrice = ori.LimitPrice;
    res.VolumeTraded = ori.VolumeTraded;
    res.VolumeTotal = ori.VolumeTotal;
    res.VolumeTotalOriginal = ori.VolumeTotalOriginal;
    res.TimeCondition = ori.TimeCondition;
    res.VolumeCondition = ori.VolumeCondition;
    res.OrderPriceType = ori.OrderPriceType;
    res.Direction = ori.Direction;
    res.OffsetFlag = ori.CombOffsetFlag[0];
    res.HedgeFlag = ori.CombOffsetFlag[0];
    res.OrderStatus = ori.OrderStatus;
    res.RequestID = ori.RequestID;
    return res;
}


inline struct LFRtnTradeField parseFrom(const struct CThostFtdcTradeField& ori) {
    struct LFRtnTradeField res = {};
    memcpy(res.BrokerID, ori.BrokerID, 11);
    memcpy(res.UserID, ori.UserID, 16);
    memcpy(res.InvestorID, ori.InvestorID, 13);
    memcpy(res.BusinessUnit, ori.BusinessUnit, 21);
    memcpy(res.InstrumentID, ori.InstrumentID, 31);
    memcpy(res.OrderRef, ori.OrderRef, 13);
    memcpy(res.ExchangeID, ori.ExchangeID, 9);
    memcpy(res.TradeID, ori.TradeID, 21);
    memcpy(res.OrderSysID, ori.OrderSysID, 21);
    memcpy(res.ParticipantID, ori.ParticipantID, 11);
    memcpy(res.ClientID, ori.ClientID, 11);
    res.Price = ori.Price;
    res.Volume = ori.Volume;
    memcpy(res.TradingDay, ori.TradingDay, 13);
    memcpy(res.TradeTime, ori.TradeTime, 9);
    res.Direction = ori.Direction;
    res.OffsetFlag = ori.OffsetFlag;
    res.HedgeFlag = ori.HedgeFlag;
    return res;
}

inline struct LFOrderActionField parseFrom(const struct CThostFtdcInputOrderActionField& ori) {
    struct LFOrderActionField res = {};
    memcpy(res.BrokerID, ori.BrokerID, 11);
    memcpy(res.InvestorID, ori.InvestorID, 13);
    memcpy(res.InstrumentID, ori.InstrumentID, 31);
    memcpy(res.ExchangeID, ori.ExchangeID, 9);
    memcpy(res.UserID, ori.UserID, 16);
    memcpy(res.OrderRef, ori.OrderRef, 13);
    memcpy(res.OrderSysID, ori.OrderSysID, 21);
    res.RequestID = ori.RequestID;
    res.ActionFlag = ori.ActionFlag;
    res.LimitPrice = ori.LimitPrice;
    res.VolumeChange = ori.VolumeChange;
    return res;
}

inline struct CThostFtdcInputOrderActionField parseTo(const struct LFOrderActionField& lf) {
    struct CThostFtdcInputOrderActionField res = {};
    memcpy(res.BrokerID, lf.BrokerID, 11);
    memcpy(res.InvestorID, lf.InvestorID, 13);
    memcpy(res.InstrumentID, lf.InstrumentID, 31);
    memcpy(res.ExchangeID, lf.ExchangeID, 9);
    memcpy(res.UserID, lf.UserID, 16);
    memcpy(res.OrderRef, lf.OrderRef, 13);
    memcpy(res.OrderSysID, lf.OrderSysID, 21);
    res.RequestID = lf.RequestID;
    res.ActionFlag = lf.ActionFlag;
    res.LimitPrice = lf.LimitPrice;
    res.VolumeChange = lf.VolumeChange;
    return res;
}

inline struct CThostFtdcQryTradingAccountField parseTo(const struct LFQryAccountField& lf) {
    struct CThostFtdcQryTradingAccountField res = {};
    memcpy(res.BrokerID, lf.BrokerID, 11);
    memcpy(res.InvestorID, lf.InvestorID, 13);
    return res;
}

inline struct LFRspAccountField parseFrom(const struct CThostFtdcTradingAccountField& ori) {
    struct LFRspAccountField res = {};
    memcpy(res.BrokerID, ori.BrokerID, 11);
    memcpy(res.InvestorID, ori.AccountID, 13);
    res.PreMortgage = ori.PreMortgage;
    res.PreCredit = ori.PreCredit;
    res.PreDeposit = ori.PreDeposit;
    res.PreBalance = ori.PreBalance;
    res.PreMargin = ori.PreMargin;
    res.Deposit = ori.Deposit;
    res.Withdraw = ori.Withdraw;
    res.FrozenMargin = ori.FrozenMargin;
    res.FrozenCash = ori.FrozenCash;
    res.FrozenCommission = ori.FrozenCommission;
    res.CurrMargin = ori.CurrMargin;
    res.CashIn = ori.CashIn;
    res.Commission = ori.Commission;
    res.CloseProfit = ori.CloseProfit;
    res.PositionProfit = ori.PositionProfit;
    res.Balance = ori.Balance;
    res.Available = ori.Available;
    res.WithdrawQuota = ori.WithdrawQuota;
    res.Reserve = ori.Reserve;
    memcpy(res.TradingDay, ori.TradingDay, 9);
    res.Credit = ori.Credit;
    res.Mortgage = ori.Mortgage;
    res.ExchangeMargin = ori.ExchangeMargin;
    res.DeliveryMargin = ori.DeliveryMargin;
    res.ExchangeDeliverMargin = ori.ExchangeDeliveryMargin;
    res.ReserveBalance = ori.ReserveBalance;
    res.Equity = ori.PreBalance - ori.PreCredit - ori.PreMortgage + ori.Mortgage - ori.Withdraw + ori.Deposit + ori.CloseProfit + ori.PositionProfit + ori.CashIn - ori.Commission;
    return res;
}

#endif