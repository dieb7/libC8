#include "C8.h"
#include "SimpleC8Keypad.h"
#include "SimpleC8Random.h"
#include "SimpleC8Display.h"
#include "SimpleC8Timer.h"
#include "SimpleC8Mem.h"

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

TEST_GROUP(C8)
{
    C8* chip8;
    SimpleC8Mem* mem;
    C8Stack* st;
    SimpleC8Display* disp;
    SimpleC8Keypad* key;
    SimpleC8Timer *delayTimer;
    SimpleC8Timer *soundTimer;
    SimpleC8Random * random;

    void setup() {
        chip8 = new C8();
        mem = new SimpleC8Mem();
        st = new C8Stack();
        disp = new SimpleC8Display();
        key = new SimpleC8Keypad();
        delayTimer = new SimpleC8Timer();
        soundTimer = new SimpleC8Timer();
        random = new SimpleC8Random();

        chip8->setMem(mem);
        chip8->setStack(st);
        chip8->setDisplay(disp);
        chip8->setKey(key);
        chip8->setDelayTimer(delayTimer);
        chip8->setSoundTimer(soundTimer);
        chip8->setRandom(random);
    }
    void teardown() {
        delete chip8;
        delete mem;
        delete st;
        delete disp;
        delete key;
        delete delayTimer;
        delete soundTimer;
        delete random;
    }
};

TEST(C8, op00E0)
{
    mem->Set(0x200, 0x00);
    mem->Set(0x201, 0xE0);

    disp->Draw(2, 4, 0x80);
    CHECK(disp->getPixel(2,4));

    chip8->emulateCycle();


    CHECK(!disp->getPixel(2,4));
}

TEST(C8, op00EE)
{
    st->push(0x300);

    mem->Set(0x200, 0x00);
    mem->Set(0x201, 0xEE);

    chip8->emulateCycle();

    CHECK_EQUAL(0x302, chip8->getPc());
}

TEST(C8, op1NNN)
{
    mem->Set(0x200, 0x14);
    mem->Set(0x201, 0xA5);

    chip8->emulateCycle();
    CHECK_EQUAL(0x04A5, chip8->getPc());
}

TEST(C8, op2NNN)
{
    mem->Set(0x200, 0x24);
    mem->Set(0x201, 0xA5);

    chip8->emulateCycle();
    CHECK_EQUAL(0x04A5, chip8->getPc());

    CHECK_EQUAL(0x0200, st->pop());
}

TEST(C8, op3NNN)
{
    mem->Set(0x200, 0x34);
    mem->Set(0x201, 0xA5);

    chip8->setVn(4, 0xA5);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0204, chip8->getPc());

    mem->Set(0x204, 0x34);
    mem->Set(0x205, 0xA5);

    chip8->setVn(4, 0xA0);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0206, chip8->getPc());
}

TEST(C8, op4NNN)
{
    mem->Set(0x200, 0x44);
    mem->Set(0x201, 0xA5);

    chip8->setVn(4, 0xA0);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0204, chip8->getPc());

    mem->Set(0x204, 0x44);
    mem->Set(0x205, 0xA5);

    chip8->setVn(4, 0xA5);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0206, chip8->getPc());
}

TEST(C8, op5NNN)
{
    mem->Set(0x200, 0x54);
    mem->Set(0x201, 0x55);

    chip8->setVn(4, 0xA5);
    chip8->setVn(5, 0xA5);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0204, chip8->getPc());

    mem->Set(0x204, 0x54);
    mem->Set(0x205, 0x55);

    chip8->setVn(4, 0xA0);
    chip8->setVn(5, 0xA5);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0206, chip8->getPc());
}

TEST(C8, op6XNN)
{
    mem->Set(0x200, 0x64);
    mem->Set(0x201, 0x55);

    chip8->emulateCycle();
    CHECK_EQUAL(0x55, chip8->getVn(4));

    CHECK_EQUAL(0x202, chip8->getPc());
}

TEST(C8, op7XNN)
{
    mem->Set(0x200, 0x74);
    mem->Set(0x201, 0x55);

    chip8->setVn(4, 0x05);

    chip8->emulateCycle();
    CHECK_EQUAL(0x5A, chip8->getVn(4));

    CHECK_EQUAL(0x202, chip8->getPc());
}

TEST(C8, op8XY0)
{
    mem->Set(0x200, 0x84);
    mem->Set(0x201, 0x50);

    chip8->setVn(5, 0x05);

    chip8->emulateCycle();
    CHECK_EQUAL(0x05, chip8->getVn(4));

    CHECK_EQUAL(0x202, chip8->getPc());
}

