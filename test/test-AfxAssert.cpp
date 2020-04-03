#if defined(_DEBUG)
// Redefine asserts to throw exceptions instead of doing the normal stuff. Note that this assumes certain implementation details.
#include <stdexcept>
#define AfxDebugBreak() throw std::runtime_error("AfxDebugBreak")
#define AfxAssertFailedLine(f, l) true
#endif

// Prevent afx.h from actually being included
#define __AFX_H__

#include "Misc/AfxAssert.h"
#include "Misc/Etc.h"

#include "gtest/gtest.h"

#if defined(_DEBUG)

TEST(AfxAssertTest, Limits)
{
    EXPECT_NO_THROW(ASSERT_LIMITS(0, 0, 0));
    EXPECT_NO_THROW(ASSERT_LIMITS(0, 0, 1));
    EXPECT_NO_THROW(ASSERT_LIMITS(0, 0, 2));
    EXPECT_THROW(   ASSERT_LIMITS(0, 1, 0), std::runtime_error);
    EXPECT_NO_THROW(ASSERT_LIMITS(0, 1, 1));
    EXPECT_NO_THROW(ASSERT_LIMITS(0, 1, 2));
    EXPECT_THROW(   ASSERT_LIMITS(0, 2, 0), std::runtime_error);
    EXPECT_THROW(   ASSERT_LIMITS(0, 2, 1), std::runtime_error);
    EXPECT_NO_THROW(ASSERT_LIMITS(0, 2, 2));
    EXPECT_THROW(   ASSERT_LIMITS(1, 0, 0), std::runtime_error);
    EXPECT_THROW(   ASSERT_LIMITS(1, 0, 1), std::runtime_error);
    EXPECT_THROW(   ASSERT_LIMITS(1, 0, 2), std::runtime_error);
    EXPECT_THROW(   ASSERT_LIMITS(1, 1, 0), std::runtime_error);
    EXPECT_NO_THROW(ASSERT_LIMITS(1, 1, 1));
    EXPECT_NO_THROW(ASSERT_LIMITS(1, 1, 2));
    EXPECT_THROW(   ASSERT_LIMITS(1, 2, 0), std::runtime_error);
    EXPECT_THROW(   ASSERT_LIMITS(1, 2, 1), std::runtime_error);
    EXPECT_NO_THROW(ASSERT_LIMITS(1, 2, 2));
    EXPECT_THROW(   ASSERT_LIMITS(2, 0, 0), std::runtime_error);
    EXPECT_THROW(   ASSERT_LIMITS(2, 0, 1), std::runtime_error);
    EXPECT_THROW(   ASSERT_LIMITS(2, 0, 2), std::runtime_error);
    EXPECT_THROW(   ASSERT_LIMITS(2, 1, 0), std::runtime_error);
    EXPECT_THROW(   ASSERT_LIMITS(2, 1, 1), std::runtime_error);
    EXPECT_THROW(   ASSERT_LIMITS(2, 1, 2), std::runtime_error);
    EXPECT_THROW(   ASSERT_LIMITS(2, 2, 0), std::runtime_error);
    EXPECT_THROW(   ASSERT_LIMITS(2, 2, 1), std::runtime_error);
    EXPECT_NO_THROW(ASSERT_LIMITS(2, 2, 2));
}

TEST(AfxAssertTest, MemsetValid)
{
    char * char_pointer = 0;
    EXPECT_NO_THROW(ASSERT_MEMSET_VALID(char_pointer, 0));
    EXPECT_NO_THROW(ASSERT_MEMSET_VALID(char_pointer, -1));
    EXPECT_NO_THROW(ASSERT_MEMSET_VALID(char_pointer, -128));
    EXPECT_NO_THROW(ASSERT_MEMSET_VALID(char_pointer, 255));
    EXPECT_THROW(   ASSERT_MEMSET_VALID(char_pointer, -129), std::runtime_error);
    EXPECT_THROW(   ASSERT_MEMSET_VALID(char_pointer, 256), std::runtime_error);

    int * int_pointer = 0;
    EXPECT_NO_THROW(ASSERT_MEMSET_VALID(int_pointer, 0));
    EXPECT_NO_THROW(ASSERT_MEMSET_VALID(int_pointer, -1));
    EXPECT_THROW(   ASSERT_MEMSET_VALID(int_pointer, -128), std::runtime_error);
    EXPECT_THROW(   ASSERT_MEMSET_VALID(int_pointer, 255), std::runtime_error);
    EXPECT_THROW(   ASSERT_MEMSET_VALID(int_pointer, -129), std::runtime_error);
    EXPECT_THROW(   ASSERT_MEMSET_VALID(int_pointer, 256), std::runtime_error);
}


