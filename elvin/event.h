#ifndef ELVIN_EVENT_H
#define ELVIN_EVENT_H

#include <memory>

#include "thelonious/types.h"

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
    Event(uint32_t time) : time(time), id(nextId++) {}
    virtual bool process(const TimeData &time) = 0;

    uint32_t time;
    const uint32_t id;
};

typedef std::unique_ptr<Event> EventPtr;

bool compareEventTime(EventPtr &a, EventPtr &b) {
    return a->time < b->time;
}

}


#endif
