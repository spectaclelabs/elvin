#ifndef ELVIN_P_POINTER
#define ELVIN_P_POINTER

#include <memory>

#include "elvin/pattern.h"
#include "elvin/pattern_type.h"

namespace elvin {

class PPointer : Pattern {
public:
    template <typename Type>
    PPointer(Type pattern) : pattern(new PatternType<Type>(pattern)) {
    }

    PPointer(const PPointer &other) : pattern(other.clone()) {
    }

    PPointer(PPointer && other) : pattern(std::move(other.pattern)) {
    }

    PPointer operator=(const PPointer &other) {
        pattern.reset(other.clone());
        return *this;
    }

    PPointer operator=(PPointer &&other) {
        pattern = std::move(other.pattern);
        return *this;
    }

    ~PPointer() {
    }

    PatternValue next() {
        return pattern->next();
    }

    void reset() {
        pattern->reset();
    }

    Pattern *clone() const {
        return pattern->clone();
    }

private:
    std::unique_ptr<Pattern> pattern;
};

}

#endif
