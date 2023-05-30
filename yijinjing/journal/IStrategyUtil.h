/** IStrategyUtil
 *  strategy utilities  abstraction
*/
#ifndef PROJECT_ISTRATEGYUTIL_H
#define PROJECT_ISTRATEGYUTIL_H

#include "YJJ_DECLARE.h"

YJJ_NAMESPACE_START

/** interface class */
class IStrategyUtil
{
public:
    /** register strategy in paged service */
    virtual bool register_strategy(int& requestIdStart, int& requestIdEnd) = 0;
    /** request kungfu trade engine login */ 
    virtual bool td_connect(short source) = 0;
    /** subscribe market data */
    virtual bool md_subscribe(const vector<string>& tickers, short source, short msg_type) = 0;
};

YJJ_NAMESPACE_END

#endif