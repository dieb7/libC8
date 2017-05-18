#ifndef C8TIMER_H
#define C8TIMER_H


class C8Timer
{
public:
    C8Timer();
    virtual ~C8Timer();

    virtual void SetValue(unsigned char v) = 0;

    virtual unsigned char GetValue() = 0;

    virtual void UpdateValue() = 0;

protected:

private:
};

#endif // C8TIMER_H
