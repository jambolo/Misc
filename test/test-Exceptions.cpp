#include "Misc/Exceptions.h"

#include "gtest/gtest.h"

struct Fail
{
    Fail()
    {
        throw ConstructorFailedException();
    }
    Fail(char const * text)
    {
        throw ConstructorFailedException(text);
    }
};

struct Succeed
{
};

TEST(ExceptionsTest, ConstructorFailedException)
{
    EXPECT_NO_THROW({ (void)Succeed(); });
    EXPECT_THROW({ (void)Fail(); }, ConstructorFailedException);

    std::string text;
    try
    {
        (void)Fail();
    }
    catch (ConstructorFailedException const & ex)
    {
        text = ex.what();
    }
    EXPECT_EQ(text, "constructor failed");

    try
    {
        (void)Fail("alternate text");
    }
    catch (ConstructorFailedException const & ex)
    {
        text = ex.what();
    }
    EXPECT_EQ(text, "alternate text");
}
