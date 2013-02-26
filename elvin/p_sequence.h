#ifndef P_SEQUENCE_H
#define P_SEQUENCE_H

#include "pattern.h"

namespace elvin {

template <size_t N>
class PSequenceT : public PatternT {
public:
    virtual NextTuple next() {
        if (position >= repeats * N) {
            return NextTuple(0.0f, false, false);
        }

        uint32_t index = (position + offset) % N;

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
        for (int i=0; i<N; i++) {
            sequence[i]->reset();
        }
    }

    static Pattern create(PatternArray<N> sequence, uint32_t repeats,
                          uint32_t offset) {
        return Pattern(new PSequenceT(std::move(sequence), repeats, offset));
    }

private:
    PSequenceT(PatternArray<N> sequence, uint32_t repeats,
              uint32_t offset) :
        sequence(std::move(sequence)), repeats(repeats), offset(offset),
        position(0) {
    }

    PatternArray<N> sequence;
    uint32_t repeats;
    uint32_t offset;
    uint32_t position;
};

template <size_t N>
Pattern PSequence(PatternArray<N> sequence, uint32_t repeats=1,
                  uint32_t offset=0) {
    return PSequenceT<N>::create(std::move(sequence), repeats, offset);
}

}

#endif
