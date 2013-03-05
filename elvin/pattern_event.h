#ifndef ELVIN_PATTERN_EVENT_H
#define ELVIN_PATTERN_EVENT_H

#include <vector>
#include <tuple>
#include <functional>

#include "thelonious/types.h"

#include "pattern.h"
#include "time_data.h"
#include "dispatcher.h"

using namespace thelonious;

namespace elvin {

template <typename CallbackType>
class PatternEvent : public Event {
public:
    PatternEvent(Sample time, std::initializer_list<Pattern> patterns,
                 Pattern durationPattern, CallbackType callback) :
        Event(time), patterns(patterns), arguments(patterns.size()),
        durationPattern(std::move(durationPattern)), callback(callback),
        dispatcher(make_dispatcher<std::vector<Sample>>(callback)) {}
        
        
    virtual bool process(const TimeData &time) {
        bool shouldContinue = runCallback();
        if (!shouldContinue) {
            // Pattern hasn't provided a value, so don't process the callback
            // or add any further events
            return false;
        }

        NextTuple tuple = durationPattern->next();
        Sample value = std::get<0>(tuple);
        bool hasValue = std::get<1>(tuple);

        if (hasValue) {
            this->time += value * time.beatLength;
            return true;
        }
        return false;
    }

    std::vector<Pattern> patterns;
    std::vector<Sample> arguments;
    Pattern durationPattern;
    CallbackType callback;
    std::function<void(std::vector<Sample>)> dispatcher;

private:
    // Runs the callback samples collected from the patterns
    bool runCallback() {
        // Collect the next value from each of the patterns
        for (uint32_t i=0; i<patterns.size(); i++) {
            NextTuple tuple = patterns[i]->next();

            bool hasValue = std::get<1>(tuple);
            if (!hasValue) {
                return false;
            }

            arguments[i] = std::get<0>(tuple);
        }

        dispatcher(arguments);
        return true;
    }
};

}


#endif
