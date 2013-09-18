#ifndef ELVIN_PATTERN_VALUE_H
#define ELVIN_PATTERN_VALUE_H

namespace elvin {

struct PatternValue {
    PatternValue() : value(0), exists(false), isLiteral(false) {}
    float value;
    bool exists;
    bool isLiteral;
};

} // namespace elvin

#endif
