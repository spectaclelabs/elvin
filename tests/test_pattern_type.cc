#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "elvin/pattern_type.h"

#include "utils.h"

using namespace elvin;
using namespace testing;

TEST(PatternType, Literal) {
    bool same = std::is_same<PatternType<float>, PLiteral>::value;
    EXPECT_TRUE(same);
}

TEST(PatternType, LiteralRef) {
    bool same = std::is_same<PatternType<float&>, PLiteral>::value;
    EXPECT_TRUE(same);
}

TEST(PatternType, Pattern) {
    bool same = std::is_same<
                    PatternType<TestPattern>,
                    TestPattern
                >::value;
    EXPECT_TRUE(same);
}

TEST(PatternType, PatternRef) {
    bool same = std::is_same<
                    PatternType<TestPattern &>,
                    TestPattern
                >::value;
    EXPECT_TRUE(same);
}

