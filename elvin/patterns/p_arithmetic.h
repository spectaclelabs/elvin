#ifndef ELVIN_P_ARITHMETIC_H
#define ELVIN_P_ARITHMETIC_H

#include "elvin/pattern.h"
#include "elvin/pattern_value.h"
#include "elvin/pattern_type.h"

namespace elvin {

template <typename StepsPattern>
class PArithmeticT : public Pattern {
public:
    PArithmeticT(float initialValue, StepsPattern steps, uint32_t repeats) :
        initialValue(initialValue), value(initialValue), steps(steps),
        repeats(repeats), position(0), done(false) {
    }

    PatternValue next() {
        if (done || (repeats > 0 && position >= repeats)) {
            return PatternValue();
        }

        PatternValue next;
        next.value = value;
        next.exists = true;

        PatternValue step = steps.next();
        if (step.exists) {
            value += step.value;
        }
        else {
            done = true;
        }

        position++;

        return next;
    }

    void reset() {
        position = 0;
        value = initialValue;
        done = false;
    }

    PArithmeticT<StepsPattern>* clone() const {
        return new PArithmeticT<StepsPattern>(*this);
    }


private:
    float initialValue;
    float value;
    StepsPattern steps;
    uint32_t repeats;
    uint32_t position;

    bool done;
};

template <typename StepsPatternF>
using PArithmeticFT = PArithmeticT<PatternType<StepsPatternF>>;

template <typename StepsPatternF>
PArithmeticFT<StepsPatternF> PArithmetic(float initialValue,
                                         StepsPatternF steps,
                                         uint32_t repeats=1) {
    return PArithmeticFT<StepsPatternF>(initialValue, steps, repeats);
}

}

#endif
