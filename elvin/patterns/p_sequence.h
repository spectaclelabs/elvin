#ifndef ELVIN_P_SEQUENCE_H
#define ELVIN_P_SEQUENCE_H

#include "elvin/pattern.h"
#include "elvin/pattern_value.h"
#include "elvin/collections/p_tuple.h"
#include "elvin/collections/p_vector.h"
#include "elvin/collections/interface.h"

namespace elvin {

using namespace collections;

template <typename CollectionType>
class PSequenceT : public Pattern {
public:

    PSequenceT(CollectionType sequence, uint32_t repeats,
               uint32_t offset) :
            sequence(std::move(sequence)), repeats(repeats), offset(offset),
            position(0) {
    }

    PatternValue next() {
        if (repeats > 0 &&
            position >=repeats * collections::interface::size(sequence)) {
            return PatternValue();
        }

        uint32_t index = (position + offset) %
                         collections::interface::size(sequence);

        PatternValue value = collections::interface::next(sequence, index);

        if (!value.exists) {
            position++;
            collections::interface::reset(sequence, index);
            return next();
        }

        if (value.isLiteral) {
            position++;
        }

        value.exists = true;
        value.isLiteral = false;
        return value;
    }

    void reset() {
        position = 0;
        for (uint32_t i=0; i<collections::interface::size(sequence); i++) {
            collections::interface::reset(sequence, i);
        }
    }

    PSequenceT<CollectionType> *clone() const {
        return new PSequenceT<CollectionType>(*this);
    }

private:
    CollectionType sequence;

    uint32_t repeats;
    uint32_t offset;
    uint32_t position;
};

template <typename... PatternTypes>
using PSequenceTupleT = PSequenceT<PTupleT<PatternTypes...>>;

typedef PSequenceT<PVectorT> PSequenceVectorT;

template <typename... PatternTypes>
PSequenceTupleT<PatternTypes...> PSequence(PTupleT<PatternTypes...> tuple,
                                           uint32_t repeats=1,
                                           uint32_t offset=0) {
    return PSequenceTupleT<PatternTypes...>(std::move(tuple), repeats, offset);
}

PSequenceVectorT PSequence(PVectorT vector, uint32_t repeats=1,
                           uint32_t offset=0) {
    return PSequenceVectorT(std::move(vector), repeats, offset);
}


}

#endif
