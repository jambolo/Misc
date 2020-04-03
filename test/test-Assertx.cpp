#include "Misc/Assertx.h"
#include "Misc/Etc.h"
#include "gtest/gtest.h"

#if defined(_DEBUG)

TEST(AssertxTest, DISABLED_Limits)
{
    EXPECT_NO_THROW(assert_limits(0, 0, 0));
    EXPECT_NO_THROW(assert_limits(0, 0, 1));
    EXPECT_NO_THROW(assert_limits(0, 0, 2));
    EXPECT_THROW(assert_limits(0, 1, 0), std::runtime_error);
    EXPECT_NO_THROW(assert_limits(0, 1, 1));
    EXPECT_NO_THROW(assert_limits(0, 1, 2));
    EXPECT_THROW(assert_limits(0, 2, 0), std::runtime_error);
    EXPECT_THROW(assert_limits(0, 2, 1), std::runtime_error);
    EXPECT_NO_THROW(assert_limits(0, 2, 2));
    EXPECT_THROW(assert_limits(1, 0, 0), std::runtime_error);
    EXPECT_THROW(assert_limits(1, 0, 1), std::runtime_error);
    EXPECT_THROW(assert_limits(1, 0, 2), std::runtime_error);
    EXPECT_THROW(assert_limits(1, 1, 0), std::runtime_error);
    EXPECT_NO_THROW(assert_limits(1, 1, 1));
    EXPECT_NO_THROW(assert_limits(1, 1, 2));
    EXPECT_THROW(assert_limits(1, 2, 0), std::runtime_error);
    EXPECT_THROW(assert_limits(1, 2, 1), std::runtime_error);
    EXPECT_NO_THROW(assert_limits(1, 2, 2));
    EXPECT_THROW(assert_limits(2, 0, 0), std::runtime_error);
    EXPECT_THROW(assert_limits(2, 0, 1), std::runtime_error);
    EXPECT_THROW(assert_limits(2, 0, 2), std::runtime_error);
    EXPECT_THROW(assert_limits(2, 1, 0), std::runtime_error);
    EXPECT_THROW(assert_limits(2, 1, 1), std::runtime_error);
    EXPECT_THROW(assert_limits(2, 1, 2), std::runtime_error);
    EXPECT_THROW(assert_limits(2, 2, 0), std::runtime_error);
    EXPECT_THROW(assert_limits(2, 2, 1), std::runtime_error);
    EXPECT_NO_THROW(assert_limits(2, 2, 2));
}

TEST(AssertxTest, DISABLED_MemsetValid)
{
    char * char_pointer = 0;
    EXPECT_NO_THROW(assert_memset_valid(char_pointer, 0));
    EXPECT_NO_THROW(assert_memset_valid(char_pointer, -1));
    EXPECT_NO_THROW(assert_memset_valid(char_pointer, -128));
    EXPECT_NO_THROW(assert_memset_valid(char_pointer, 255));
    EXPECT_THROW(assert_memset_valid(char_pointer, -129), std::runtime_error);
    EXPECT_THROW(assert_memset_valid(char_pointer, 256), std::runtime_error);

    int * int_pointer = 0;
    EXPECT_NO_THROW(assert_memset_valid(int_pointer, 0));
    EXPECT_NO_THROW(assert_memset_valid(int_pointer, -1));
    EXPECT_THROW(assert_memset_valid(int_pointer, -128), std::runtime_error);
    EXPECT_THROW(assert_memset_valid(int_pointer, 255), std::runtime_error);
    EXPECT_THROW(assert_memset_valid(int_pointer, -129), std::runtime_error);
    EXPECT_THROW(assert_memset_valid(int_pointer, 256), std::runtime_error);
}


TEST(AssertxTest, DISABLED_PointerValid)
{
    int x;
    int * nonnullpointer = &x;
    int * nullpointer = nullptr;
    EXPECT_NO_THROW(assert_pointer_valid(nonnullpointer, false));
    EXPECT_NO_THROW(assert_pointer_valid(nonnullpointer, true));
    EXPECT_THROW(   assert_pointer_valid(nullpointer, false), std::runtime_error);
    EXPECT_NO_THROW(assert_pointer_valid(nullpointer, true));
    EXPECT_THROW(   assert_pointer_valid(0, false), std::runtime_error);
    EXPECT_NO_THROW(assert_pointer_valid(0, true));
}

