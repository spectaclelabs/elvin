#ifndef ELVIN_P_SUBTRACT_H
#define ELVIN_P_SUBTRACT_H

#include <utility>
#include <tuple>

#include "pattern.h"
#include "pattern_t.h"

namespace elvin {

class PSubtractT : public PatternT {
public:
    virtual NextTuple next() {
        NextTuple leftTuple = left->next();
        NextTuple rightTuple = right->next();

        Sample hasLeft = std::get<1>(leftTuple);
        Sample hasRight = std::get<1>(rightTuple);
        if (!hasLeft || !hasRight) {
            return NextTuple(0.0f, false, false);
        }

        Sample leftValue = std::get<0>(leftTuple);
        Sample rightValue = std::get<0>(rightTuple);
        return NextTuple(leftValue - rightValue, true, false);
    }

    virtual void reset() {
        left->reset();
        right->reset();
    }

    static Pattern create(Pattern left, Pattern right) {
        return Pattern(new PSubtractT(std::move(left), std::move(right)));
    }

private:
    PSubtractT(Pattern left, Pattern right) : left(std::move(left)),
                                         right(std::move(right)) {}
    Pattern left;
    Pattern right;
};

constexpr auto &PSubtract = PSubtractT::create;

Pattern operator-(Pattern left, Pattern right) {
    return PSubtract(std::move(left), std::move(right));
}

}

#endif
