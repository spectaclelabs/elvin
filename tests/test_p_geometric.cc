#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "elvin/patterns/p_geometric.h"

#include "utils.h"

using namespace testing;
using namespace elvin;

TEST(PGeometric, SimpleValues) {
    auto pattern = PGeometric(5, 2, 3);
    auto next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(5.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(10.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(20.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_FALSE(next.exists);

    next = pattern.next();
    EXPECT_FALSE(next.exists);
}

TEST(PGeometric, Reset) {
    auto pattern = PGeometric(5, 2, 3);
    auto next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(5.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(10.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    pattern.reset();
    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(5.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(10.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(20.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_FALSE(next.exists);

    next = pattern.next();
    EXPECT_FALSE(next.exists);
}

TEST(PGeometric, VariableSteps) {
    auto pattern = PGeometric(5, TestPattern(1.f, 2), 3);
    auto next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(5.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(5.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(10.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_FALSE(next.exists);

    next = pattern.next();
    EXPECT_FALSE(next.exists);
}

TEST(PGeometric, ShortVariableSteps) {
    auto pattern = PGeometric(5, TestPattern(1.f, 1), 3);
    auto next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(5.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(5.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_FALSE(next.exists);

    next = pattern.next();
    EXPECT_FALSE(next.exists);
}

