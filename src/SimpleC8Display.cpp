#include "SimpleC8Display.h"

SimpleC8Display::SimpleC8Display()
{
    Clear();
    drawFlag = false;
}

SimpleC8Display::~SimpleC8Display()
{
}

void SimpleC8Display::Clear()
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 32; j++) {
            mem[i][j] = 0;
        }
    }
    drawFlag = true;
}

bool SimpleC8Display::Draw(unsigned char x, unsigned char y, unsigned char data)
{
    bool flip0 = false;
    bool flip1 = false;

    if (x < 64 && y < 32) {
        unsigned char xbyte = x / 8;
        unsigned char xbit = x % 8;

        unsigned char temp = ~mem[xbyte][y];

        mem[xbyte][y] ^= data >> xbit;

        flip0 = (temp | mem[xbyte][y]) < 0xFF;

        if (xbyte + 1 < 8) {
            temp = ~mem[xbyte + 1][y];
            mem[xbyte + 1][y] ^= data << (8 - xbit);
            flip1 = (temp | mem[xbyte + 1][y]) < 0xFF;
        }
    }
    drawFlag = true;

    return flip0 | flip1;
}

void SimpleC8Display::setPixel(unsigned char x, unsigned char y, bool val)
{
    unsigned char xbyte = x / 8;
    unsigned char xbit = x % 8;
    unsigned char temp = 0;

    if (val) {
        unsigned char mask = 0x80 >> xbit;
        temp = mask | mem[xbyte][y];
    } else {
        unsigned char mask = ~(0x80 >> xbit);
        temp = mask & mem[xbyte][y];
    }
    mem[xbyte][y] = temp;
}

bool SimpleC8Display::getPixel(unsigned char x, unsigned char y)
{
    unsigned char xbyte = x / 8;
    unsigned char xbit = x % 8;
    unsigned char mask = 0x80 >> xbit;
    unsigned char temp = mem[xbyte][y] & mask;
    return temp > 0;
}
