#ifndef ELVIN_PATTERN_H
#define ELVIN_PATTERN_H

#include <array>
#include <memory>

#include "thelonious/types.h"

#include "pattern_t.h"
#include "p_literal.h"

using namespace thelonious;

namespace elvin {

class Pattern : public std::shared_ptr<PatternT> {
public:
    Pattern() : std::shared_ptr<PatternT>() {}
    Pattern(Sample s) : std::shared_ptr<PatternT>(new PLiteralT(s)) {}


    // Inheriting constructors - implemented in GCC 4.8
    // We explicitly forward PatternT * to the correct constructor instead
    //using std::shared_ptr<PatternT>::std::shared_ptr<PatternT>;
    
    Pattern(PatternT *pattern) : std::shared_ptr<PatternT>(pattern) {}
};

}

#endif
