/**
 * Provide basic nano time and time transformation
*/

#ifndef YIJINJING_TIMER_H
#define YIJINJING_TIMER_H

#include "YJJ_DECLARE.h"

YJJ_NAMESPACE_START

const long MILLISECONDS_PER_SECOND = 1000;
const long MICROSECONDS_PER_MILLISECOND = 1000;
const long NANOSECONDS_PER_MICROSECOND = 1000;

const long MICROSECONDS_PER_SECOND = MICROSECONDS_PER_MILLISECOND * MILLISECONDS_PER_SECOND;
const long NANOSECONDS_PER_MILLISECOND = NANOSECONDS_PER_MICROSECOND * MICROSECONDS_PER_MILLISECOND;
const long NANOSECONDS_PER_SECOND = NANOSECONDS_PER_MILLISECOND * MILLISECONDS_PER_SECOND;

const int SECONDS_PER_MINUTE = 60;
const int MINUTES_PER_HOUR = 60;
const int HOURS_PER_DAY = 24;
const int SECONDS_PER_HOUR = SECONDS_PER_MINUTE * MINUTES_PER_HOUR;

const long MILLISECONDS_PER_MINUTE = MILLISECONDS_PER_SECOND * SECONDS_PER_MINUTE;
const long NANOSECONDS_PER_MINUTE = NANOSECONDS_PER_SECOND * SECONDS_PER_MINUTE;
const long NANOSECONDS_PER_HOUR = NANOSECONDS_PER_SECOND * SECONDS_PER_HOUR;
const long NANOSECONDS_PER_DAY = NANOSECONDS_PER_HOUR * HOURS_PER_DAY; 

/**
 * timer for nanosecond, main class
*/
class NanoTimer
{
public:
    /** return current nano time: unix-timestamp * 1e9 + nano-part */
    long getNano();
    /** singleton */
    static NanoTimer* getInstance();

private:
    NanoTimer();
    /** singleton */
    static boost::shared_ptr<NanoTimer> m_ptr;
    /** object to be updated every time called */
    long long int secDiff;
};

/**
 * util function to utilize NanoTimer
 * @return current nano time in long (unix-timestamp * 1e9 + nano-part)
*/
inline long getNanoTime() {
    return NanoTimer::getInstance()->getNano();
}

/**
 *  parse struct tm to nano time
 * @param _tm ctime struct
 * @return nano time in long
 */
inline long parseTm(struct tm _tm) {
    return timelocal(&_tm) * NANOSECONDS_PER_SECOND;
}
YJJ_NAMESPACE_END
#endif // YIJINJING_TIMER_H