#include "Misc/Exceptions.h"

#include "gtest/gtest.h"

TEST(ExceptionsTest, ConstructorFailedException)
{
    bool thrown;
    thrown = false;
    try
    {
        throw ConstructorFailedException();
    }
    catch (...)
    {
        thrown = true;
    }
    EXPECT_TRUE(thrown);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    int rv = RUN_ALL_TESTS();
    return rv;
}
