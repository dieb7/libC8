#include "SimpleC8Timer.h"

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

TEST_GROUP(SimpleC8Timer)
{
    SimpleC8Timer* c8Timer;

    void setup() {
        c8Timer = new SimpleC8Timer();
    }
    void teardown() {
        delete c8Timer;
    }
};

TEST(SimpleC8Timer, Create)
{
    c8Timer->SetValue(0xF4);
    CHECK_EQUAL(0xF4, c8Timer->GetValue());
}

