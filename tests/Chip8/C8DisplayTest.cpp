#include "C8Display.h"

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

TEST_GROUP(C8Display)
{
    C8Display* c8Display;

    void setup() {
        c8Display = new C8Display();
    }
    void teardown() {
        delete c8Display;
    }
};

TEST(C8Display, Create)
{
    for (unsigned char x = 0; x < 64; x++) {
        for (unsigned char y = 0; y < 32; y++) {
            CHECK(!c8Display->getPixel(x, y))
        }
    }
}

TEST(C8Display, setGet)
{
    c8Display->setPixel(2, 4, true);
    CHECK(c8Display->getPixel(2, 4));

    c8Display->setPixel(2, 4, false);
    CHECK(!c8Display->getPixel(2, 4));

    c8Display->setPixel(63, 31, true);
    CHECK(c8Display->getPixel(63, 31));

    c8Display->setPixel(63, 31, false);
    CHECK(!c8Display->getPixel(63, 31));
}

TEST(C8Display, drawD)
{
    c8Display->Draw(0, 0, 0xE0);
    CHECK(c8Display->getPixel(0, 0));
    CHECK(c8Display->getPixel(1, 0));
    CHECK(c8Display->getPixel(2, 0));
    CHECK(!c8Display->getPixel(3, 0));

    c8Display->Draw(0, 1, 0x90);

    CHECK(c8Display->getPixel(0, 1));
    CHECK(!c8Display->getPixel(1, 1));
    CHECK(!c8Display->getPixel(2, 1));
    CHECK(c8Display->getPixel(3, 1));

    c8Display->Draw(0, 2, 0x90);

    CHECK(c8Display->getPixel(0, 2));
    CHECK(!c8Display->getPixel(1, 2));
    CHECK(!c8Display->getPixel(2, 2));
    CHECK(c8Display->getPixel(3, 2));

    c8Display->Draw(0, 3, 0xE0);

    CHECK(c8Display->getPixel(0, 3));
    CHECK(c8Display->getPixel(1, 3));
    CHECK(c8Display->getPixel(2, 3));
    CHECK(!c8Display->getPixel(3, 3));
}

TEST(C8Display, drawShift5)
{
    c8Display->Draw(5, 0, 0xE0);
    CHECK(c8Display->getPixel(5, 0));
    CHECK(c8Display->getPixel(6, 0));
    CHECK(c8Display->getPixel(7, 0));
    CHECK(!c8Display->getPixel(8, 0));

    c8Display->Draw(5, 1, 0x90);

    CHECK(c8Display->getPixel(5, 1));
    CHECK(!c8Display->getPixel(6, 1));
    CHECK(!c8Display->getPixel(7, 1));
    CHECK(c8Display->getPixel(8, 1));

    c8Display->Draw(5, 2, 0x90);

    CHECK(c8Display->getPixel(5, 2));
    CHECK(!c8Display->getPixel(6, 2));
    CHECK(!c8Display->getPixel(7, 2));
    CHECK(c8Display->getPixel(8, 2));

    c8Display->Draw(5, 3, 0xE0);

    CHECK(c8Display->getPixel(5, 3));
    CHECK(c8Display->getPixel(6, 3));
    CHECK(c8Display->getPixel(7, 3));
    CHECK(!c8Display->getPixel(8, 3));
}

TEST(C8Display, outOfBounds0)
{
    c8Display->Draw(64, 0, 0xFF);
    c8Display->Draw(0, 33, 0xFF);
}

TEST(C8Display, outOfBounds1)
{
    c8Display->Draw(60, 0, 0xFF);

    CHECK(c8Display->getPixel(60, 0));
    CHECK(c8Display->getPixel(61, 0));
    CHECK(c8Display->getPixel(62, 0));
    CHECK(c8Display->getPixel(63, 0));
}

TEST(C8Display, flip0)
{
    CHECK(!c8Display->Draw(0, 0, 0xFF));
    CHECK(c8Display->Draw(0, 0, 0x01));

    CHECK(!c8Display->getPixel(7, 0));
}

TEST(C8Display, flip1)
{
    CHECK(!c8Display->Draw(0, 0, 0x55));
    CHECK(!c8Display->Draw(0, 0, 0xAA));

    CHECK(c8Display->getPixel(0, 0));
    CHECK(c8Display->getPixel(1, 0));
    CHECK(c8Display->getPixel(2, 0));
    CHECK(c8Display->getPixel(3, 0));
    CHECK(c8Display->getPixel(4, 0));
    CHECK(c8Display->getPixel(5, 0));
    CHECK(c8Display->getPixel(6, 0));
    CHECK(c8Display->getPixel(7, 0));
}