TEST(AfxAssertTest, PointerValid)
{
    int x;
    int * nonnullpointer = &x;
    int * nullpointer = nullptr;
    EXPECT_NO_THROW(ASSERTP(nonnullpointer, false));
    EXPECT_NO_THROW(ASSERTP(nonnullpointer, true));
    EXPECT_THROW(   ASSERTP(nullpointer, false), std::runtime_error);
    EXPECT_NO_THROW(ASSERTP(nullpointer, true));
    EXPECT_THROW(   ASSERTP(0, false), std::runtime_error);
    EXPECT_NO_THROW(ASSERTP(0, true));
}

TEST(AfxAssertTest, AlmostEqual)
{
    EXPECT_THROW(ASSERT_ALMOST_EQUAL(  98.0,  100.0,  0.01), std::runtime_error);
    EXPECT_THROW(ASSERT_ALMOST_EQUAL( 100.0,   98.0,  0.01), std::runtime_error);
    EXPECT_THROW(ASSERT_ALMOST_EQUAL(  98.0,  100.0, -0.01), std::runtime_error);
    EXPECT_THROW(ASSERT_ALMOST_EQUAL( 100.0,   98.0, -0.01), std::runtime_error);
    EXPECT_THROW(ASSERT_ALMOST_EQUAL(  98.0, -100.0,  0.01), std::runtime_error);
    EXPECT_THROW(ASSERT_ALMOST_EQUAL( 100.0,  -98.0,  0.01), std::runtime_error);
    EXPECT_THROW(ASSERT_ALMOST_EQUAL(  98.0, -100.0, -0.01), std::runtime_error);
    EXPECT_THROW(ASSERT_ALMOST_EQUAL( 100.0,  -98.0, -0.01), std::runtime_error);
    EXPECT_THROW(ASSERT_ALMOST_EQUAL( -98.0,  100.0,  0.01), std::runtime_error);
    EXPECT_THROW(ASSERT_ALMOST_EQUAL(-100.0,   98.0,  0.01), std::runtime_error);
    EXPECT_THROW(ASSERT_ALMOST_EQUAL( -98.0,  100.0, -0.01), std::runtime_error);
    EXPECT_THROW(ASSERT_ALMOST_EQUAL(-100.0,   98.0, -0.01), std::runtime_error);
    EXPECT_THROW(ASSERT_ALMOST_EQUAL( -98.0, -100.0,  0.01), std::runtime_error);
    EXPECT_THROW(ASSERT_ALMOST_EQUAL(-100.0,  -98.0,  0.01), std::runtime_error);
    EXPECT_THROW(ASSERT_ALMOST_EQUAL( -98.0, -100.0, -0.01), std::runtime_error);
    EXPECT_THROW(ASSERT_ALMOST_EQUAL(-100.0,  -98.0, -0.01), std::runtime_error);

    EXPECT_NO_THROW(ASSERT_ALMOST_EQUAL( 99.0, 100.0,  0.02));
    EXPECT_NO_THROW(ASSERT_ALMOST_EQUAL(100.0,  99.0,  0.02));
    EXPECT_NO_THROW(ASSERT_ALMOST_EQUAL (99.0, 100.0, -0.02));
    EXPECT_NO_THROW(ASSERT_ALMOST_EQUAL(100.0,  99.0, -0.02));
    EXPECT_THROW(   ASSERT_ALMOST_EQUAL(  99.0, -100.0,  0.02), std::runtime_error);
    EXPECT_THROW(   ASSERT_ALMOST_EQUAL( 100.0,  -99.0,  0.02), std::runtime_error);
    EXPECT_THROW(   ASSERT_ALMOST_EQUAL(  99.0, -100.0, -0.02), std::runtime_error);
    EXPECT_THROW(   ASSERT_ALMOST_EQUAL( 100.0,  -99.0, -0.02), std::runtime_error);
    EXPECT_THROW(   ASSERT_ALMOST_EQUAL( -99.0,  100.0,  0.02), std::runtime_error);
    EXPECT_THROW(   ASSERT_ALMOST_EQUAL(-100.0,   99.0,  0.02), std::runtime_error);
    EXPECT_THROW(   ASSERT_ALMOST_EQUAL( -99.0,  100.0, -0.02), std::runtime_error);
    EXPECT_THROW(   ASSERT_ALMOST_EQUAL(-100.0,   99.0, -0.02), std::runtime_error);
    EXPECT_NO_THROW(ASSERT_ALMOST_EQUAL( -99.0, -100.0,  0.02));
    EXPECT_NO_THROW(ASSERT_ALMOST_EQUAL(-100.0,  -99.0,  0.02));
    EXPECT_NO_THROW(ASSERT_ALMOST_EQUAL( -99.0, -100.0, -0.02));
    EXPECT_NO_THROW(ASSERT_ALMOST_EQUAL(-100.0,  -99.0, -0.02));

    EXPECT_NO_THROW(ASSERT_ALMOST_EQUAL(0.0, 0.0, 0.0));
    EXPECT_NO_THROW(ASSERT_ALMOST_EQUAL(0.0, 0.0, 0.01));
}

