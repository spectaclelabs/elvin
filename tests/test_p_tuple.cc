#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "elvin/collections/p_tuple.h"
#include "elvin/collections/interface.h"

#include "utils.h"

using namespace elvin;
using namespace elvin::collections;
using namespace elvin::collections::interface;
using namespace testing;

TEST(PTuple, Types) {
    typedef PTupleFT<float, TestPattern, TestPattern, float> typeA;
    typedef PTupleT<PLiteral, TestPattern, TestPattern, PLiteral> typeB;
    bool same = std::is_same<typeA, typeB>::value;
    EXPECT_TRUE(same);
}


TEST(PTuple, InitializeWithRValues) {
    auto tuple = PTuple(2.f, TestPattern());

    typedef decltype(tuple) typeA;
    typedef PTupleT<PLiteral, TestPattern> typeB;
    bool same = std::is_same<typeA, typeB>::value;
    EXPECT_TRUE(same);
}

TEST(PTuple, InitializeWithLValues) {
    float literal = 2.f;
    TestPattern pattern;
    auto tuple = PTuple(literal, pattern);

    typedef decltype(tuple) typeA;
    typedef PTupleT<PLiteral, TestPattern> typeB;
    bool same = std::is_same<typeA, typeB>::value;
    EXPECT_TRUE(same);
}

TEST(PTuple, InitializeWithMixedValues) {
    float literal = 2.f;
    TestPattern pattern;
    auto tuple = PTuple(literal, pattern, 3.f, TestPattern());

    typedef decltype(tuple) typeA;
    typedef PTupleT<PLiteral, TestPattern, PLiteral, TestPattern> typeB;
    bool same = std::is_same<typeA, typeB>::value;
    EXPECT_TRUE(same);
}

TEST(PTuple, InitializeAllFloats) {
    auto tuple = PTuple(1.f, 2.f, 3.f, 4.f);

    typedef decltype(tuple) typeA;
    typedef PTupleT<PLiteral, PLiteral, PLiteral, PLiteral> typeB;
    bool same = std::is_same<typeA, typeB>::value;
    EXPECT_TRUE(same);
}


TEST(PTuple, AdvancesCorrectly) {
    auto tuple = PTuple(TestPattern(), TestPattern(), TestPattern());

    // Advance the first tuple a few times
    EXPECT_THAT(next(tuple, 0).value, FloatEq(0.f));
    EXPECT_THAT(next(tuple, 0).value, FloatEq(1.f));
    EXPECT_THAT(next(tuple, 0).value, FloatEq(2.f));
    EXPECT_THAT(next(tuple, 0).value, FloatEq(3.f));

    // Advance the second and third tuples
    EXPECT_THAT(next(tuple, 1).value, FloatEq(0.f));
    EXPECT_THAT(next(tuple, 2).value, FloatEq(0.f));
    EXPECT_THAT(next(tuple, 1).value, FloatEq(1.f));
    EXPECT_THAT(next(tuple, 2).value, FloatEq(1.f));

    // Advance the first tuple once more
    EXPECT_THAT(next(tuple, 0).value, FloatEq(4.f));
}

TEST(PTuple, ResetsCorrectly) {
    auto tuple = PTuple(TestPattern(), TestPattern(), TestPattern());

    // Advance the each tuple a few times
    EXPECT_THAT(next(tuple, 0).value, FloatEq(0.f));
    EXPECT_THAT(next(tuple, 1).value, FloatEq(0.f));
    EXPECT_THAT(next(tuple, 2).value, FloatEq(0.f));
    EXPECT_THAT(next(tuple, 0).value, FloatEq(1.f));
    EXPECT_THAT(next(tuple, 1).value, FloatEq(1.f));
    EXPECT_THAT(next(tuple, 2).value, FloatEq(1.f));
    
    // Reset and tick the first one
    reset(tuple, 0);
    EXPECT_THAT(next(tuple, 0).value, FloatEq(0.f));
    EXPECT_THAT(next(tuple, 0).value, FloatEq(1.f));
    EXPECT_THAT(next(tuple, 0).value, FloatEq(2.f));

    
    // Reset and tick the second one
    reset(tuple, 1);
    EXPECT_THAT(next(tuple, 1).value, FloatEq(0.f));
    EXPECT_THAT(next(tuple, 1).value, FloatEq(1.f));

    // Make sure the others are still fine
    EXPECT_THAT(next(tuple, 0).value, FloatEq(3.f));
    EXPECT_THAT(next(tuple, 2).value, FloatEq(2.f));
}

