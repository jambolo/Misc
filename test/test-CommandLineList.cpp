#include "Misc/CommandLineList.h"

#include "gtest/gtest.h"

TEST(CommandLineListTest, Placeholder)
{
    EXPECT_TRUE(false);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    int rv = RUN_ALL_TESTS();
    return rv;
}
