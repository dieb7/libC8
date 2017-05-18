#ifndef D_Simple8Key_H
#define D_Simple8Key_H

#include "C8Keypad.h"

///////////////////////////////////////////////////////////////////////////////
//
//  C8Key is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////

class SimpleC8Keypad : public C8Keypad
{
public:
    SimpleC8Keypad();
    virtual ~SimpleC8Keypad();

    void Push(unsigned char k);
    void Release(unsigned char k);
    bool Get(unsigned char k);

    void Clear()
    {
        keys = 0;
    };

private:

    unsigned short keys;

    unsigned short getMask(unsigned char k)
    {
        return 0x1 << k;
    }

};

#endif  // D_Simple8Key_H
