#ifndef ELVIN_P_GEOMETRIC_H
#define ELVIN_P_GEOMETRIC_H

#include <limits>

#include "thelonious/types.h"

#include "pattern.h"
#include "pattern_t.h"

namespace elvin {

class PGeometricT : public PatternT {
public:
    virtual NextTuple next() {
        NextTuple tuple = steps->next();
        bool haveValue = std::get<1>(tuple);

        if (!haveValue || repeats > 0 && position >= repeats) {
            return NextTuple(0.0f, false, false);
        }

        float step = std::get<0>(tuple);
        value *= step;
        position++;

        return NextTuple(value, true, false);
    }

    virtual void reset() {
        position = 0;
    }

    static Pattern create(Sample initialValue, Pattern steps,
                          uint32_t repeats) {
        return Pattern(new PGeometricT(initialValue, steps, repeats));
    }

private:
    PGeometricT(Sample initialValue, Pattern steps, uint32_t repeats) :
        value(initialValue), steps(steps), repeats(repeats), position(0) {
    }

    Sample value;
    Pattern steps;
    uint32_t repeats;
    uint32_t position;
};

Pattern PGeometric(Sample initialValue, Pattern steps,
                    uint32_t repeats=1) {
    return PGeometricT::create(initialValue, steps, repeats);
}

}

#endif
