#include "C8Stack.h"

C8Stack::C8Stack()
{
    sp = -1;
    for (int i = 0; i < 16; i++) {
        st[i] = 0;
    }
}

C8Stack::~C8Stack()
{
}

bool C8Stack::push(unsigned short val)
{
    if (sp < 15) {
        st[++sp] = val;
        return true;
    }
    return false;
}

unsigned short C8Stack::pop()
{
    if (sp > -1) {
        return st[sp--];
    }
    return 0;
}
