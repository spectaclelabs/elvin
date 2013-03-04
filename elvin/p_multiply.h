#ifndef ELVIN_P_MULTIPLY_H
#define ELVIN_P_MULTIPLY_H

#include <utility>
#include <tuple>

#include "pattern.h"
#include "pattern_t.h"

namespace elvin {

class PMultiplyT : public PatternT {
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
        return NextTuple(leftValue * rightValue, true, false);
    }

    virtual void reset() {
        left->reset();
        right->reset();
    }

    static Pattern create(Pattern left, Pattern right) {
        return Pattern(new PMultiplyT(std::move(left), std::move(right)));
    }

private:
    PMultiplyT(Pattern left, Pattern right) : left(std::move(left)),
                                         right(std::move(right)) {}
    Pattern left;
    Pattern right;
};

constexpr auto &PMultiply = PMultiplyT::create;

Pattern operator*(Pattern left, Pattern right) {
    return PMultiply(std::move(left), std::move(right));
}

}

#endif
