#include "Chip8.h"

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

TEST_GROUP(Chip8)
{
    Chip8* chip8;
    C8Stack* st;
    C8Display* disp;
    C8Key* key;

    void setup() {
        chip8 = new Chip8();
        st = new C8Stack();
        disp = new C8Display();
        key = new C8Key();
        chip8->setStack(st);
        chip8->setDisplay(disp);
        chip8->setKey(key);
    }
    void teardown() {
        delete chip8;
        delete st;
        delete disp;
        delete key;
    }
};

TEST(Chip8, op00E0)
{
    chip8->setMem(0x200, 0x00);
    chip8->setMem(0x201, 0xE0);

    disp->Draw(2, 4, 0x80);
    CHECK(disp->getPixel(2,4));

    chip8->emulateCycle();


    CHECK(!disp->getPixel(2,4));
}

TEST(Chip8, op00EE)
{
    st->push(0x300);

    chip8->setMem(0x200, 0x00);
    chip8->setMem(0x201, 0xEE);

    chip8->emulateCycle();

    CHECK_EQUAL(0x302, chip8->getPc());
}

TEST(Chip8, op1NNN)
{
    chip8->setMem(0x200, 0x14);
    chip8->setMem(0x201, 0xA5);

    chip8->emulateCycle();
    CHECK_EQUAL(0x04A5, chip8->getPc());
}

TEST(Chip8, op2NNN)
{
    chip8->setMem(0x200, 0x24);
    chip8->setMem(0x201, 0xA5);

    chip8->emulateCycle();
    CHECK_EQUAL(0x04A5, chip8->getPc());

    CHECK_EQUAL(0x0200, st->pop());
}

TEST(Chip8, op3NNN)
{
    chip8->setMem(0x200, 0x34);
    chip8->setMem(0x201, 0xA5);

    chip8->setVn(4, 0xA5);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0204, chip8->getPc());

    chip8->setMem(0x204, 0x34);
    chip8->setMem(0x205, 0xA5);

    chip8->setVn(4, 0xA0);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0206, chip8->getPc());
}

TEST(Chip8, op4NNN)
{
    chip8->setMem(0x200, 0x44);
    chip8->setMem(0x201, 0xA5);

    chip8->setVn(4, 0xA0);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0204, chip8->getPc());

    chip8->setMem(0x204, 0x44);
    chip8->setMem(0x205, 0xA5);

    chip8->setVn(4, 0xA5);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0206, chip8->getPc());
}

TEST(Chip8, op5NNN)
{
    chip8->setMem(0x200, 0x54);
    chip8->setMem(0x201, 0x55);

    chip8->setVn(4, 0xA5);
    chip8->setVn(5, 0xA5);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0204, chip8->getPc());

    chip8->setMem(0x204, 0x54);
    chip8->setMem(0x205, 0x55);

    chip8->setVn(4, 0xA0);
    chip8->setVn(5, 0xA5);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0206, chip8->getPc());
}

TEST(Chip8, op6XNN)
{
    chip8->setMem(0x200, 0x64);
    chip8->setMem(0x201, 0x55);

    chip8->emulateCycle();
    CHECK_EQUAL(0x55, chip8->getVn(4));

    CHECK_EQUAL(0x202, chip8->getPc());
}

TEST(Chip8, op7XNN)
{
    chip8->setMem(0x200, 0x74);
    chip8->setMem(0x201, 0x55);

    chip8->setVn(4, 0x05);

    chip8->emulateCycle();
    CHECK_EQUAL(0x5A, chip8->getVn(4));

    CHECK_EQUAL(0x202, chip8->getPc());
}

TEST(Chip8, op8XY0)
{
    chip8->setMem(0x200, 0x84);
    chip8->setMem(0x201, 0x50);

    chip8->setVn(5, 0x05);

    chip8->emulateCycle();
    CHECK_EQUAL(0x05, chip8->getVn(4));

    CHECK_EQUAL(0x202, chip8->getPc());
}

