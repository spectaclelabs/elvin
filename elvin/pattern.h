#ifndef PATTERN_H
#define PATTERN_H

#include <memory>

#include "thelonious/types.h"

#include "pattern_t.h"
#include "p_literal.h"

using namespace thelonious;

namespace elvin {

class Pattern : public std::unique_ptr<PatternT> {
public:
    Pattern() : std::unique_ptr<PatternT>() {}
    Pattern(Sample s) : std::unique_ptr<PatternT>(new PLiteralT(s)) {}


    // Inheriting constructors - implemented in GCC 4.8
    // We explicitly forward PatternT * to the correct constructor instead
    //using std::unique_ptr<PatternT>::std::unique_ptr<PatternT>;
    
    Pattern(PatternT *pattern) : std::unique_ptr<PatternT>(pattern) {}
};

}

#endif
