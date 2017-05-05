#ifndef D_Chip8_H
#define D_Chip8_H

#include "C8Stack.h"

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

    void setStack(C8Stack * s) {st = s;};

    void emulateCycle();

    unsigned char getMem(unsigned int address);
    void setMem(unsigned int address, unsigned char val);

    unsigned short getPc() {return pc;};
    void setPc(unsigned short val) {pc = val;};

    unsigned char getGfx(unsigned int address);
    void setGfx(unsigned int address, unsigned char val);

    void stackPush(unsigned short val);
    unsigned short stackPop();

private:

    Chip8(const Chip8&);
    Chip8& operator=(const Chip8&);

    unsigned char  mem[0xE00];

    unsigned short pc;
    unsigned char  gfx[2048];
    unsigned char  key[16];
    unsigned short opcode;
    unsigned short I;

    unsigned char  V[16];
    C8Stack * st;
    unsigned char  delayTimer;
    unsigned char  soundTimer;

//    void (Chip8::*ops)(void);

};

#endif  // D_Chip8_H
