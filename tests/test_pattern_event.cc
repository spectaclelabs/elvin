#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "elvin/pattern_event.h"
#include "elvin/patterns/p_literal.h"
#include "elvin/collections/p_tuple.h"

#include "utils.h"

using namespace elvin;
using namespace elvin::collections;
using namespace testing;

float args[2];
bool called;

void noArgs() {
    called = true;
}

void oneArg(float arg) {
    called = true;
    args[0] = arg;
}

void twoArgs(float arg0, float arg1) {
    called = true;
    args[0] = arg0;
    args[1] = arg1;
}

class PatternEventTest : public Test {
public:
    PatternEventTest() {
        reset();
    }

    void reset() {
        args[0] = 0.f;
        args[1] = 0.f;
        called = false;
    }
};

TEST_F(PatternEventTest, NoArgs) {
    PatternEvent<PTupleT<>, PLiteral>
        event(0, PTuple(), PLiteral(1.f), noArgs);

    TimeData timeData(60);

    bool success = event.process(timeData);
    EXPECT_TRUE(called);
    EXPECT_TRUE(success);
    EXPECT_THAT(args[0], FloatEq(0.f));
    EXPECT_THAT(args[1], FloatEq(0.f));
}

TEST_F(PatternEventTest, OneArg) {
    PatternEvent<PTupleT<TestPattern>, PLiteral, float>
        event(0, PTuple(TestPattern()), PLiteral(1.f), oneArg);
    TimeData timeData(60); 

    bool success = event.process(timeData);
    EXPECT_TRUE(called);
    EXPECT_TRUE(success);
    EXPECT_THAT(args[0], FloatEq(0.f));
    EXPECT_THAT(args[1], FloatEq(0.f));

    reset();
    success = event.process(timeData);
    EXPECT_TRUE(called);
    EXPECT_TRUE(success);
    EXPECT_THAT(args[0], FloatEq(1.f));
    EXPECT_THAT(args[1], FloatEq(0.f));

    reset();
    success = event.process(timeData);
    EXPECT_TRUE(called);
    EXPECT_TRUE(success);
    EXPECT_THAT(args[0], FloatEq(2.f));
    EXPECT_THAT(args[1], FloatEq(0.f));
}

TEST_F(PatternEventTest, TwoArgs) {
    auto patterns = PTuple(TestPattern(), TestPattern(3));
    PatternEvent<PTupleT<TestPattern, TestPattern>, PLiteral, float, float>
        event(0, std::move(patterns), PLiteral(1.f), twoArgs);
    TimeData timeData(60); 

    bool success = event.process(timeData);
    EXPECT_TRUE(called);
    EXPECT_TRUE(success);
    EXPECT_THAT(args[0], FloatEq(0.f));
    EXPECT_THAT(args[1], FloatEq(3.f));

    reset();
    success = event.process(timeData);
    EXPECT_TRUE(called);
    EXPECT_TRUE(success);
    EXPECT_THAT(args[0], FloatEq(1.f));
    EXPECT_THAT(args[1], FloatEq(4.f));

    reset();
    success = event.process(timeData);
    EXPECT_TRUE(called);
    EXPECT_TRUE(success);
    EXPECT_THAT(args[0], FloatEq(2.f));
    EXPECT_THAT(args[1], FloatEq(5.f));
}

TEST_F(PatternEventTest, PatternShort) {
    auto patterns = PTuple(TestPattern(), TestPattern(3, 2));
    PatternEvent<decltype(patterns), PLiteral, float, float>
        event(0, std::move(patterns), PLiteral(1.f), twoArgs);

    TimeData timeData(60); 

    bool success = event.process(timeData);
    EXPECT_TRUE(called);
    EXPECT_TRUE(success);
    EXPECT_THAT(args[0], FloatEq(0.f));
    EXPECT_THAT(args[1], FloatEq(3.f));

    reset();
    success = event.process(timeData);
    EXPECT_TRUE(called);
    EXPECT_TRUE(success);
    EXPECT_THAT(args[0], FloatEq(1.f));
    EXPECT_THAT(args[1], FloatEq(4.f));

    reset();
    success = event.process(timeData);
    EXPECT_FALSE(called);
    EXPECT_FALSE(success);
}

TEST_F(PatternEventTest, DurationShort) {
    auto patterns = PTuple(TestPattern());
    PatternEvent<decltype(patterns), TestPattern, float>
        event(0, std::move(patterns), TestPattern(1.f, 2.f), oneArg);

    TimeData timeData(60);

    bool success = event.process(timeData);
    EXPECT_TRUE(called);
    EXPECT_TRUE(success);
    EXPECT_THAT(args[0], FloatEq(0.f));

    reset();
    success = event.process(timeData);
    EXPECT_TRUE(called);
    EXPECT_TRUE(success);
    EXPECT_THAT(args[0], FloatEq(1.f));

    reset();
    success = event.process(timeData);
    EXPECT_FALSE(called);
    EXPECT_FALSE(success);
}

