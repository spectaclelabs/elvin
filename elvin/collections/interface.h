#ifndef ELVIN_COLLECTIONS_ACTIONS_H
#define ELVIN_COLLECTIONS_ACTIONS_H

#include "elvin/pattern_value.h"
#include "p_vector.h"
#include "p_tuple.h"



namespace elvin {
namespace collections {
namespace interface {

// Vector interface
inline PatternValue next(PVectorT & vector, uint32_t index) {
    return vector[index].next();
}

inline void reset(PVectorT & vector, uint32_t index) {
    vector[index].reset();
}

inline uint32_t size(PVectorT &vector) {
    return vector.size();
}

// Tuple interface

template <uint32_t I, typename... PatternTypes>
typename std::enable_if<I == sizeof...(PatternTypes), PatternValue>::type
inline doNext(PTupleT<PatternTypes...> & tuple, uint32_t index) {
    return PatternValue();
}

template <uint32_t I, typename... PatternTypes>
typename std::enable_if<I < sizeof...(PatternTypes), PatternValue>::type
inline doNext(PTupleT<PatternTypes...> & tuple, uint32_t index) {
    if (index == I) {
        return std::get<I>(tuple).next();
    }
    else {
        return doNext<I + 1, PatternTypes...>(tuple, index);
    }
}

template <typename... PatternTypes>
inline PatternValue next(PTupleT<PatternTypes...> & tuple, uint32_t index) {
    return doNext<0, PatternTypes...>(tuple, index);
}

template <uint32_t I, typename... PatternTypes>
typename std::enable_if<I == sizeof...(PatternTypes)>::type
inline doReset(PTupleT<PatternTypes...> & tuple, uint32_t index) {
}

template <uint32_t I, typename... PatternTypes>
typename std::enable_if<I < sizeof...(PatternTypes)>::type
inline doReset(PTupleT<PatternTypes...> & tuple, uint32_t index) {
    if (index == I) {
        std::get<I>(tuple).reset();
    }
    else {
        doReset<I + 1, PatternTypes...>(tuple, index);
    }
}

template <typename... PatternTypes>
inline void reset(PTupleT<PatternTypes...> & tuple, uint32_t index) {
    doReset<0, PatternTypes...>(tuple, index);
}

template <typename... PatternTypes>
inline uint32_t size(PTupleT<PatternTypes...> & tuple) {
    return sizeof...(PatternTypes);
}

}
} // namespace collections
} // namespace elvin

#endif

