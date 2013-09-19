#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "elvin/patterns/p_literal.h"

using namespace elvin;
using namespace testing;

TEST(PLiteral, FloatValue) {
    PLiteral pattern(0.4f);

    auto next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(0.4f));
    EXPECT_TRUE(next.exists);
    EXPECT_TRUE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, FloatEq(0.4f));
    EXPECT_TRUE(next.exists);
    EXPECT_TRUE(next.isLiteral);
}

