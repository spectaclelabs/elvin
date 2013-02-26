#ifndef ELVIN_PATTERN_T_H
#define ELVIN_PATTERN_T_H

#include <tuple>
#include "thelonious/types.h"

using namespace thelonious;

namespace elvin {

typedef std::tuple<Sample, bool, bool> NextTuple;

class PatternT {
public:
    virtual NextTuple next() = 0;
    virtual void reset() = 0;
};

}

#endif
