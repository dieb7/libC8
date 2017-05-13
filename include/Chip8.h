#ifndef D_Chip8_H
#define D_Chip8_H

#include "C8Stack.h"
#include "C8Display.h"
#include "C8Key.h"

///////////////////////////////////////////////////////////////////////////////
//
//  Chip8 is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////

class Chip8
{
public:
    explicit Chip8();
    virtual ~Chip8();

    void setStack(C8Stack * s)
    {
        st = s;
    };

    void setDisplay(C8Display * d)
    {
        disp = d;
    };

    void setKey(C8Key * k)
    {
        key = k;
    };

    void emulateCycle();

    unsigned char getMem(unsigned int address);
    void setMem(unsigned int address, unsigned char val);

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

    unsigned char getDelayTimer()
    {
        return delayTimer;
    };
    void setDelayTimer(unsigned char d)
    {
        delayTimer = d;
    };

    unsigned char getSoundTimer()
    {
        return soundTimer;
    };
    void setSoundTimer(unsigned char s)
    {
        soundTimer = s;
    };

private:

    Chip8(const Chip8&);
    Chip8& operator=(const Chip8&);

    unsigned char  mem[0xE00];

    unsigned short pc;
    C8Display * disp;
    C8Key * key;
    unsigned short opcode;
    unsigned short I;

    unsigned char  V[16];
    C8Stack * st;
    unsigned char  delayTimer;
    unsigned char  soundTimer;
};

#endif  // D_Chip8_H
