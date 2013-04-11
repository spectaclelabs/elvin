#ifndef ELVIN_P_ARITHMETIC_H
#define ELVIN_P_ARITHMETIC_H

#include <limits>

#include "thelonious/types.h"

#include "pattern.h"
#include "pattern_t.h"

namespace elvin {

class PArithmeticT : public PatternT {
public:
    virtual NextTuple next() {
        NextTuple tuple = steps->next();
        bool haveValue = std::get<1>(tuple);

        if (!haveValue || repeats > 0 && position >= repeats) {
            return NextTuple(0.0f, false, false);
        }

        float step = std::get<0>(tuple);
        value += step;
        position++;

        return NextTuple(value, true, false);
    }

    virtual void reset() {
        position = 0;
    }

    static Pattern create(Sample initialValue, Pattern steps,
                          uint32_t repeats) {
        return Pattern(new PArithmeticT(initialValue, steps, repeats));
    }

private:
    PArithmeticT(Sample initialValue, Pattern steps, uint32_t repeats) :
        value(initialValue), steps(steps), repeats(repeats), position(0) {
    }

    Sample value;
    Pattern steps;
    uint32_t repeats;
    uint32_t position;
};

Pattern PArithmetic(Sample initialValue, Pattern steps,
                    uint32_t repeats=1) {
    return PArithmeticT::create(initialValue, steps, repeats);
}

}

#endif
