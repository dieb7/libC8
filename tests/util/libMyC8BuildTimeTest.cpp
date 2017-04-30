#include "CppUTest/TestHarness.h"
#include "libMyC8BuildTime.h"

TEST_GROUP(libMyC8BuildTime)
{
  libMyC8BuildTime* projectBuildTime;

  void setup()
  {
    projectBuildTime = new libMyC8BuildTime();
  }
  void teardown()
  {
    delete projectBuildTime;
  }
};

TEST(libMyC8BuildTime, Create)
{
  CHECK(0 != projectBuildTime->GetDateTime());
}

