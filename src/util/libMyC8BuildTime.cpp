#include "libMyC8BuildTime.h"

libMyC8BuildTime::libMyC8BuildTime()
: dateTime(__DATE__ " " __TIME__)
{
}

libMyC8BuildTime::~libMyC8BuildTime()
{
}

const char* libMyC8BuildTime::GetDateTime()
{
    return dateTime;
}

