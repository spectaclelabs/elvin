#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "elvin/patterns/p_interlace.h"
#include "elvin/collections/p_tuple.h"

#include "utils.h"

using namespace testing;
using namespace elvin;

TEST(PInterlace, EqualSize) {
    auto p1 = TestPattern(1, 2);
    auto p2 = TestPattern(3, 2);
    auto pattern = PInterlace(PTuple(std::move(p1), std::move(p2)));

    auto next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(1.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(3.f));
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

    next = pattern.next();
    EXPECT_FALSE(next.exists);

    next = pattern.next();
    EXPECT_FALSE(next.exists);
}

TEST(PInterlace, UnequalSize) {
    auto p1 = TestPattern(1, 2);
    auto p2 = TestPattern(3, 4);
    auto pattern = PInterlace(PTuple(std::move(p1), std::move(p2)));

    auto next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(1.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(3.f));
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

    next = pattern.next();
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

