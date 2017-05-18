#ifndef C8KEYPAD_H
#define C8KEYPAD_H


class C8Keypad
{
public:
    C8Keypad();
    virtual ~C8Keypad();

    virtual void Push(unsigned char k) = 0;
    virtual void Release(unsigned char k) = 0;
    virtual bool Get(unsigned char k) = 0;

    virtual void Clear() = 0;

protected:

private:
};

#endif // C8KEYPAD_H