TEST(AssertxTest, DISABLED_AlmostEqual)
{
    EXPECT_THROW(assert_almost_equal(98.0, 100.0, 0.01), std::runtime_error);
    EXPECT_THROW(assert_almost_equal(100.0, 98.0, 0.01), std::runtime_error);
    EXPECT_THROW(assert_almost_equal(98.0, 100.0, -0.01), std::runtime_error);
    EXPECT_THROW(assert_almost_equal(100.0, 98.0, -0.01), std::runtime_error);
    EXPECT_THROW(assert_almost_equal(98.0, -100.0, 0.01), std::runtime_error);
    EXPECT_THROW(assert_almost_equal(100.0, -98.0, 0.01), std::runtime_error);
    EXPECT_THROW(assert_almost_equal(98.0, -100.0, -0.01), std::runtime_error);
    EXPECT_THROW(assert_almost_equal(100.0, -98.0, -0.01), std::runtime_error);
    EXPECT_THROW(assert_almost_equal(-98.0, 100.0, 0.01), std::runtime_error);
    EXPECT_THROW(assert_almost_equal(-100.0, 98.0, 0.01), std::runtime_error);
    EXPECT_THROW(assert_almost_equal(-98.0, 100.0, -0.01), std::runtime_error);
    EXPECT_THROW(assert_almost_equal(-100.0, 98.0, -0.01), std::runtime_error);
    EXPECT_THROW(assert_almost_equal(-98.0, -100.0, 0.01), std::runtime_error);
    EXPECT_THROW(assert_almost_equal(-100.0, -98.0, 0.01), std::runtime_error);
    EXPECT_THROW(assert_almost_equal(-98.0, -100.0, -0.01), std::runtime_error);
    EXPECT_THROW(assert_almost_equal(-100.0, -98.0, -0.01), std::runtime_error);

    EXPECT_NO_THROW(assert_almost_equal(99.0, 100.0, 0.02));
    EXPECT_NO_THROW(assert_almost_equal(100.0, 99.0, 0.02));
    EXPECT_NO_THROW(assert_almost_equal(99.0, 100.0, -0.02));
    EXPECT_NO_THROW(assert_almost_equal(100.0, 99.0, -0.02));
    EXPECT_THROW(assert_almost_equal(99.0, -100.0, 0.02), std::runtime_error);
    EXPECT_THROW(assert_almost_equal(100.0, -99.0, 0.02), std::runtime_error);
    EXPECT_THROW(assert_almost_equal(99.0, -100.0, -0.02), std::runtime_error);
    EXPECT_THROW(assert_almost_equal(100.0, -99.0, -0.02), std::runtime_error);
    EXPECT_THROW(assert_almost_equal(-99.0, 100.0, 0.02), std::runtime_error);
    EXPECT_THROW(assert_almost_equal(-100.0, 99.0, 0.02), std::runtime_error);
    EXPECT_THROW(assert_almost_equal(-99.0, 100.0, -0.02), std::runtime_error);
    EXPECT_THROW(assert_almost_equal(-100.0, 99.0, -0.02), std::runtime_error);
    EXPECT_NO_THROW(assert_almost_equal(-99.0, -100.0, 0.02));
    EXPECT_NO_THROW(assert_almost_equal(-100.0, -99.0, 0.02));
    EXPECT_NO_THROW(assert_almost_equal(-99.0, -100.0, -0.02));
    EXPECT_NO_THROW(assert_almost_equal(-100.0, -99.0, -0.02));

    EXPECT_NO_THROW(assert_almost_equal(0.0, 0.0, 0.0));
    EXPECT_NO_THROW(assert_almost_equal(0.0, 0.0, 0.01));
}

TEST(AssertxTest, DISABLED_ArrayIndexValid)
{
    int a[2];
    EXPECT_THROW(assert_array_index_valid(a, -1), std::runtime_error);
    EXPECT_NO_THROW(assert_array_index_valid(a, 0));
    EXPECT_NO_THROW(assert_array_index_valid(a, 1));
    EXPECT_THROW(assert_array_index_valid(a, 2), std::runtime_error);
}

TEST(AssertxTest, DISABLED_PowerOfTwo)
{
    EXPECT_THROW(assert_power_of_two(-2), std::runtime_error);
    EXPECT_THROW(assert_power_of_two(-1), std::runtime_error);
    EXPECT_NO_THROW(assert_power_of_two(0));
    EXPECT_NO_THROW(assert_power_of_two(0x1));
    EXPECT_NO_THROW(assert_power_of_two(0x2));
    EXPECT_THROW(assert_power_of_two(3), std::runtime_error);
    EXPECT_NO_THROW(assert_power_of_two(0x4));
    EXPECT_NO_THROW(assert_power_of_two(0x80));
    EXPECT_THROW(assert_power_of_two(0xc0), std::runtime_error);
    EXPECT_NO_THROW(assert_power_of_two(0x100));
    EXPECT_NO_THROW(assert_power_of_two(0x8000));
    EXPECT_THROW(assert_power_of_two(0xc000), std::runtime_error);
    EXPECT_NO_THROW(assert_power_of_two(0x10000));
    EXPECT_NO_THROW(assert_power_of_two(0x80000000));
    EXPECT_THROW(assert_power_of_two(0xc0000000), std::runtime_error);
    EXPECT_NO_THROW(assert_power_of_two(0x100000000));
    EXPECT_NO_THROW(assert_power_of_two(0x8000000000000000));
}

#else // defined(_DEBUG)

class AssertxTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        GTEST_SKIP();
    }
};

TEST_F(AssertxTest, Release)
{
}
#endif // defined(_DEBUG)
