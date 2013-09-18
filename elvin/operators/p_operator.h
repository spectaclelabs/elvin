#ifndef ELVIN_P_OPERATOR_H
#define ELVIN_P_OPERATOR_H

#include <type_traits>

#include "elvin/pattern.h"
#include "elvin/pattern_type.h"
#include "elvin/pattern_value.h"

namespace elvin {
namespace operators {

template <typename PatternA, typename PatternB, char Op>
class POperatorT : public Pattern {
public:
    POperatorT(PatternA left, PatternB right) : left(std::move(left)),
                                                right(std::move(right)) {}
    
    virtual PatternValue next() {
        PatternValue leftValue = left.next();
        PatternValue rightValue = right.next();
        
        if (!leftValue.exists || !rightValue.exists) {
            return PatternValue();
        }

        PatternValue value;
        value.value = operate<Op>(leftValue.value, rightValue.value);
        value.exists = true;
        value.isLiteral = false;
        return value;
    }

    virtual void reset() {
        left.reset();
        right.reset();
    }

    POperatorT *clone() const {
        return new POperatorT(*this);
    }

private:
    template <char LOp>
    typename std::enable_if<LOp == '+', float>::type
    operate(float left, float right) {
        return left + right;
    }

    template <char LOp>
    typename std::enable_if<LOp == '-', float>::type
    operate(float left, float right) {
        return left - right;
    }

    template <char LOp>
    typename std::enable_if<LOp == '*', float>::type
    operate(float left, float right) {
        return left * right;
    }

    template <char LOp>
    typename std::enable_if<LOp == '/', float>::type
    operate(float left, float right) {
        return left / right;
    }

    template <char LOp>
    typename std::enable_if<LOp == '%', float>::type
    operate(float left, float right) {
        return left - std::floor(left / right) * right;
    }

    PatternA left;
    PatternB right;
};



// Operator types
template <typename PatternA, typename PatternB>
using PAddT = POperatorT<PatternA, PatternB, '+'>;

template <typename PatternA, typename PatternB>
using PSubtractT = POperatorT<PatternA, PatternB, '-'>;

template <typename PatternA, typename PatternB>
using PMultiplyT = POperatorT<PatternA, PatternB, '*'>;

template <typename PatternA, typename PatternB>
using PDivideT = POperatorT<PatternA, PatternB, '/'>;

template <typename PatternA, typename PatternB>
using PModuloT = POperatorT<PatternA, PatternB, '%'>;

// Operator types which take floats for converting to PLiterals
template <typename PatternA, typename PatternB>
using PAddFT = PAddT<PatternType<PatternA>, PatternType<PatternB>>;

template <typename PatternA, typename PatternB>
using PSubtractFT = PSubtractT<PatternType<PatternA>, PatternType<PatternB>>;

template <typename PatternA, typename PatternB>
using PMultiplyFT = PMultiplyT<PatternType<PatternA>, PatternType<PatternB>>;

template <typename PatternA, typename PatternB>
using PDivideFT = PDivideT<PatternType<PatternA>, PatternType<PatternB>>;

template <typename PatternA, typename PatternB>
using PModuloFT = PModuloT<PatternType<PatternA>, PatternType<PatternB>>;

// Checks whether one of the two template arguments is a pattern
template <typename PatternA, typename PatternB>
struct HasPattern :
    public std::integral_constant<bool,
                                  std::is_base_of<Pattern, PatternA>::value ||
                                  std::is_base_of<Pattern, PatternB>::value> {
};


// Operator overloads
template <typename PatternA, typename PatternB>            
typename std::enable_if<HasPattern<PatternA, PatternB>::value,
                        PAddFT<PatternA, PatternB>>::type
operator+(PatternA left, PatternB right) {
    return PAddFT<PatternA, PatternB>(std::move(left), std::move(right));
}

template <typename PatternA, typename PatternB>
typename std::enable_if<HasPattern<PatternA, PatternB>::value,
                        PSubtractFT<PatternA, PatternB>>::type
operator-(PatternA left, PatternB right) {
    return PSubtractFT<PatternA, PatternB>(std::move(left), std::move(right));
}

template <typename PatternA, typename PatternB>
typename std::enable_if<HasPattern<PatternA, PatternB>::value,
                        PMultiplyFT<PatternA, PatternB>>::type
operator*(PatternA left, PatternB right) {
    return PMultiplyFT<PatternA, PatternB>(std::move(left), std::move(right));
}

template <typename PatternA, typename PatternB>
typename std::enable_if<HasPattern<PatternA, PatternB>::value,
                        PDivideFT<PatternA, PatternB>>::type
operator/(PatternA left, PatternB right) {
    return PDivideFT<PatternA, PatternB>(std::move(left), std::move(right));
}

template <typename PatternA, typename PatternB>
typename std::enable_if<HasPattern<PatternA, PatternB>::value,
                        PModuloFT<PatternA, PatternB>>::type
operator%(PatternA left, PatternB right) {
    return PModuloFT<PatternA, PatternB>(std::move(left), std::move(right));
}


} // namespace operators
} // namespace elvin

#endif
