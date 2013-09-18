#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "elvin/patterns/p_arithmetic.h"

#include "utils.h"

using namespace testing;
using namespace elvin;

TEST(PArithmetic, SimpleValues) {
    auto pattern = PArithmetic(5, 2, 3);
    auto next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(5.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(7.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(9.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_FALSE(next.exists);

    next = pattern.next();
    EXPECT_FALSE(next.exists);
}

TEST(PArithmetic, Reset) {
    auto pattern = PArithmetic(5, 2, 3);
    auto next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(5.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(7.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    pattern.reset();
    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(5.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(7.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(9.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_FALSE(next.exists);

    next = pattern.next();
    EXPECT_FALSE(next.exists);
}

TEST(PArithmetic, VariableSteps) {
    auto pattern = PArithmetic(5, TestPattern(1, 2), 3);
    auto next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(5.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(6.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(8.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_FALSE(next.exists);

    next = pattern.next();
    EXPECT_FALSE(next.exists);
}

TEST(PArithmetic, ShortVariableSteps) {
    auto pattern = PArithmetic(5, TestPattern(1, 1), 3);
    auto next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(5.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(6.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_FALSE(next.exists);

    next = pattern.next();
    EXPECT_FALSE(next.exists);
}

