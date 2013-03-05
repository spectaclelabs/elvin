#ifndef ELVIN_BASIC_EVENT_H
#define ELVIN_BASIC_EVENT_H

#include <functional>

#include "thelonious/types.h"

#include "time_data.h"

using namespace thelonious;

namespace elvin {

class BasicEvent : public Event {
public:
    BasicEvent(Sample time, std::function<void()> callback) :
        Event(time), callback(callback) {}

    virtual bool process(const TimeData &time) {
        callback();
        return false;
    }

    std::function<void()> callback;
};

}


#endif
