#include <iostream>

#include "unit_test.h"
#include "json_pointer_test.h"
#include <format/json.h>

int
main (int argc, char *argv[])
{
  ::testing::InitGoogleTest (& argc, argv);
  // testing::GTEST_FLAG (filter) = "-json_pointer_test.point";
  return RUN_ALL_TESTS ();
}
