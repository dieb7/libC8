#include "C8Mem.h"

C8Mem::C8Mem()
{
}

C8Mem::~C8Mem()
{
}

unsigned char C8Mem::Get(unsigned int address)
{
    if (address > 0x1FF && address < 0x1000) {
        return mem[address - 0x200];
    }
    return 0x00;
}

void C8Mem::Set(unsigned int address, unsigned char val)
{
    if (address > 0x1FF && address < 0x1000) {
        mem[address - 0x200] = val;
    }
}
