#ifndef ELVIN_TYPES_H
#define ELVIN_TYPES_H

#include "thelonious/types.h"

#include <array>
#include <memory>

#include "pattern.h"
#include "event.h"

namespace elvin {

template <size_t N>
using PatternArray = std::array<Pattern, N>;

template <size_t N>
using ValueArray = std::array<Sample, N>;

template <size_t N>
using EventArray = std::array<std::unique_ptr<Event>, N>;

}

#endif