TEST(C8, op8XY1)
{
    mem->Set(0x200, 0x84);
    mem->Set(0x201, 0x51);

    chip8->setVn(4, 0x05);
    chip8->setVn(5, 0x08);
    chip8->setVn(0xF, 0xFF);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0D, chip8->getVn(4));

    CHECK_EQUAL(0x00, chip8->getVn(0xF));

    CHECK_EQUAL(0x202, chip8->getPc());
}

TEST(C8, op8XY2)
{
    mem->Set(0x200, 0x84);
    mem->Set(0x201, 0x52);

    chip8->setVn(4, 0x05);
    chip8->setVn(5, 0x06);
    chip8->setVn(0xF, 0xFF);

    chip8->emulateCycle();
    CHECK_EQUAL(0x04, chip8->getVn(4));

    CHECK_EQUAL(0x00, chip8->getVn(0xF));

    CHECK_EQUAL(0x202, chip8->getPc());
}

TEST(C8, op8XY3)
{
    mem->Set(0x200, 0x84);
    mem->Set(0x201, 0x53);

    chip8->setVn(4, 0x06);
    chip8->setVn(5, 0x04);
    chip8->setVn(0xF, 0xFF);

    chip8->emulateCycle();
    CHECK_EQUAL(0x02, chip8->getVn(4));

    CHECK_EQUAL(0x00, chip8->getVn(0xF));

    CHECK_EQUAL(0x202, chip8->getPc());
}


TEST(C8, op8XY4)
{
    mem->Set(0x200, 0x84);
    mem->Set(0x201, 0x54);

    chip8->setVn(4, 0x0A);
    chip8->setVn(5, 0x04);
    chip8->setVn(0xF, 0xFF);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0E, chip8->getVn(4));

    CHECK_EQUAL(0x00, chip8->getVn(0xF));

    CHECK_EQUAL(0x202, chip8->getPc());


    mem->Set(0x202, 0x84);
    mem->Set(0x203, 0x54);

    chip8->setVn(4, 0xFF);
    chip8->setVn(5, 0x0F);
    chip8->setVn(0xF, 0xFF);

    chip8->emulateCycle();

    CHECK_EQUAL(0x0E, chip8->getVn(4));

    CHECK_EQUAL(0x01, chip8->getVn(0xF));

    CHECK_EQUAL(0x204, chip8->getPc());
}

TEST(C8, op8XY5)
{
    mem->Set(0x200, 0x84);
    mem->Set(0x201, 0x55);

    chip8->setVn(4, 0x0A);
    chip8->setVn(5, 0x04);
    chip8->setVn(0xF, 0xFF);

    chip8->emulateCycle();
    CHECK_EQUAL(0x06, chip8->getVn(4));

    CHECK_EQUAL(0x00, chip8->getVn(0xF));

    CHECK_EQUAL(0x202, chip8->getPc());


    mem->Set(0x202, 0x84);
    mem->Set(0x203, 0x55);

    chip8->setVn(4, 0x06);
    chip8->setVn(5, 0x0F);
    chip8->setVn(0xF, 0xFF);

    chip8->emulateCycle();

    CHECK_EQUAL(0xF7, chip8->getVn(4));

    CHECK_EQUAL(0x01, chip8->getVn(0xF));

    CHECK_EQUAL(0x204, chip8->getPc());
}

TEST(C8, op8XY6)
{
    mem->Set(0x200, 0x84);
    mem->Set(0x201, 0x56);

    chip8->setVn(4, 0x0A);
    chip8->setVn(0xF, 0xFF);

    chip8->emulateCycle();
    CHECK_EQUAL(0x05, chip8->getVn(4));

    CHECK_EQUAL(0x00, chip8->getVn(0xF));

    CHECK_EQUAL(0x202, chip8->getPc());


    mem->Set(0x202, 0x84);
    mem->Set(0x203, 0x56);

    chip8->setVn(4, 0x07);
    chip8->setVn(0xF, 0xFF);

    chip8->emulateCycle();

    CHECK_EQUAL(0x03, chip8->getVn(4));

    CHECK_EQUAL(0x01, chip8->getVn(0xF));

    CHECK_EQUAL(0x204, chip8->getPc());
}

