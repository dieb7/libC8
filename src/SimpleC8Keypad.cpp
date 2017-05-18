#include "SimpleC8Keypad.h"

SimpleC8Keypad::SimpleC8Keypad()
{
    keys = 0;
}

SimpleC8Keypad::~SimpleC8Keypad()
{
}


void SimpleC8Keypad::Push(unsigned char k)
{
    if (k < 16) {
        keys |= getMask(k);
    }
}

void SimpleC8Keypad::Release(unsigned char k)
{
    if (k < 16) {
        keys &= ~getMask(k);
    }
}

bool SimpleC8Keypad::Get(unsigned char k)
{
    if (k < 16) {
        return (keys & getMask(k)) > 0;
    }
    return false;
}
