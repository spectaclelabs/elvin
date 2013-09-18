#ifndef ELVIN_COLLECTIONS_P_VECTOR_H
#define ELVIN_COLLECTIONS_P_VECTOR_H

#include <vector>
#include "elvin/patterns/p_pointer.h"

namespace elvin {
namespace collections {

typedef std::vector<PPointer> PVectorT;

template <typename... PatternTypesF>
PVectorT PVector(PatternTypesF... patterns) {
    return PVectorT{patterns...};
}

} // namespace collections
} // namespace elvin

#endif

