#ifndef ELVIN_TEST_UTILS_H
#define ELVIN_TEST_UTILS_H

#include "elvin/pattern.h"
#include "elvin/pattern_value.h"

class TestPattern : public elvin::Pattern {
public:
    TestPattern(float start=0, uint32_t limit=0) :
            start(start), count(start), limit(limit), position(0) {
    }

    elvin::PatternValue next() {
        elvin::PatternValue next;
        if (limit != 0 && position >= limit) {
            return next;
        }
        next.value = count;
        next.exists = true;
        next.isLiteral = false;
        count++;
        position++;
        return next;
    }

    void reset() {
        count = start;
        position = 0;
    }

    TestPattern* clone() const {
        return new TestPattern(*this);
    }

private:
    float start;
    float count;
    uint32_t limit;
    uint32_t position;
};

#endif
