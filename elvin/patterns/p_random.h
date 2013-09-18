#ifndef ELVIN_P_RANDOM_H
#define ELVIN_P_RANDOM_H

#include "elvin/pattern.h"
#include "elvin/pattern_value.h"

namespace elvin {

class PRandomT : public Pattern {
public:
    PRandomT(float low, float high, uint32_t repeats) :   
        low(low), high(high), repeats(repeats), position(0) {
    }
 
    PatternValue next() {
        if (repeats > 0 && position >= repeats) {
            return PatternValue();
        }

        PatternValue value;
        value.exists = true;

        float random = std::rand();
        random /= RAND_MAX;
        value.value = low + (high - low) * random;
        position++;

        return value;
    }

    void reset() {
        position = 0;
    }

    PRandomT* clone() const {
        return new PRandomT(*this);
    }


private:
    float low;
    float high;
    uint32_t repeats;
    uint32_t position;
};

PRandomT PRandom(float low=0.0f, float high=1.0f, uint32_t repeats=0) {
    return PRandomT(low, high, repeats);
}

}

#endif
