#ifndef D_SIMPLEC8Timer_H
#define D_SIMPLEC8Timer_H

#include "C8Timer.h"

///////////////////////////////////////////////////////////////////////////////
//
//  C8Timer is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////

class SimpleC8Timer : public C8Timer
{
public:
    SimpleC8Timer();
    virtual ~SimpleC8Timer();

    void SetValue(unsigned char v)
    {
        timerValue = v;
    };
    unsigned char GetValue()
    {
        return timerValue;
    };

    void UpdateValue();

private:
    long long prev;
    unsigned char timerValue;
};

#endif  // D_SIMPLEC8Timer_H
