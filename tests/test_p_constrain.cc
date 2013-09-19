#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "elvin/patterns/p_constrain.h"

#include "utils.h"

using namespace testing;
using namespace elvin;

TEST(PConstrain, Exact) {
    auto pattern = PConstrain(0.1f, 0.4f);
    auto next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(0.1f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(0.1f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(0.1f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(0.1f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_FALSE(next.exists);

    next = pattern.next();
    EXPECT_FALSE(next.exists);
}

TEST(PConstrain, Over) {
    auto pattern = PConstrain(0.15f, 0.4f);
    auto next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(0.15f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(0.15f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(0.1f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_FALSE(next.exists);

    next = pattern.next();
    EXPECT_FALSE(next.exists);
}

TEST(PConstrain, Under) {
    auto pattern = PConstrain(TestPattern(0.1f, 1), 0.4f);
    auto next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(0.1f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(0.3f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_FALSE(next.exists);

    next = pattern.next();
    EXPECT_FALSE(next.exists);
}

TEST(PConstrain, Threshold) {
    auto pattern = PConstrain(0.1f, 0.4f, 0.25f);
    auto next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(0.1f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(0.1f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(0.2f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral); 

    next = pattern.next();
    EXPECT_FALSE(next.exists);

    next = pattern.next();
    EXPECT_FALSE(next.exists);
}


