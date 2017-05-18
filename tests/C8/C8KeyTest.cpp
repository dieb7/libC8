#include "SimpleC8Keypad.h"

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

TEST_GROUP(SimpleC8Keypad)
{
    SimpleC8Keypad* c8Key;

    void setup() {
        c8Key = new SimpleC8Keypad();
    }
    void teardown() {
        delete c8Key;
    }
};

TEST(SimpleC8Keypad, setGetKey)
{
    c8Key->Push(0);
    CHECK(c8Key->Get(0));
    c8Key->Release(0);
    CHECK(!c8Key->Get(0));

    c8Key->Push(6);
    CHECK(c8Key->Get(6));
    c8Key->Release(6);
    CHECK(!c8Key->Get(6));
}

TEST(SimpleC8Keypad, outOfBounds)
{
    c8Key->Push(16);
    CHECK(!c8Key->Get(16));
    c8Key->Release(16);
    CHECK(!c8Key->Get(16));
}