TEST(Chip8, op8XY1)
{
    chip8->setMem(0x200, 0x84);
    chip8->setMem(0x201, 0x51);

    chip8->setVn(4, 0x05);
    chip8->setVn(5, 0x08);
    chip8->setVn(0xF, 0xFF);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0D, chip8->getVn(4));

    CHECK_EQUAL(0x00, chip8->getVn(0xF));

    CHECK_EQUAL(0x202, chip8->getPc());
}

TEST(Chip8, op8XY2)
{
    chip8->setMem(0x200, 0x84);
    chip8->setMem(0x201, 0x52);

    chip8->setVn(4, 0x05);
    chip8->setVn(5, 0x06);
    chip8->setVn(0xF, 0xFF);

    chip8->emulateCycle();
    CHECK_EQUAL(0x04, chip8->getVn(4));

    CHECK_EQUAL(0x00, chip8->getVn(0xF));

    CHECK_EQUAL(0x202, chip8->getPc());
}

TEST(Chip8, op8XY3)
{
    chip8->setMem(0x200, 0x84);
    chip8->setMem(0x201, 0x53);

    chip8->setVn(4, 0x06);
    chip8->setVn(5, 0x04);
    chip8->setVn(0xF, 0xFF);

    chip8->emulateCycle();
    CHECK_EQUAL(0x02, chip8->getVn(4));

    CHECK_EQUAL(0x00, chip8->getVn(0xF));

    CHECK_EQUAL(0x202, chip8->getPc());
}


TEST(Chip8, op8XY4)
{
    chip8->setMem(0x200, 0x84);
    chip8->setMem(0x201, 0x54);

    chip8->setVn(4, 0x0A);
    chip8->setVn(5, 0x04);
    chip8->setVn(0xF, 0xFF);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0E, chip8->getVn(4));

    CHECK_EQUAL(0x00, chip8->getVn(0xF));

    CHECK_EQUAL(0x202, chip8->getPc());


    chip8->setMem(0x202, 0x84);
    chip8->setMem(0x203, 0x54);

    chip8->setVn(4, 0xFF);
    chip8->setVn(5, 0x0F);
    chip8->setVn(0xF, 0xFF);

    chip8->emulateCycle();

    CHECK_EQUAL(0x0E, chip8->getVn(4));

    CHECK_EQUAL(0x01, chip8->getVn(0xF));

    CHECK_EQUAL(0x204, chip8->getPc());
}

TEST(Chip8, op8XY5)
{
    chip8->setMem(0x200, 0x84);
    chip8->setMem(0x201, 0x55);

    chip8->setVn(4, 0x0A);
    chip8->setVn(5, 0x04);
    chip8->setVn(0xF, 0xFF);

    chip8->emulateCycle();
    CHECK_EQUAL(0x06, chip8->getVn(4));

    CHECK_EQUAL(0x00, chip8->getVn(0xF));

    CHECK_EQUAL(0x202, chip8->getPc());


    chip8->setMem(0x202, 0x84);
    chip8->setMem(0x203, 0x55);

    chip8->setVn(4, 0x06);
    chip8->setVn(5, 0x0F);
    chip8->setVn(0xF, 0xFF);

    chip8->emulateCycle();

    CHECK_EQUAL(0xF7, chip8->getVn(4));

    CHECK_EQUAL(0x01, chip8->getVn(0xF));

    CHECK_EQUAL(0x204, chip8->getPc());
}

TEST(Chip8, op8XY6)
{
    chip8->setMem(0x200, 0x84);
    chip8->setMem(0x201, 0x56);

    chip8->setVn(4, 0x0A);
    chip8->setVn(0xF, 0xFF);

    chip8->emulateCycle();
    CHECK_EQUAL(0x05, chip8->getVn(4));

    CHECK_EQUAL(0x00, chip8->getVn(0xF));

    CHECK_EQUAL(0x202, chip8->getPc());


    chip8->setMem(0x202, 0x84);
    chip8->setMem(0x203, 0x56);

    chip8->setVn(4, 0x07);
    chip8->setVn(0xF, 0xFF);

    chip8->emulateCycle();

    CHECK_EQUAL(0x03, chip8->getVn(4));

    CHECK_EQUAL(0x01, chip8->getVn(0xF));

    CHECK_EQUAL(0x204, chip8->getPc());
}

