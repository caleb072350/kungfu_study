#ifndef LONGFIST_TRANSFER_M_H
#define LONGFIST_TRANSFER_M_H

#include <cstdio>
/*
 * 150006320 -> '15:00:06'
 */
inline void UpdateTimeFromMilSecInt(char* time_str, int time_int)
{
    time_int /= 1000;
    sprintf(time_str, "%02d:%02d:%02d", time_int / 10000, time_int / 100 % 100, time_int % 100);
}

/*
 * 150006320 -> 320
 */
inline int UpdateMillisecFromMilSecInt(int& mil_sec, int time_int)
{
    mil_sec = time_int % 1000;
}

#endif