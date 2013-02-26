#ifndef TYPES_H
#define TYPES_H

#include "thelonious/types.h"

#include <array>
#include "pattern.h"

namespace elvin {

template <size_t N>
using PatternArray = std::array<Pattern, N>;

template <size_t N>
using ValueArray = std::array<Sample, N>;

}

#endif