TEST(C8, op8XY7)
{
    mem->Set(0x200, 0x84);
    mem->Set(0x201, 0x57);

    chip8->setVn(5, 0x0A);
    chip8->setVn(4, 0x04);
    chip8->setVn(0xF, 0xFF);

    chip8->emulateCycle();
    CHECK_EQUAL(0x06, chip8->getVn(4));

    CHECK_EQUAL(0x00, chip8->getVn(0xF));

    CHECK_EQUAL(0x202, chip8->getPc());


    mem->Set(0x202, 0x84);
    mem->Set(0x203, 0x57);

    chip8->setVn(5, 0x06);
    chip8->setVn(4, 0x0F);
    chip8->setVn(0xF, 0xFF);

    chip8->emulateCycle();

    CHECK_EQUAL(0xF7, chip8->getVn(4));

    CHECK_EQUAL(0x01, chip8->getVn(0xF));

    CHECK_EQUAL(0x204, chip8->getPc());
}

TEST(C8, op8XYE)
{
    mem->Set(0x200, 0x84);
    mem->Set(0x201, 0x5E);

    chip8->setVn(4, 0x0A);
    chip8->setVn(0xF, 0xFF);

    chip8->emulateCycle();
    CHECK_EQUAL(0x14, chip8->getVn(4));

    CHECK_EQUAL(0x00, chip8->getVn(0xF));

    CHECK_EQUAL(0x202, chip8->getPc());


    mem->Set(0x202, 0x84);
    mem->Set(0x203, 0x5E);

    chip8->setVn(4, 0xF0);
    chip8->setVn(0xF, 0xFF);

    chip8->emulateCycle();

    CHECK_EQUAL(0xE0, chip8->getVn(4));

    CHECK_EQUAL(0x01, chip8->getVn(0xF));

    CHECK_EQUAL(0x204, chip8->getPc());
}

TEST(C8, op9XY0)
{
    mem->Set(0x200, 0x94);
    mem->Set(0x201, 0x55);

    chip8->setVn(4, 0xA0);
    chip8->setVn(5, 0xA5);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0204, chip8->getPc());

    mem->Set(0x204, 0x94);
    mem->Set(0x205, 0x55);

    chip8->setVn(4, 0xA5);
    chip8->setVn(5, 0xA5);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0206, chip8->getPc());
}

TEST(C8, opANNN)
{
    mem->Set(0x200, 0xA4);
    mem->Set(0x201, 0x55);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0455, chip8->getI());
    CHECK_EQUAL(0x202, chip8->getPc());
}

TEST(C8, opBNNN)
{
    mem->Set(0x200, 0xB4);
    mem->Set(0x201, 0xA4);

    chip8->setVn(0, 0x4);

    chip8->emulateCycle();
    CHECK_EQUAL(0x04A8, chip8->getPc());
}

TEST(C8, opCXNN)
{
    /**< @todo find a way to test this opcode */
}

TEST(C8, opDXYN)
{
    mem->Set(0x200, 0xD0);
    mem->Set(0x201, 0x12);

    mem->Set(0x300, 0xE0);
    mem->Set(0x301, 0x90);

    chip8->setI(0x300);

    chip8->setVn(0, 0x5);
    chip8->setVn(1, 0x0);

    chip8->emulateCycle();
    CHECK_EQUAL(0x202, chip8->getPc());

    CHECK_EQUAL(0x300, chip8->getI());

    CHECK(disp->getPixel(5, 0));
    CHECK(disp->getPixel(6, 0));
    CHECK(disp->getPixel(7, 0));
    CHECK(!disp->getPixel(8, 0));

    CHECK(disp->getPixel(5, 1));
    CHECK(!disp->getPixel(6, 1));
    CHECK(!disp->getPixel(7, 1));
    CHECK(disp->getPixel(8, 1));

    CHECK_EQUAL(0, chip8->getVn(0xF));


    mem->Set(0x202, 0xD0);
    mem->Set(0x203, 0x12);

    mem->Set(0x302, 0x20);

    chip8->setI(0x302);

    chip8->setVn(0, 0x5);
    chip8->setVn(1, 0x0);

    chip8->emulateCycle();
    CHECK_EQUAL(0x204, chip8->getPc());

    CHECK_EQUAL(0x302, chip8->getI());

    CHECK(disp->getPixel(5, 0));
    CHECK(disp->getPixel(6, 0));
    CHECK(!disp->getPixel(7, 0));
    CHECK(!disp->getPixel(8, 0));

    CHECK_EQUAL(1, chip8->getVn(0xF));
}

TEST(C8, opEX9E)
{
    mem->Set(0x200, 0xE1);
    mem->Set(0x201, 0x9E);

    key->Push(0x2);

    chip8->setVn(0x1, 0x2);

    chip8->emulateCycle();
    CHECK_EQUAL(0x204, chip8->getPc());

    mem->Set(0x204, 0xE2);
    mem->Set(0x201, 0x9E);

    key->Release(0x3);

    chip8->setVn(0x2, 0x3);

    chip8->emulateCycle();
    CHECK_EQUAL(0x206, chip8->getPc());
}