TEST(AfxAssertTest, ArrayIndexValid)
{
    int a[2];
    EXPECT_THROW(   ASSERT_ARRAY_INDEX_VALID(a, -1), std::runtime_error);
    EXPECT_NO_THROW(ASSERT_ARRAY_INDEX_VALID(a, 0));
    EXPECT_NO_THROW(ASSERT_ARRAY_INDEX_VALID(a, 1));
    EXPECT_THROW(   ASSERT_ARRAY_INDEX_VALID(a, 2), std::runtime_error);
}

TEST(AfxAssertTest, PowerOfTwo)
{
    EXPECT_THROW(   ASSERT_POWER_OF_TWO(-2), std::runtime_error);
    EXPECT_THROW(   ASSERT_POWER_OF_TWO(-1), std::runtime_error);
    EXPECT_NO_THROW(ASSERT_POWER_OF_TWO(0));
    EXPECT_NO_THROW(ASSERT_POWER_OF_TWO(0x1));
    EXPECT_NO_THROW(ASSERT_POWER_OF_TWO(0x2));
    EXPECT_THROW(   ASSERT_POWER_OF_TWO(3), std::runtime_error);
    EXPECT_NO_THROW(ASSERT_POWER_OF_TWO(0x4));
    EXPECT_NO_THROW(ASSERT_POWER_OF_TWO(0x80));
    EXPECT_THROW(   ASSERT_POWER_OF_TWO(0xc0), std::runtime_error);
    EXPECT_NO_THROW(ASSERT_POWER_OF_TWO(0x100));
    EXPECT_NO_THROW(ASSERT_POWER_OF_TWO(0x8000));
    EXPECT_THROW(   ASSERT_POWER_OF_TWO(0xc000), std::runtime_error);
    EXPECT_NO_THROW(ASSERT_POWER_OF_TWO(0x10000));
    EXPECT_NO_THROW(ASSERT_POWER_OF_TWO(0x80000000));
    EXPECT_THROW(   ASSERT_POWER_OF_TWO(0xc0000000), std::runtime_error);
    EXPECT_NO_THROW(ASSERT_POWER_OF_TWO(0x100000000));
    EXPECT_NO_THROW(ASSERT_POWER_OF_TWO(0x8000000000000000));
}

#else // defined(_DEBUG)

class AfxAssertTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        GTEST_SKIP();
    }
};

TEST_F(AfxAssertTest, Release)
{
}
#endif // defined(_DEBUG)
