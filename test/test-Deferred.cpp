#include "Misc/Deferred.h"

#include "gtest/gtest.h"

TEST(DeferredTest, ConstructDefault)
{
    EXPECT_FALSE(Deferred<int>().deferred());
    EXPECT_EQ(Deferred<int>().value(), int());
}

TEST(DeferredTest, Construct)
{
    EXPECT_TRUE(Deferred<int>(1).deferred());
    EXPECT_EQ(Deferred<int>(1).value(), 1);
}

TEST(DeferredTest, CopyConstruct)
{
    Deferred<int> unassigned;
    EXPECT_EQ(Deferred<int>(unassigned).deferred(), unassigned.value());
    EXPECT_EQ(Deferred<int>(unassigned).value(), unassigned.value());

    Deferred<int> assigned(1);
    EXPECT_EQ(Deferred<int>(assigned).deferred(), assigned.deferred());
    EXPECT_EQ(Deferred<int>(assigned).value(), assigned.value());
}

TEST(DeferredTest, Assign)
{
    Deferred<int> u;
    Deferred<int> unassigned;
    Deferred<int> x(1);
    Deferred<int> y(2);

    u = unassigned;
    EXPECT_EQ(u.deferred(), unassigned.deferred());
    EXPECT_EQ(u.value(), unassigned.deferred());
    u = x;
    EXPECT_EQ(u.deferred(), x.deferred());
    EXPECT_EQ(u.value(), x.value());
    u = y;
    EXPECT_EQ(u.deferred(), y.deferred());
    EXPECT_EQ(u.value(), y.value());
    u = unassigned;
    EXPECT_EQ(u.deferred(), unassigned.deferred());
    EXPECT_EQ(u.value(), unassigned.deferred());
}

TEST(DeferredTest, AssignValue)
{
    Deferred<int> u;
    Deferred<int> unassigned;
    Deferred<int> x(1);
    Deferred<int> y(2);

    u = 1;
    EXPECT_TRUE(u.deferred());
    EXPECT_EQ(u.value(), 1);
    u = 2;
    EXPECT_TRUE(u.deferred());
    EXPECT_EQ(u.value(), 2);
}

TEST(DeferredTest, ConversionOperator)
{
    int           u = ~int();
    Deferred<int> unassigned;
    Deferred<int> x(1);

    u = (int)x;
    EXPECT_EQ(u, x.value());
    u = (int)unassigned;
    EXPECT_EQ(u, unassigned.value());
}
