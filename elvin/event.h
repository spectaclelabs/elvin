#ifndef EVENT_H
#define EVENT_H

#include <functional>

#include "thelonious/types.h"

#include "scheduler.h"
#include "pattern.h"
#include "time_data.h"
#include "indices.h"

using namespace thelonious;

namespace elvin {

// Store static variables in a seperate template class.  C++ sigh...
template <class Dummy>
struct EventStatics {
    static uint32_t nextId;
};

template <class Dummy>
uint32_t EventStatics<Dummy>::nextId = 1;


class Event : public EventStatics<void> {
public:
    Event() : id(nextId++) {}
    Sample time;
    
    virtual bool process(const TimeData &time) = 0;
    const uint32_t id;
};

class BasicEvent : public Event {
public:
    virtual bool process(const TimeData &time) {
        callback();
        return false;
    }

    std::function<void()> callback;
};

template <size_t numberOfPatterns, typename CallbackType>
class PatternEvent : public Event {
public:
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

    std::array<Pattern, numberOfPatterns> patterns;
    Pattern durationPattern;
    CallbackType callback;

private:
    // Runs the callback samples collected from the patterns
    bool runCallback() {
        // Collect the next value from each of the patterns
        std::array<Sample, numberOfPatterns> arguments;
        for (int i=0; i<numberOfPatterns; i++) {
            NextTuple tuple = patterns[i]->next();

            bool hasValue = std::get<1>(tuple);
            if (!hasValue) {
                return false;
            }

            arguments[i] = std::get<0>(tuple);
        }

        // Run the callback using an index pack
        call(arguments, BuildIndices<numberOfPatterns>{});
        return true;
    }

    // Template magic to expand the array into arguments for the callback.
    // Expansion is done using an index pack.  I really don't understand how
    // this works :D
    template <size_t... I>
    void call(std::array<Sample, numberOfPatterns> &arguments, indices<I...>) {
        callback(arguments[I]...);
    }
};

bool compareEventTime(std::unique_ptr<Event> &a, std::unique_ptr<Event> &b) {
    return a->time < b->time;
}

typedef std::unique_ptr<Event> EventPtr;

}


#endif
