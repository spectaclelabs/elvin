#ifndef ELVIN_COLLECTIONS_P_TUPLE_H
#define ELVIN_COLLECTIONS_P_TUPLE_H

#include <tuple>

#include "elvin/pattern_type.h"

namespace elvin {
namespace collections {

template <typename... PatternTypes>
using PTupleT = std::tuple<PatternTypes...>;

template <typename... PatternTypesF>
using PTupleFT = PTupleT<PatternType<PatternTypesF>...>;

template <typename... PatternTypesF>
PTupleFT<PatternTypesF...> PTuple(PatternTypesF&&... patterns) {
    return std::make_tuple(std::forward<PatternTypesF>(patterns)...);
}

} // namespace collections
} // namespace elvin

#endif

