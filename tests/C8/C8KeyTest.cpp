#include "C8Key.h"

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

TEST_GROUP(C8Key)
{
    C8Key* c8Key;

    void setup() {
        c8Key = new C8Key();
    }
    void teardown() {
        delete c8Key;
    }
};

TEST(C8Key, setGetKey)
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

TEST(C8Key, outOfBounds)
{
    c8Key->Push(16);
    CHECK(!c8Key->Get(16));
    c8Key->Release(16);
    CHECK(!c8Key->Get(16));
}
