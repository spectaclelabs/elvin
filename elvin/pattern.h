#ifndef ELVIN_PATTERN_H
#define ELVIN_PATTERN_H

#include "pattern_value.h"

namespace elvin {

class Pattern {
public:
    virtual PatternValue next() = 0;
    virtual void reset() = 0;
    virtual Pattern *clone() const = 0;
};

} // namespace elvin

#endif