TEST(Chip8, op8XY7)
{
    chip8->setMem(0x200, 0x84);
    chip8->setMem(0x201, 0x57);

    chip8->setVn(5, 0x0A);
    chip8->setVn(4, 0x04);
    chip8->setVn(0xF, 0xFF);

    chip8->emulateCycle();
    CHECK_EQUAL(0x06, chip8->getVn(4));

    CHECK_EQUAL(0x00, chip8->getVn(0xF));

    CHECK_EQUAL(0x202, chip8->getPc());


    chip8->setMem(0x202, 0x84);
    chip8->setMem(0x203, 0x57);

    chip8->setVn(5, 0x06);
    chip8->setVn(4, 0x0F);
    chip8->setVn(0xF, 0xFF);

    chip8->emulateCycle();

    CHECK_EQUAL(0xF7, chip8->getVn(4));

    CHECK_EQUAL(0x01, chip8->getVn(0xF));

    CHECK_EQUAL(0x204, chip8->getPc());
}

TEST(Chip8, op8XYE)
{
    chip8->setMem(0x200, 0x84);
    chip8->setMem(0x201, 0x5E);

    chip8->setVn(4, 0x0A);
    chip8->setVn(0xF, 0xFF);

    chip8->emulateCycle();
    CHECK_EQUAL(0x14, chip8->getVn(4));

    CHECK_EQUAL(0x00, chip8->getVn(0xF));

    CHECK_EQUAL(0x202, chip8->getPc());


    chip8->setMem(0x202, 0x84);
    chip8->setMem(0x203, 0x5E);

    chip8->setVn(4, 0xF0);
    chip8->setVn(0xF, 0xFF);

    chip8->emulateCycle();

    CHECK_EQUAL(0xE0, chip8->getVn(4));

    CHECK_EQUAL(0x01, chip8->getVn(0xF));

    CHECK_EQUAL(0x204, chip8->getPc());
}

TEST(Chip8, op9XY0)
{
    chip8->setMem(0x200, 0x94);
    chip8->setMem(0x201, 0x55);

    chip8->setVn(4, 0xA0);
    chip8->setVn(5, 0xA5);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0204, chip8->getPc());

    chip8->setMem(0x204, 0x94);
    chip8->setMem(0x205, 0x55);

    chip8->setVn(4, 0xA5);
    chip8->setVn(5, 0xA5);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0206, chip8->getPc());
}

TEST(Chip8, opANNN)
{
    chip8->setMem(0x200, 0xA4);
    chip8->setMem(0x201, 0x55);

    chip8->emulateCycle();
    CHECK_EQUAL(0x0455, chip8->getI());
    CHECK_EQUAL(0x202, chip8->getPc());
}

TEST(Chip8, opBNNN)
{
    chip8->setMem(0x200, 0xB4);
    chip8->setMem(0x201, 0xA4);

    chip8->setVn(0, 0x4);

    chip8->emulateCycle();
    CHECK_EQUAL(0x04A8, chip8->getPc());
}

TEST(Chip8, opCXNN)
{
    /**< @todo find a way to test this opcode */
}

TEST(Chip8, opDXYN)
{
    chip8->setMem(0x200, 0xD0);
    chip8->setMem(0x201, 0x12);

    chip8->setMem(0x300, 0xE0);
    chip8->setMem(0x301, 0x90);

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


    chip8->setMem(0x202, 0xD0);
    chip8->setMem(0x203, 0x12);

    chip8->setMem(0x302, 0x20);

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

TEST(Chip8, opEX9E)
{
    chip8->setMem(0x200, 0xE1);
    chip8->setMem(0x201, 0x9E);

    key->Push(0x2);

    chip8->setVn(0x1, 0x2);

    chip8->emulateCycle();
    CHECK_EQUAL(0x204, chip8->getPc());

    chip8->setMem(0x204, 0xE2);
    chip8->setMem(0x201, 0x9E);

    key->Release(0x3);

    chip8->setVn(0x2, 0x3);

    chip8->emulateCycle();
    CHECK_EQUAL(0x206, chip8->getPc());
}
