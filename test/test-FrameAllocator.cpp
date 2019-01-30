#include "Misc/FrameAllocator.h"

#include "gtest/gtest.h"

TEST(FrameAllocatorTest, Placeholder)
{
    EXPECT_TRUE(false);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    int rv = RUN_ALL_TESTS();
    return rv;
}
