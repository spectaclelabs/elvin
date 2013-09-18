#ifndef ELVIN_P_INTERLACE_H
#define ELVIN_P_INTERLACE_H

#include "elvin/pattern.h"
#include "elvin/pattern_value.h"
#include "elvin/collections/p_tuple.h"
#include "elvin/collections/p_vector.h"
#include "elvin/collections/interface.h"

namespace elvin {

using namespace collections;

template <typename CollectionType>
class PInterlaceT : public Pattern {
public:
    PInterlaceT(CollectionType patterns) :
            patterns(std::move(patterns)), position(0) {
    }

    PatternValue next() {
        PatternValue value;
        uint32_t count = 0;
        do {
            value = collections::interface::next(patterns, position);
            count++;
            position++;
            position %= collections::interface::size(patterns);
        } while (!value.exists &&
                 count < collections::interface::size(patterns));

        if (!value.exists) {
            // No values left in any of the patterns
            return PatternValue();
        }

        value.isLiteral = false;
        return value;
    }

    void reset() {
        position = 0;
        for (uint32_t i=0; i<collections::interface::size(patterns); i++) {
            collections::interface::reset(patterns, i);
        }
    }

    PInterlaceT<CollectionType>* clone() const {
        return new PInterlaceT<CollectionType>(*this);
    }

private:
    CollectionType patterns;
    uint32_t position;
};

template <typename... PatternTypes>
using PInterlaceTupleT = PInterlaceT<PTupleT<PatternTypes...>>;

typedef PInterlaceT<PVectorT> PInterlaceVectorT;

template <typename... PatternTypes>
PInterlaceTupleT<PatternTypes...> PInterlace(PTupleT<PatternTypes...> tuple) {
    return PInterlaceTupleT<PatternTypes...>(std::move(tuple));
}

PInterlaceVectorT PInterlace(PVectorT vector) {
    return PInterlaceVectorT(std::move(vector));
}

}

#endif
