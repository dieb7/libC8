#ifndef D_Chip8_H
#define D_Chip8_H

#include "C8Mem.h"
#include "C8Stack.h"
#include "C8Display.h"
#include "C8Keypad.h"
#include "C8Timer.h"
#include "C8Random.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Chip8 is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////

class C8
{
public:
    explicit C8();
    virtual ~C8();

    void setMem(C8Mem * m)
    {
        mem = m;
    };

    void setStack(C8Stack * s)
    {
        st = s;
    };

    void setDisplay(C8Display * d)
    {
        disp = d;
    };

    void setKey(C8Keypad * k)
    {
        key = k;
    };

    void setDelayTimer(C8Timer * t)
    {
        delayTimer = t;
    }

    void setSoundTimer(C8Timer * t)
    {
        soundTimer = t;
    }

    void setRandom(C8Random * r)
    {
        random = r;
    }

    void emulateCycle();

    unsigned short getPc()
    {
        return pc;
    };
    void setPc(unsigned short val)
    {
        pc = val;
    };

    unsigned char getVn(unsigned int index)
    {
        return V[0x000F & index];
    };
    void setVn(unsigned int index, unsigned char val)
    {
        V[0x000F & index] = val;
    };

    void setI(unsigned short val)
    {
        I = val & 0x0FFF;
    };
    unsigned short getI()
    {
        return I;
    };

private:

    C8(const C8&);
    C8& operator=(const C8&);

    C8Mem * mem;
    C8Display * disp;
    C8Keypad * key;
    C8Stack * st;
    C8Timer * delayTimer;
    C8Timer * soundTimer;
    C8Random * random;

    unsigned short pc;
    unsigned short opcode;
    unsigned short I;
    unsigned char V[16];
};

#endif  // D_Chip8_H
