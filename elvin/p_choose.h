#ifndef ELVIN_P_CHOOSE_H
#define ELVIN_P_CHOOSE_H

#include <utility>
#include <tuple>
#include <cstdlib>

#include "pattern.h"
#include "pattern_t.h"

namespace elvin {

class PChooseT : public PatternT {
public:
    virtual NextTuple next() {
        if (repeats > 0 && position >= repeats) {
            return NextTuple(0.0f, false, false);
        }

        NextTuple tuple = patterns[index]->next();

        Sample value = std::get<0>(tuple);
        bool hasValue = std::get<1>(tuple);
        bool isLiteral = std::get<2>(tuple);

        if (!hasValue || isLiteral) {
            index = std::rand() % patterns.size();
            position++;
        }

        if (!hasValue) {
            patterns[index]->reset();
            return next();
        }

        return NextTuple(value, true, false);
    }

    virtual void reset() {
        position = 0;
        index = std::rand() % patterns.size();
        for (uint32_t i=0; i<patterns.size(); i++) {
            patterns[i]->reset();
        }
    }

    static Pattern create(std::vector<Pattern> patterns, uint32_t repeats=0) {
        return Pattern(new PChooseT(std::move(patterns), repeats));
    }

private:
    PChooseT(std::vector<Pattern> patterns, uint32_t repeats=0) :
            patterns(std::move(patterns)), repeats(repeats), position(0),
            index(std::rand() % this->patterns.size()) {
    }

    std::vector<Pattern> patterns;
    uint32_t repeats;
    uint32_t position;
    uint32_t index;
};

Pattern PChoose(std::vector<Pattern> patterns, uint32_t repeats=0) {
    return PChooseT::create(std::move(patterns), repeats);
}

}

#endif
