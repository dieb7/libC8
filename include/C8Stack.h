#ifndef D_C8Stack_H
#define D_C8Stack_H

///////////////////////////////////////////////////////////////////////////////
//
//  C8Stack is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////

class C8Stack
{
public:
    C8Stack();
    virtual ~C8Stack();

    bool push(unsigned short val);
    unsigned short pop();

private:

    int sp;
    unsigned short st[16];

};

#endif  // D_C8Stack_H
