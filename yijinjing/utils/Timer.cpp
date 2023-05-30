#include "Timer.h"
#include <chrono>

USING_YJJ_NAMESPACE

boost::shared_ptr<NanoTimer> NanoTimer::m_ptr = boost::shared_ptr<NanoTimer>(nullptr);

NanoTimer* NanoTimer::getInstance()
{
    if (m_ptr.get() == nullptr)
    {
        m_ptr = boost::shared_ptr<NanoTimer>(new NanoTimer());
    }
    return m_ptr.get();
}

NanoTimer::NanoTimer()
{
    int unix_second_num = std::chrono::seconds(std::time(NULL)).count();
    int tick_second_num = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now().time_since_epoch()
    ).count();

    secDiff = (unix_second_num - tick_second_num) * NANOSECONDS_PER_SECOND;
}

long NanoTimer::getNano()
{
    long _nano = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::high_resolution_clock::now().time_since_epoch()
    ).count();
    return _nano + secDiff;
}