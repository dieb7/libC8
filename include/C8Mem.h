#ifndef D_C8Mem_H
#define D_C8Mem_H

///////////////////////////////////////////////////////////////////////////////
//
//  C8Mem is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////

class C8Mem
{
public:
    explicit C8Mem();
    virtual ~C8Mem();

    unsigned char Get(unsigned int address);
    void Set(unsigned int address, unsigned char val);

private:

    C8Mem(const C8Mem&);
    C8Mem& operator=(const C8Mem&);

    unsigned char  mem[0xE00];

};

#endif  // D_C8Mem_H
