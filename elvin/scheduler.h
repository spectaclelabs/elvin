#ifndef ELVIN_SCHEDULER_H
#define ELVIN_SCHEDULER_H

#include <algorithm>
#include <array>

#include "event.h"
#include "basic_event.h"
#include "pattern_event.h"
#include "pattern_type.h"
#include "time_data.h"

namespace elvin {

template <size_t maxEvents=16>
class Scheduler {
public:

    Scheduler(float bpm=120.0f) :
        time(bpm) {
    }

    uint32_t addRelative(float beats, void(*callback)()) {
        if (full()) {
            return 0;
        }

        uint32_t eventTime = time.time + beats * time.beatLength;
        BasicEventPtr event(new BasicEvent(eventTime, callback));

        uint32_t id = event->id;

        events[numberOfEvents] = std::move(event);
        push();

        return id;
    }

    uint32_t addAbsolute(float beat, void(*callback)()) {
        if (full()) {
            return 0;
        }

        if (beat < time.beat && time.time > time.lastBeatTime) {
            return 0;
        }

        uint32_t eventTime = time.lastBeatTime + (beat - time.beat) *
                           time.beatLength;
        BasicEventPtr event(new BasicEvent(eventTime, callback));

        uint32_t id = event->id;

        events[numberOfEvents] = std::move(event);
        push();

        return id;
    }

    template <typename CollectionType, typename DurationPatternF,
              typename... CallbackArgs>
    uint32_t play(CollectionType patterns,
                  DurationPatternF durationPattern,
                  void(*callback)(CallbackArgs...)) {
    
        if (full()) {
            return 0;
        }

        typedef PatternType<DurationPatternF> DurationPattern;

        PatternEventPtr<CollectionType, DurationPattern, CallbackArgs...> event(
            new PatternEvent<CollectionType, DurationPattern, CallbackArgs...>(
                time.time, std::move(patterns), std::move(durationPattern),
                callback
            )
        );

        uint32_t id = event->id;

        events[numberOfEvents] = std::move(event);
        push();
        
        return id;
    }

    void remove(uint32_t eventId) {
        EventPtr& endEvent = *(events.begin() + numberOfEvents - 1);
        for (auto it=events.begin(); it!=events.begin()+numberOfEvents; it++) {
            EventPtr& event = *it;
            if (event->id == eventId) {
                event.reset();
                std::swap(event, endEvent);
                numberOfEvents--;
                std::make_heap(events.begin(),
                               events.begin() + numberOfEvents,
                               compareEventTime);
                return;
            }
        }
    }


    void tick() {
        uint32_t endTime = time.time + constants::BLOCK_SIZE;

        while (numberOfEvents && events[0]->time <= endTime) {
            time.time = events[0]->time;
            updateClock();
            pop();
            EventPtr &event = events[numberOfEvents];
            // While processing we need to pretend that numberOfEvents is
            // one higher than it actually is by incrementing, then
            // decrementing when we are done.  This is becuase if we add
            // further events during processing they will overwrite the current
            // event, which may need re-adding.
            numberOfEvents++;
            bool needsPush = event->process(time);
            numberOfEvents--;
            if (needsPush) {
                push();
            }
            else {
                event.reset();
            }
        }
        time.time = endTime;
        updateClock();
    }

    // TODO: Getters and setters

private:
    void push() {
        numberOfEvents++;
        std::push_heap(events.begin(), events.begin() + numberOfEvents,
                       compareEventTime);
    }

    void pop() {
        std::pop_heap(events.begin(), events.begin() + numberOfEvents,
                      compareEventTime);
        numberOfEvents--;
    }

    bool full() {
        return numberOfEvents >= maxEvents;
    }
                
    void updateClock() {
        while (time.time > time.lastBeatTime + time.beatLength) {
            time.beat++;
            time.beatInBar++;;
            if (time.beatInBar == time.beatsPerBar) {
                time.bar++;
                time.beatInBar = 0u;
            }
            time.lastBeatTime += time.beatLength;
        }
    }

    TimeData time;
    std::array<EventPtr, maxEvents> events;
    size_t numberOfEvents;
};

}

#endif
