#ifndef ELVIN_P_STUTTER_H
#define ELVIN_P_STUTTER_H

#include <utility>
#include <tuple>

#include "pattern.h"
#include "pattern_t.h"

namespace elvin {

class PStutterT : public PatternT {
public:
    virtual NextTuple next() {
        if (position == limit) {
            NextTuple valueTuple = pattern->next();
            NextTuple repeatTuple = repeats->next();

            bool hasValue = std::get<1>(valueTuple);
            bool hasRepeat = std::get<1>(repeatTuple);
            if (!hasValue || !hasRepeat) {
                return NextTuple(0, false, false);
            }

            value = std::get<0>(valueTuple);
            limit = std::get<0>(repeatTuple);
            position = 0;
        }

        position++;
        return NextTuple(value, true, false);
    }

    virtual void reset() {
        position = 0;
        limit = 0;
        pattern.reset();
        repeats.reset();
    }

    static Pattern create(Pattern pattern, Pattern repeats) {
        return Pattern(new PStutterT(pattern, repeats));
    }

private:
    PStutterT(Pattern pattern, Pattern repeats) :
        pattern(pattern), repeats(repeats), position(0), limit(0) {
    }

    Pattern pattern;
    Pattern repeats;

    Sample value;
    uint32_t position;
    uint32_t limit;
};

Pattern PStutter(Pattern pattern, Pattern repeats) {
    return PStutterT::create(pattern, repeats);
}

}

#endif
