#ifndef ELVIN_P_RANDOM_H
#define ELVIN_P_RANDOM_H

#include <cstdlib>
#include <limits>

#include "pattern.h"
#include "pattern_t.h"

namespace elvin {

class PRandomT : public PatternT {
public:
    virtual NextTuple next() {
        if (position >= repeats) {
            return NextTuple(0.0f, false, false);
        }

        Sample value = low + (high - low) * ((Sample) rand()) / RAND_MAX;
        position++;

        return NextTuple(value, true, false);
    }

    virtual void reset() {
        position = 0;
    }

    static Pattern create(Sample low, Sample high, uint32_t repeats) {
        return Pattern(new PRandomT(low, high, repeats));
    }

private:
    PRandomT(Sample low, Sample high, uint32_t repeats) :
        low(low), high(high), repeats(repeats), position(0) {
    }

    Sample low;
    Sample high;
    uint32_t repeats;
    uint32_t position;
};

Pattern PRandom(Sample low=0.0f, Sample high=1.0f,
                uint32_t repeats=std::numeric_limits<uint32_t>::max()) {
    return PRandomT::create(low, high, repeats);
}

}

#endif
