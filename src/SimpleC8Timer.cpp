#include "SimpleC8Timer.h"
#include <sys/time.h>
#include <cstddef>

SimpleC8Timer::SimpleC8Timer()
{
    struct timeval te;
    gettimeofday(&te, NULL);

    timerValue = 0;
    prev = te.tv_sec*1000LL + te.tv_usec/1000;
}

SimpleC8Timer::~SimpleC8Timer()
{
}

void SimpleC8Timer::UpdateValue()
{
    if (timerValue) {
        struct timeval te;
        gettimeofday(&te, NULL);
        long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000;
        if (milliseconds - prev > 17) {
            timerValue--;
            prev = milliseconds;
        }
    }
}
