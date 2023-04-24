#include "transfer_m.h"

int main() {
    char buf[100] = {0};
    int test_int = 150006320;
    UpdateTimeFromMilSecInt(buf, test_int);
    printf("time: %s\n", buf);

    int  mil_sec = 0;
    printf("test_int: %d\n", test_int);
    UpdateMillisecFromMilSecInt(mil_sec, test_int);
    printf("mil_sec: %d\n", mil_sec);
}