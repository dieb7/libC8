#include "Chip8.h"

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

TEST_GROUP(Chip8)
{
    Chip8* chip8;
    C8Stack* st;

    void setup()
    {
        chip8 = new Chip8();
        st = new C8Stack();
        chip8->setStack(st);
    }
    void teardown()
    {
        delete chip8;
        delete st;
    }
};

TEST(Chip8, op00E0)
{
    chip8->setMem(0x200, 0x00);
    chip8->setMem(0x201, 0xE0);

    chip8->setGfx(0x201, 246);
    CHECK(chip8->getGfx(0x201) == 246);

    chip8->emulateCycle();

    CHECK_EQUAL(0, chip8->getGfx(0x201));
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
