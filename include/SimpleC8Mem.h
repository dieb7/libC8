#ifndef D_SimpleC8Mem_H
#define D_SimpleC8Mem_H

#include "C8Mem.h"

///////////////////////////////////////////////////////////////////////////////
//
//  SimpleC8Mem is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////

class SimpleC8Mem : public C8Mem
{
public:
    SimpleC8Mem();
    virtual ~SimpleC8Mem();

    unsigned char Get(unsigned int address);
    void Set(unsigned int address, unsigned char val);

private:

    unsigned char  mem[0xE00];

};

#endif  // D_SimpleC8Mem_H
