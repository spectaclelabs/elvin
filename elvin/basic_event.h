#ifndef ELVIN_BASIC_EVENT_H
#define ELVIN_BASIC_EVENT_H

#include <memory>

#include "time_data.h"
#include "event.h"

namespace elvin {

class BasicEvent : public Event {
public:
    BasicEvent(uint32_t time, void(*callback)()) :
        Event(time), callback(callback) {}

    virtual bool process(const TimeData &time) {
        callback();
        return false;
    }

    void(*callback)();
};

typedef std::unique_ptr<BasicEvent> BasicEventPtr;

}


#endif
