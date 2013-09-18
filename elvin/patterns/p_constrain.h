#ifndef ELVIN_P_CONSTRAIN_H
#define ELVIN_P_CONSTRAIN_H

#include "elvin/pattern.h"
#include "elvin/pattern_value.h"
#include "elvin/pattern_type.h"

namespace elvin {

template <typename ConstrainedPattern>
class PConstrainT : public Pattern {
public:
    PConstrainT(ConstrainedPattern pattern, float limit, float tolerance) :
            pattern(std::move(pattern)), limit(limit), tolerance(tolerance),
            sum(0) {
    }
 
    PatternValue next() {
        if (sum >= limit) {
            return PatternValue();
        }

        PatternValue value = pattern.next();
        if (!value.exists || sum + value.value >= limit || limit - sum < tolerance) {
            value.value = limit - sum;
        }

        sum += value.value;

        value.exists = true;
        value.isLiteral = false;
        return value;
    }

    void reset() {
        pattern.reset();
        sum = 0;
    }

    PConstrainT<ConstrainedPattern>* clone() const {
        return new PConstrainT<ConstrainedPattern>(*this);
    }

private:
    ConstrainedPattern pattern;

    float limit;
    float tolerance;
    float sum;
};

template <typename ConstrainedPatternF>
using PConstrainFT = PConstrainT<PatternType<ConstrainedPatternF>>;

template <typename ConstrainedPatternF>
PConstrainFT<ConstrainedPatternF> PConstrain(ConstrainedPatternF pattern,
                                             float limit, float tolerance=0.f) {
    return PConstrainFT<ConstrainedPatternF>(pattern, limit, tolerance);
}

}

#endif
