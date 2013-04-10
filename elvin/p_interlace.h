#ifndef ELVIN_P_INTERLACE_H
#define ELVIN_P_INTERLACE_H

#include <utility>
#include <tuple>
#include <vector>

#include "pattern.h"
#include "pattern_t.h"

namespace elvin {

class PInterlaceT : public PatternT {
public:
    virtual NextTuple next() {
        NextTuple nextTuple = patterns[position]->next();

        bool hasValue = std::get<1>(nextTuple);
        if (!hasValue) {
            return NextTuple(0, false, false);
        }

        Sample value = std::get<0>(nextTuple);

        position++;
        if (position >= patterns.size()) {
            position = 0;
        }

        return NextTuple(value, true, false);
    }

    virtual void reset() {
        position = 0;
        for (uint32_t i=0; i<patterns.size(); i++) {
            patterns[i]->reset();
        }
    }

    static Pattern create(std::vector<Pattern> patterns) {
        return Pattern(new PInterlaceT(std::move(patterns)));
    }

private:
    PInterlaceT(std::vector<Pattern> patterns) :
        patterns(patterns), position(0) {
    }

    std::vector<Pattern> patterns;
    uint32_t position;
};

Pattern PInterlace(std::vector<Pattern> patterns) {
    return PInterlaceT::create(std::move(patterns));
}

}

#endif
