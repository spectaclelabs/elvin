#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "elvin/collections/p_vector.h"
#include "elvin/collections/interface.h"

#include "utils.h"

using namespace elvin;
using namespace elvin::collections;
using namespace elvin::collections::interface;
using namespace testing;

TEST(PVector, AdvancesCorrectly) {
    auto vector = PVector(TestPattern(), TestPattern(), TestPattern());

    // Advance the first vector a few times
    EXPECT_THAT(next(vector, 0).value, FloatEq(0.f));
    EXPECT_THAT(next(vector, 0).value, FloatEq(1.f));
    EXPECT_THAT(next(vector, 0).value, FloatEq(2.f));
    EXPECT_THAT(next(vector, 0).value, FloatEq(3.f));

    // Advance the second and third vectors
    EXPECT_THAT(next(vector, 1).value, FloatEq(0.f));
    EXPECT_THAT(next(vector, 2).value, FloatEq(0.f));
    EXPECT_THAT(next(vector, 1).value, FloatEq(1.f));
    EXPECT_THAT(next(vector, 2).value, FloatEq(1.f));

    // Advance the first vector once more
    EXPECT_THAT(next(vector, 0).value, FloatEq(4.f));
}

TEST(PVector, ResetsCorrectly) {
    auto vector = PVector(TestPattern(), TestPattern(), TestPattern());

    // Advance the each vector a few times
    EXPECT_THAT(next(vector, 0).value, FloatEq(0.f));
    EXPECT_THAT(next(vector, 1).value, FloatEq(0.f));
    EXPECT_THAT(next(vector, 2).value, FloatEq(0.f));
    EXPECT_THAT(next(vector, 0).value, FloatEq(1.f));
    EXPECT_THAT(next(vector, 1).value, FloatEq(1.f));
    EXPECT_THAT(next(vector, 2).value, FloatEq(1.f));
    
    // Reset and tick the first one
    reset(vector, 0);
    EXPECT_THAT(next(vector, 0).value, FloatEq(0.f));
    EXPECT_THAT(next(vector, 0).value, FloatEq(1.f));
    EXPECT_THAT(next(vector, 0).value, FloatEq(2.f));

    
    // Reset and tick the second one
    reset(vector, 1);
    EXPECT_THAT(next(vector, 1).value, FloatEq(0.f));
    EXPECT_THAT(next(vector, 1).value, FloatEq(1.f));

    // Make sure the others are still fine
    EXPECT_THAT(next(vector, 0).value, FloatEq(3.f));
    EXPECT_THAT(next(vector, 2).value, FloatEq(2.f));
}

TEST(PVector, Copies) {
    auto vectorA = PVector(TestPattern(), TestPattern(), TestPattern());
    auto vectorB = vectorA;

    // Advance the first vector a few times
    EXPECT_THAT(next(vectorA, 0).value, FloatEq(0.f));
    EXPECT_THAT(next(vectorA, 0).value, FloatEq(1.f));
    EXPECT_THAT(next(vectorA, 0).value, FloatEq(2.f));

    // Advance the second vector - they should be different
    EXPECT_THAT(next(vectorB, 0).value, FloatEq(0.f));
    EXPECT_THAT(next(vectorB, 0).value, FloatEq(1.f));
    EXPECT_THAT(next(vectorB, 0).value, FloatEq(2.f));
}

