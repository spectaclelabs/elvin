#ifndef ELVIN_P_CONSTRAIN_H
#define ELVIN_P_CONSTRAIN_H

#include <utility>
#include <tuple>

#include "pattern.h"
#include "pattern_t.h"

namespace elvin {

class PConstrainT : public PatternT {
public:
    virtual NextTuple next() {
        if (sum >= limit) {
            return NextTuple(0.f, false, false);
        }

        NextTuple nextTuple = pattern->next();
        float value = std::get<0>(nextTuple);
        bool hasValue = std::get<1>(nextTuple);
        if (!hasValue || sum + value >= limit || limit - sum < tolerance) {
            value = limit - sum;
        }

        sum += value;

        return NextTuple(value, true, false);
    }

    virtual void reset() {
        pattern.reset();
        sum = 0;
    }

    static Pattern create(Pattern pattern, float limit, float tolerance) {
        return Pattern(new PConstrainT(pattern, limit, tolerance));
    }

private:
    PConstrainT(Pattern pattern, float limit, float tolerance) :
        pattern(pattern), limit(limit), tolerance(tolerance), sum(0) {
    }

    Pattern pattern;

    float limit;
    float tolerance;
    float sum;
};

Pattern PConstrain(Pattern pattern, float limit, float tolerance) {
    return PConstrainT::create(pattern, limit, tolerance);
}

}

#endif