TEST(C8, opEXA1)
{
    mem->Set(0x200, 0xE1);
    mem->Set(0x201, 0xA1);

    key->Release(0x2);

    chip8->setVn(0x1, 0x2);

    chip8->emulateCycle();
    CHECK_EQUAL(0x204, chip8->getPc());

    mem->Set(0x204, 0xE2);
    mem->Set(0x201, 0xA1);

    key->Push(0x3);

    chip8->setVn(0x2, 0x3);

    chip8->emulateCycle();
    CHECK_EQUAL(0x206, chip8->getPc());
}

TEST(C8, opFX07)
{
    mem->Set(0x200, 0xF5);
    mem->Set(0x201, 0x07);

    delayTimer->SetValue(0x9F);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0202, chip8->getPc());

    CHECK_EQUAL(0x9F, chip8->getVn(0x5));
}

TEST(C8, opFX0A)
{
    mem->Set(0x200, 0xF5);
    mem->Set(0x201, 0x0A);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0200, chip8->getPc());

    key->Push(0x9);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0202, chip8->getPc());

    CHECK_EQUAL(0x9, chip8->getVn(0x5));
}

TEST(C8, opFX15)
{
    mem->Set(0x200, 0xF5);
    mem->Set(0x201, 0x15);

    chip8->setVn(0x5, 0x12);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0202, chip8->getPc());

    CHECK_EQUAL(0x12, delayTimer->GetValue());
}

TEST(C8, opFX1E)
{
    mem->Set(0x200, 0xF5);
    mem->Set(0x201, 0x1E);

    chip8->setVn(0x5, 0x5);
    chip8->setI(0x5);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0202, chip8->getPc());

    CHECK_EQUAL(0x000A, chip8->getI());
}

TEST(C8, opFX29)
{
    mem->Set(0x200, 0xF5);
    mem->Set(0x201, 0x29);

    chip8->setVn(0x5, 0x5);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0202, chip8->getPc());

    CHECK_EQUAL(0x19, chip8->getI());
}

TEST(C8, opFX33)
{
    mem->Set(0x200, 0xF5);
    mem->Set(0x201, 0x33);

    chip8->setVn(0x5, 0xFF);
    chip8->setI(0x300);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0202, chip8->getPc());

    CHECK_EQUAL(0x02, mem->Get(chip8->getI()));
    CHECK_EQUAL(0x05, mem->Get(chip8->getI() + 1));
    CHECK_EQUAL(0x05, mem->Get(chip8->getI() + 2));
}

TEST(C8, opFX55)
{
    mem->Set(0x200, 0xF5);
    mem->Set(0x201, 0x55);

    chip8->setVn(0x0, 0x0);
    chip8->setVn(0x1, 0x1);
    chip8->setVn(0x2, 0x2);
    chip8->setVn(0x3, 0x3);
    chip8->setVn(0x4, 0x4);
    chip8->setVn(0x5, 0x5);

    chip8->setI(0x300);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0202, chip8->getPc());

    CHECK_EQUAL(0x00, mem->Get(chip8->getI()));
    CHECK_EQUAL(0x01, mem->Get(chip8->getI() + 1));
    CHECK_EQUAL(0x02, mem->Get(chip8->getI() + 2));
    CHECK_EQUAL(0x03, mem->Get(chip8->getI() + 3));
    CHECK_EQUAL(0x04, mem->Get(chip8->getI() + 4));
    CHECK_EQUAL(0x05, mem->Get(chip8->getI() + 5));
}

TEST(C8, opFX65)
{
    mem->Set(0x200, 0xF5);
    mem->Set(0x201, 0x65);

    mem->Set(0x300, 0x0);
    mem->Set(0x301, 0x1);
    mem->Set(0x302, 0x2);
    mem->Set(0x303, 0x3);
    mem->Set(0x304, 0x4);
    mem->Set(0x305, 0x5);

    chip8->setI(0x300);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0202, chip8->getPc());

    CHECK_EQUAL(0x00, chip8->getVn(0x0));
    CHECK_EQUAL(0x01, chip8->getVn(0x1));
    CHECK_EQUAL(0x02, chip8->getVn(0x2));
    CHECK_EQUAL(0x03, chip8->getVn(0x3));
    CHECK_EQUAL(0x04, chip8->getVn(0x4));
    CHECK_EQUAL(0x05, chip8->getVn(0x5));
}
