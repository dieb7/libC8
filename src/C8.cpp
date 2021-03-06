#include "C8.h"

void clearMem(unsigned char * buff, unsigned int buffSize)
{
    for (unsigned int i = 0; i < buffSize; i++) {
        buff[i] = 0;
    }
}

C8::C8()
{
    pc = 0x200;
    opcode = 0;
    I = 0;

//    mem = nullptr;
//    disp = nullptr;
//    key = nullptr;
//    st = nullptr;
//    delayTimer = nullptr;
//    soundTimer = nullptr;
}

C8::~C8()
{

}

void C8::emulateCycle()
{
    // fetch opcode
    opcode = (unsigned short)(mem->Get(pc) << 8 | mem->Get(pc + 1));

    // decode opcode
    switch(opcode & 0xF000) {
    case 0x0000:
        if (opcode == 0x00E0) {
            disp->Clear();
        } else if (opcode == 0x00EE) {
            pc = st->pop();
        }
        break;
    case 0x1000:
        pc = opcode & 0x0FFF;
        pc -= 2;
        break;
    case 0x2000:
        st->push(pc);
        pc = opcode & 0x0FFF;
        pc -= 2;
        break;
    case 0x3000:
        if (V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF)) {
            pc += 2;
        }
        break;
    case 0x4000:
        if (V[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF)) {
            pc += 2;
        }
        break;
    case 0x5000:
        if (V[(opcode & 0x0F00) >> 8] == V[(opcode & 0x00F0) >> 4]) {
            pc += 2;
        }
        break;
    case 0x6000:
        V[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
        break;
    case 0x7000:
        V[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
        break;
    case 0x8000:
        switch (opcode & 0x000F) {
        case 0x0:
            V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4] ;
            break;
        case 0x1:
            V[(opcode & 0x0F00) >> 8] |= V[(opcode & 0x00F0) >> 4] ;
            V[0xF] = 0;
            break;
        case 0x2:
            V[(opcode & 0x0F00) >> 8] &= V[(opcode & 0x00F0) >> 4] ;
            V[0xF] = 0;
            break;
        case 0x3:
            V[(opcode & 0x0F00) >> 8] ^= V[(opcode & 0x00F0) >> 4] ;
            V[0xF] = 0;
            break;
        case 0x4: {
            unsigned int x = (opcode & 0x0F00) >> 8;
            unsigned int y = (opcode & 0x00F0) >> 4;
            unsigned int temp = V[x] + V[y];
            V[x] = temp & 0x00FF;
            V[0xF] = (temp > 0xFF) ? 1 : 0;
        }
        break;
        case 0x5: {
            unsigned int x = (opcode & 0x0F00) >> 8;
            unsigned int y = (opcode & 0x00F0) >> 4;
            unsigned int temp = V[x] - V[y];
            V[x] = temp & 0x00FF;
            V[0xF] = (temp > 0xFF) ? 1 : 0;
        }
        break;
        case 0x6: {
            unsigned char x = (opcode & 0x0F00) >> 8;
            V[0xF] = (V[x] & 0x01);
            V[x] = V[x] >> 1;
        }
        break;
        case 0x7: {
            unsigned int x = (opcode & 0x0F00) >> 8;
            unsigned int y = (opcode & 0x00F0) >> 4;
            unsigned int temp = V[y] - V[x];
            V[x] = temp & 0x00FF;
            V[0xF] = (temp > 0xFF) ? 1 : 0;
        }
        break;
        case 0xE: {
            unsigned char x = (opcode & 0x0F00) >> 8;
            V[0xF] = (V[x] & 0x80) >> 7;
            V[x] = V[x] << 1;
        }
        break;
        default:
            break;
        }
        break;
    case 0x9000:
        if (V[(opcode & 0x0F00) >> 8] != V[(opcode & 0x00F0) >> 4]) {
            pc += 2;
        }
        break;
    case 0xA000:
        I = opcode & 0x0FFF;
        break;
    case 0xB000:
        pc = (opcode & 0x0FFF) + V[0];
        pc -= 2;
        break;
    case 0xC000:
        V[(opcode & 0x0F00) >> 8] = (random->Gen() % 0xFF) & (opcode & 0x00FF);
        break;
    case 0xD000: {
        unsigned int x = (opcode & 0x0F00) >> 8;
        unsigned int y = (opcode & 0x00F0) >> 4;
        unsigned int n = (opcode & 0x000F);

        bool flip = false;

        for (unsigned int i = 0; i < n; i++) {
            flip |= disp->Draw(V[x], V[y] + i, mem->Get(I + i));
        }

        V[0xF] = flip ? 1 : 0;
    }
    break;
    case 0xE000: {
        switch(opcode & 0x00FF) {
        case 0x009E:
            if (key->Get(getVn((opcode & 0x0F00) >> 8))) {
                pc += 2;
            }
            break;
        case 0x00A1:
            if (!key->Get(getVn((opcode & 0x0F00) >> 8))) {
                pc += 2;
            }
            break;
        default:
            break;
        }
    }
    break;
    case 0xF000:
        switch(opcode & 0x00FF) {
        case 0x0007:
            setVn((opcode & 0x0F00) >> 8, delayTimer->GetValue());
            break;
        case 0x000A: {
            int i = 0;
            for (; i < 0xF; i++) {
                if (key->Get(i)) {
                    setVn((opcode & 0x0F00) >> 8, i);
                    break;
                }
            }
            if (i == 0xF) {
                pc -= 2;
            }
        }
        break;
        case 0x0015:
            delayTimer->SetValue(getVn((opcode & 0x0F00) >> 8));
            break;
        case 0x0018:
            soundTimer->SetValue(getVn((opcode & 0x0F00) >> 8));
            break;
        case 0x001E: {
            unsigned int temp = I + getVn((opcode & 0x0F00) >> 8);
            I = temp & 0xFFF;
            if (temp > 0xFFF) {
                V[0xF] = 0x1;
            }
        }
        break;
        case 0x0029:
            I = getVn((opcode & 0x0F00) >> 8) * 5;
            break;
        case 0x0033: {
            unsigned char temp = V[(opcode & 0x0F00) >> 8];
            mem->Set(I, temp / 100);
            mem->Set(I + 1, (temp / 10) % 10);
            mem->Set(I + 2, (temp % 100) % 10);
        }
        break;
        case 0x0055: {
            unsigned char temp = (opcode & 0x0F00) >> 8;
            for (unsigned char i = 0; i < temp + 1; i++) {
                mem->Set(I + i, V[i]);
            }
        }
        break;
        case 0x0065: {
            unsigned char temp = (opcode & 0x0F00) >> 8;
            for (unsigned char i = 0; i < temp + 1; i++) {
                V[i] = mem->Get(I + i);
            }
        }
        break;
        default:
            break;
        }
        break;
    default:
        break;
    }

    pc += 2;
}
