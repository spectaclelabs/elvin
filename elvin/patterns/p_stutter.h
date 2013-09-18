#ifndef ELVIN_P_STUTTER_H
#define ELVIN_P_STUTTER_H

#include "elvin/pattern.h"
#include "elvin/pattern_value.h"
#include "elvin/pattern_type.h"

namespace elvin {

template <typename StutteredPattern, typename RepeatsPattern>
class PStutterT : public Pattern {
public:
    PStutterT(StutteredPattern pattern, RepeatsPattern repeats) :
            pattern(std::move(pattern)), repeats(std::move(repeats)),
            position(0), limit(0) {
    }

    PatternValue next() {
        PatternValue patternValue;

        if (position == limit) {
            patternValue = pattern.next();
            PatternValue repeat = repeats.next();

            if (!patternValue.exists || !repeat.exists) {
                return PatternValue();
            }

            value = patternValue.value;
            limit = repeat.value;
            position = 0;
        }

        position++;

        patternValue.value = value;
        patternValue.exists = true;
        return patternValue;
    }

    void reset() {
        position = 0;
        limit = 0;
        pattern.reset();
        repeats.reset();
    }

    PStutterT<StutteredPattern, RepeatsPattern>* clone() const {
        return new PStutterT<StutteredPattern, RepeatsPattern>(*this);
    }

private:
    StutteredPattern pattern;
    RepeatsPattern repeats;

    float value;
    uint32_t position;
    uint32_t limit;
};

template <typename StutteredPatternF, typename RepeatsPatternF>
using PStutterFT = PStutterT<PatternType<StutteredPatternF>,
                             PatternType<RepeatsPatternF>>;

template <typename StutteredPatternF, typename RepeatsPatternF>
PStutterFT<StutteredPatternF, RepeatsPatternF>
PStutter(StutteredPatternF pattern, RepeatsPatternF repeats) {
    return PStutterFT<StutteredPatternF, RepeatsPatternF>(std::move(pattern),
                                                          std::move(repeats));
}

}

#endif
