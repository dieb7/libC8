#include "C8Stack.h"

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

TEST_GROUP(C8Stack)
{
    C8Stack* c8Stack;

    void setup() {
        c8Stack = new C8Stack();
    }
    void teardown() {
        delete c8Stack;
    }
};

TEST(C8Stack, push)
{
    // max depth is 16
    CHECK(c8Stack->push(0x300));
    CHECK(c8Stack->push(0x302));
    CHECK(c8Stack->push(0x304));
    CHECK(c8Stack->push(0x306));
    CHECK(c8Stack->push(0x308));
    CHECK(c8Stack->push(0x30A));
    CHECK(c8Stack->push(0x30C));
    CHECK(c8Stack->push(0x30E));

    CHECK(c8Stack->push(0x310));
    CHECK(c8Stack->push(0x312));
    CHECK(c8Stack->push(0x314));
    CHECK(c8Stack->push(0x316));
    CHECK(c8Stack->push(0x318));
    CHECK(c8Stack->push(0x31A));
    CHECK(c8Stack->push(0x31C));
    CHECK(c8Stack->push(0x31E));

    CHECK(!c8Stack->push(0x320));
}


TEST(C8Stack, pop)
{
    // max depth is 16
    c8Stack->push(0x300);
    c8Stack->push(0x302);
    c8Stack->push(0x304);
    c8Stack->push(0x306);
    c8Stack->push(0x308);
    c8Stack->push(0x30A);
    c8Stack->push(0x30C);
    c8Stack->push(0x30E);

    c8Stack->push(0x310);
    c8Stack->push(0x312);
    c8Stack->push(0x314);
    c8Stack->push(0x316);
    c8Stack->push(0x318);
    c8Stack->push(0x31A);
    c8Stack->push(0x31C);
    c8Stack->push(0x31E);

    CHECK_EQUAL(0x31E, c8Stack->pop());
    CHECK_EQUAL(0x31C, c8Stack->pop());
    CHECK_EQUAL(0x31A, c8Stack->pop());
    CHECK_EQUAL(0x318, c8Stack->pop());
}
