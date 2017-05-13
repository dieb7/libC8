#include "C8Mem.h"

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

TEST_GROUP(C8Mem)
{
    C8Mem* c8Mem;

    void setup() {
        c8Mem = new C8Mem();
    }
    void teardown() {
        delete c8Mem;
    }
};

TEST(C8Mem, SetGet)
{
    for (unsigned int i = 0x200; i < 0x1000; i++) {
        unsigned char val = i & 0xFF;
        c8Mem->Set(i, val);
        CHECK_EQUAL(val, c8Mem->Get(i));
    }
}

