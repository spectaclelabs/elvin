#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "elvin/patterns/p_choose.h"
#include "elvin/collections/p_tuple.h"

#include "utils.h"

using namespace testing;
using namespace elvin;

TEST(PChoose, SimpleValues) {
    auto pattern = PChoose(PTuple(1.f, 2.f, 3.f), 3);
    auto next = pattern.next();
    EXPECT_THAT(next.value, AnyOf(FloatEq(1.f), FloatEq(2.f), FloatEq(3.f)));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, AnyOf(FloatEq(1.f), FloatEq(2.f), FloatEq(3.f)));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, AnyOf(FloatEq(1.f), FloatEq(2.f), FloatEq(3.f)));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_FALSE(next.exists);

    next = pattern.next();
    EXPECT_FALSE(next.exists);
}

TEST(PChoose, PatternValues) {
    auto pattern = PChoose(PTuple(TestPattern(1, 3)), 2);
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

    next = pattern.next(); 
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

    next = pattern.next();
    EXPECT_FALSE(next.exists);

    next = pattern.next();
    EXPECT_FALSE(next.exists);
}

TEST(PChoose, Reset) {
    auto pattern = PChoose(PTuple(TestPattern(1, 3)), 1);
    auto next = pattern.next(); 
    EXPECT_THAT(next.value, FloatEq(1.f));
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
    EXPECT_THAT(next.value, FloatEq(3.f));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_FALSE(next.exists);   

    next = pattern.next();
    EXPECT_FALSE(next.exists);
}

