#ifndef ELVIN_P_SEQUENCE_H
#define ELVIN_P_SEQUENCE_H

#include <utility>
#include <tuple>
#include <vector>

#include "pattern.h"
#include "pattern_t.h"

namespace elvin {

class PSequenceT : public PatternT {
public:
    virtual NextTuple next() {
        if (repeats > 0 && position >= repeats * sequence.size()) {
            return NextTuple(0.0f, false, false);
        }

        uint32_t index = (position + offset) % sequence.size();

        NextTuple tuple = sequence[index]->next();

        Sample value = std::get<0>(tuple);
        bool hasValue = std::get<1>(tuple);
        bool isLiteral = std::get<2>(tuple);

        if (!hasValue) {
            position++;
            sequence[index]->reset();
            return next();
        }

        if (isLiteral) {
            position++;
        }

        return NextTuple(value, true, false);
    }

    virtual void reset() {
        position = 0;
        for (uint32_t i=0; i<sequence.size(); i++) {
            sequence[i]->reset();
        }
    }

    static Pattern create(std::initializer_list<Pattern> sequence,
                          uint32_t repeats, uint32_t offset) {
        return Pattern(new PSequenceT(std::move(sequence), repeats, offset));
    }

private:
    PSequenceT(std::initializer_list<Pattern> sequence, uint32_t repeats,
              uint32_t offset) :
        sequence(sequence), repeats(repeats), offset(offset),
        position(0) {
    }

    std::vector<Pattern> sequence;
    uint32_t repeats;
    uint32_t offset;
    uint32_t position;
};

Pattern PSequence(std::initializer_list<Pattern> sequence, uint32_t repeats=1,
                  uint32_t offset=0) {
    return PSequenceT::create(std::move(sequence), repeats, offset);
}

}

#endif
