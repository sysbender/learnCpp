#include <gtest/gtest.h>
#include "LibraryCode.h"

// test suite name , test name
TEST(TestSuiteSample, TestSample)
{
    int result = sum(2, 6)
        ASSERT_EQ(6, result)
}

int main(int argc, char **argv)
{
    testing::InitialGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}