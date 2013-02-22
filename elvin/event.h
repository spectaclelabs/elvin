#ifndef EVENT_H
#define EVENT_H

#include <functional>

#include "thelonious/types.h"

#include "scheduler.h"
#include "pattern.h"
#include "time_data.h"

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
        // Work out how to run callback here!

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
};

bool compareEventTime(std::unique_ptr<Event> &a, std::unique_ptr<Event> &b) {
    return a->time < b->time;
}

typedef std::unique_ptr<Event> EventPtr;

}


#endif
