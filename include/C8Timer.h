#ifndef D_C8Timer_H
#define D_C8Timer_H

///////////////////////////////////////////////////////////////////////////////
//
//  C8Timer is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////

class C8Timer
{
public:
    explicit C8Timer();
    virtual ~C8Timer();

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

    C8Timer(const C8Timer&);
    C8Timer& operator=(const C8Timer&);

};

#endif  // D_C8Timer_H
