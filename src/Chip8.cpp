#include "Chip8.h"

void clearMem(unsigned char * buff, unsigned int buffSize)
{
    for (unsigned int i = 0; i < buffSize; i++) {
        buff[i] = 0;
    }
}

void clearMem(unsigned short * buff, unsigned int buffSize)
{
    for (unsigned int i = 0; i < buffSize; i++) {
        buff[i] = 0;
    }
}

Chip8::Chip8()
{
    st = NULL;

    pc = 0x200;
    opcode = 0;
    I = 0;

    clearMem(gfx, sizeof(gfx) / sizeof(gfx[0]));
    clearMem(key, sizeof(key) / sizeof(key[0]));
    clearMem(mem, sizeof(mem) / sizeof(mem[0]));

    delayTimer = 0;
    soundTimer = 0;
}

Chip8::~Chip8()
{

}

unsigned char Chip8::getMem(unsigned int address)
{
    if (address > 0x1FF && address < 0x1000) {
        return mem[address - 0x200];
    }

    return 0;
}

void Chip8::setMem(unsigned int address, unsigned char val)
{
    if (address > 0x1FF && address < 0x1000) {
        mem[address - 0x200] = val;
    }
}

unsigned char Chip8::getGfx(unsigned int address)
{
    if (address < 2048) {
        return gfx[address];
    }
    return 0;
}

void Chip8::setGfx(unsigned int address, unsigned char val)
{
    if (address < 2048) {
        gfx[address] = val;
    }
}

void Chip8::emulateCycle()
{
    // fetch opcode
    opcode = (unsigned short)(getMem(pc) << 8 | getMem(pc + 1));

    // decode opcode
    switch(opcode & 0xF000) {
    case 0x0000:
        if (opcode == 0x00E0) {
            clearMem(gfx, sizeof(gfx) / sizeof(gfx[0]));
        } else if (opcode == 0x00EE) {
            pc = st->pop();
            pc += 2;
        }
        break;
    case 0x1000:
        pc = opcode & 0x0FFF;
        break;
    case 0x2000:
        st->push(pc);
        pc = opcode & 0x0FFF;
        break;
    case 0x3000:
        if (V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF)) {
            pc += 2;
        }
        pc += 2;
        break;
    default:
        opcode = 0;
    }
}
