#ifndef YIJINJING_CONSTANTS_H
#define YIJINJING_CONSTANTS_H

#include "YJJ_DECLARE.h"

YJJ_NAMESPACE_START

/** seed of hash function */
const uint HASH_SEED = 97;

#define JOURNAL_SHORT_NAME_MAX_LENGTH 30
#define JOURNAL_FOLDER_MAX_LENGTH     100

/** seed of hash function */
const long TIME_FROM_FIRST = 0;
const long TIME_TO_LAST = -1;

/** size related */
const int KB = 1024;
const int MB = 1024 * 1024;
const int JOURNAL_PAGE_SIZE = 128 * MB;
const int PAGE_MIN_HEADROOM = 2 * MB;

YJJ_NAMESPACE_END

#endif // YIJINJING_CONSTANTS_H