#include "Misc/Probability.h"

#include "gtest/gtest.h"

TEST(ProbabilityTest, Factorial)
{
    EXPECT_EQ(factorial( 0), 1);
    EXPECT_EQ(factorial( 1), 1);
    EXPECT_EQ(factorial( 2), 2);
    EXPECT_EQ(factorial( 3), 6);
    EXPECT_EQ(factorial(20), 2432902008176640000);
}

TEST(ProbabilityTest, Permutations)
{
    EXPECT_EQ(permutations(0,   0),  1);
    EXPECT_EQ(permutations(20,  0),  1);
    EXPECT_EQ(permutations(20, 20), 2432902008176640000);
    EXPECT_EQ(permutations(52,  5), 311875200);
    EXPECT_EQ(permutations( 6,  3), 120);
}

TEST(ProbabilityTest, Combinations)
{
    EXPECT_EQ(combinations(0,   0),       1);
    EXPECT_EQ(combinations(20,  0),       1);
    EXPECT_EQ(combinations(20, 20),       1);
    EXPECT_EQ(combinations(52,  5), 2598960);
    EXPECT_EQ(combinations(6,   3),      20);
}

TEST(ProbabilityTest, Multisets)
{
    EXPECT_EQ(multisets( 1,  0),    1);
    EXPECT_EQ(multisets( 1, 20),    1);
    EXPECT_EQ(multisets(20,  1),   20);
    EXPECT_EQ(multisets( 2,  3),    4);
    EXPECT_EQ(multisets( 4, 18), 1330);
}
