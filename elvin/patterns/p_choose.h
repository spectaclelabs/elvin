#ifndef ELVIN_P_CHOOSE_H
#define ELVIN_P_CHOOSE_H

#include <cstdlib>

#include "elvin/pattern.h"
#include "elvin/pattern_value.h"
#include "elvin/collections/p_tuple.h"
#include "elvin/collections/p_vector.h"
#include "elvin/collections/interface.h"

namespace elvin {

using namespace collections;

template <typename CollectionType>
class PChooseT : public Pattern {
public:
    PChooseT(CollectionType patterns, uint32_t repeats=0) :
                patterns(std::move(patterns)), repeats(repeats), position(0),
                index(std::rand() %
                      collections::interface::size(this->patterns)) {
    }

    
    PatternValue next() {
        if (repeats > 0 && position >= repeats) {
            return PatternValue();
        }

        PatternValue value = collections::interface::next(patterns, index);

        if (!value.exists || value.isLiteral) {
            index = std::rand() % collections::interface::size(patterns);
            position++;
        }

        if (!value.exists) {
            collections::interface::reset(patterns, index);
            return next();
        }

        value.isLiteral = false;
        return value;
    }

    void reset() {
        position = 0;
        index = std::rand() % collections::interface::size(patterns);
        for (uint32_t i=0; i<collections::interface::size(patterns); i++) {
            collections::interface::reset(patterns, i);
        }
    }
    
    PChooseT<CollectionType>* clone() const {
        return new PChooseT<CollectionType>(*this);
    }

private:
    CollectionType patterns;
    uint32_t repeats;
    uint32_t position;
    uint32_t index;
};

template <typename... PatternTypes>
using PChooseTupleT = PChooseT<PTupleT<PatternTypes...>>;

typedef PChooseT<PVectorT> PChooseVectorT;

template <typename... PatternTypes>
PChooseTupleT<PatternTypes...> PChoose(PTupleT<PatternTypes...> patterns,
                                       uint32_t repeats=0) {
    return PChooseTupleT<PatternTypes...>(std::move(patterns), repeats);
}

PChooseVectorT PChoose(PVectorT patterns, uint32_t repeats=0) {
    return PChooseVectorT(std::move(patterns), repeats);
}

} // namespace elvin

#endif
