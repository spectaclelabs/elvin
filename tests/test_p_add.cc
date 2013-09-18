#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "elvin/operators/p_operator.h"

#include "utils.h"

using namespace testing;
using namespace elvin;
using namespace operators;

TEST(POperator, AddPattern) {
    auto pattern = TestPattern() + TestPattern();

    auto next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(0.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(2.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(4.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);
}

TEST(POperator, AddFloatA) {
    auto pattern = TestPattern() + 1.f;

    auto next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(1.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(2.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(3.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);
}

TEST(POperator, AddFloatB) {
    auto pattern = 1.f + TestPattern();
   
    auto next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(1.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(2.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(3.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);
}

TEST(POperator, AddDifferentLength) {
    auto pattern = TestPattern(0, 2) +
                   TestPattern(0, 3);

    auto next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(0.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(2.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_FALSE(next.exists);

    next = pattern.next();
    EXPECT_FALSE(next.exists);
}

