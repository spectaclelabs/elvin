#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "elvin/patterns/p_random.h"

using namespace elvin;
using namespace testing;

TEST(PRandom, Values) {
    auto pattern = PRandom(4.f, 10.f, 3);

    auto next = pattern.next();
    EXPECT_THAT(next.value, AllOf(Gt(4.f), Lt(10.f)));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, AllOf(Gt(4.f), Lt(10.f)));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, AllOf(Gt(4.f), Lt(10.f)));
    EXPECT_TRUE(next.exists);   
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_FALSE(next.exists);   

    next = pattern.next();
    EXPECT_FALSE(next.exists);   

}

TEST(PRandom, Reset) {
    auto pattern = PRandom(4.f, 10.f, 3);

    auto next = pattern.next();
    EXPECT_THAT(next.value, AllOf(Gt(4.f), Lt(10.f)));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, AllOf(Gt(4.f), Lt(10.f)));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);
    
    pattern.reset();

    next = pattern.next();
    EXPECT_THAT(next.value, AllOf(Gt(4.f), Lt(10.f)));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, AllOf(Gt(4.f), Lt(10.f)));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_THAT(next.value, AllOf(Gt(4.f), Lt(10.f)));
    EXPECT_TRUE(next.exists);
    EXPECT_FALSE(next.isLiteral);

    next = pattern.next();
    EXPECT_FALSE(next.exists);

    next = pattern.next();
    EXPECT_FALSE(next.exists);
}

