#include "C8Key.h"

C8Key::C8Key()
{
    keys = 0;
}

C8Key::~C8Key()
{
}


void C8Key::Push(unsigned char k)
{
    if (k < 16) {
        keys |= getMask(k);
    }
}

void C8Key::Release(unsigned char k)
{
    if (k < 16) {
        keys &= ~getMask(k);
    }
}

bool C8Key::Get(unsigned char k)
{
    if (k < 16) {
        return (keys & getMask(k)) > 0;
    }
    return false;
}
