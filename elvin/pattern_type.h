#ifndef ELVIN_PATTERN_TYPE
#define ELVIN_PATTERN_TYPE

#include <type_traits>

#include "pattern.h"
#include "patterns/p_literal.h"

namespace elvin {

template <typename Type>
using PatternType =
    typename std::conditional<
                std::is_base_of<
                    Pattern,
                    typename std::remove_reference<Type>::type
                >::value,
                typename std::remove_reference<Type>::type,
                PLiteral
            >::type;

} //namespace elvin

#endif
