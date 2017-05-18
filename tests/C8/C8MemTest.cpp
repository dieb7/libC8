#include "SimpleC8Mem.h"

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

TEST_GROUP(SimpleC8Mem)
{
    SimpleC8Mem* c8Mem;

    void setup() {
        c8Mem = new SimpleC8Mem();
    }
    void teardown() {
        delete c8Mem;
    }
};

TEST(SimpleC8Mem, SetGet)
{
    for (unsigned int i = 0x200; i < 0x1000; i++) {
        unsigned char val = i & 0xFF;
        c8Mem->Set(i, val);
        CHECK_EQUAL(val, c8Mem->Get(i));
    }
}

