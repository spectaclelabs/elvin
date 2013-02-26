#ifndef ELVIN_P_LITERAL_H
#define ELVIN_P_LITERAL_H

#include <cstdlib>
#include <limits>

#include "pattern.h"
#include "pattern_t.h"

namespace elvin {

class PLiteralT : public PatternT {
public:
    PLiteralT(Sample value) : value(value) {}

    virtual NextTuple next() {
        return std::make_tuple(value, true, true);
    }

    virtual void reset() {}

private:
    Sample value;
};

}

#endif
