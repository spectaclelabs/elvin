#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "elvin/patterns/p_stutter.h"

#include "utils.h"

using namespace testing;
using namespace elvin;

TEST(PStutter, SimpleStutter) {
    auto p = TestPattern(1.f, 3);
    auto r = TestPattern(1.f, 3);
    auto pattern = PStutter(std::move(p), std::move(r));

    auto next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(1.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(2.f));
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

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(3.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);


    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(3.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_FALSE(next.exists);

    next = pattern.next();
    EXPECT_FALSE(next.exists);
}

TEST(PStutter, PatternShort) {
    auto p = TestPattern(1.f, 2);
    auto r = TestPattern(1.f, 4);
    auto pattern = PStutter(std::move(p), std::move(r));

    auto next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(1.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(2.f));
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

TEST(PStutter, RepeatsShort) {
    auto p = TestPattern(1.f, 4);
    auto r = TestPattern(1.f, 2);
    auto pattern = PStutter(std::move(p), std::move(r));

    auto next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(1.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(2.f));
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

TEST(PStutter, Reset) {
    auto p = TestPattern(1.f, 2);
    auto r = TestPattern(1.f, 2);
    auto pattern = PStutter(std::move(p), std::move(r));

    auto next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(1.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(2.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    pattern.reset();

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(1.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(2.f));
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

