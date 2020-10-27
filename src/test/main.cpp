#include <iostream>

#include "unit_test.h"
#include "json_pointer_test.h"

int
main (int argc, char *argv[])
{
  ::testing::InitGoogleTest (& argc, argv);
    // testing::GTEST_FLAG (filter) = "-uci_stdio_test.write_to_dead_child";
    return RUN_ALL_TESTS ();
}
