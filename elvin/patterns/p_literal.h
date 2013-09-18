#ifndef ELVIN_P_LITERAL_H
#define ELVIN_P_LITERAL_H

#include "elvin/pattern.h"
#include "elvin/pattern_value.h"

namespace elvin {

class PLiteral : public Pattern {
public:
    PLiteral(float value) : value(value) {}

    PatternValue next() {
        PatternValue next;
        next.value = value;
        next.exists = true;
        next.isLiteral = true;
        return next;
    }

    void reset() {}

    PLiteral* clone() const {
        return new PLiteral(*this);
    }

private:
    float value;
};

}

#endif
