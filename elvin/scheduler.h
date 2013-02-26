#ifndef ELVIN_SCHEDULER_H
#define ELVIN_SCHEDULER_H

#include <array>
#include <memory>
#include <algorithm>

#include "thelonious/rates.h"

#include "event.h"
#include "time_data.h"

namespace elvin {

template <size_t maxEvents=16>
class Scheduler {
public:
    Scheduler(Sample bpm=120.0f) :
        time(bpm) {
    }

    uint32_t addRelative(Sample beats, std::function<void()>callback) {
        if (full()) {
            return 0;
        }

        std::unique_ptr<BasicEvent> event(new BasicEvent());
        event->callback = callback;
        event->time = time.time + beats * time.beatLength;

        uint32_t id = event->id;

        events[numberOfEvents] = std::move(event);
        push();
        numberOfEvents++;

        return id;
    }


    uint32_t addAbsolute(Sample beat, std::function<void()>callback) {
        if (full()) {
            return 0;
        }

        if (beat < time.beat && time.time > time.lastBeatTime) {
            return 0;
        }

        std::unique_ptr<BasicEvent> event(new BasicEvent());
        event->callback = callback;
        event->time = time.lastBeatTime + (beat - time.beat) * time.beatLength;

        uint32_t id = event->id;

        events[numberOfEvents] = std::move(event);
        push();
        numberOfEvents++;

        return id;
    }

    template <size_t numberOfPatterns, typename CallbackType>
    uint32_t play(PatternArray<numberOfPatterns> patterns,
                  Pattern durationPattern,
                  CallbackType callback) {
        if (full()) {
            return 0;
        }

        

        std::unique_ptr<PatternEvent<numberOfPatterns, CallbackType>>
            event(new PatternEvent<numberOfPatterns, CallbackType>());

        event->patterns = std::move(patterns);
        event->durationPattern = std::move(durationPattern);
        event->callback = callback;
        
        // TODO: Quantizing start time
        event->time = time.time;

        uint32_t id = id;

        events[numberOfEvents] = std::move(event);
        push();
        numberOfEvents++;
        
        return id;
    }

    void remove(uint32_t eventId) {
        EventPtr& endEvent = *(events.begin() + numberOfEvents - 1);
        for (auto it=events.begin(); it!=events.begin()+numberOfEvents; it++) {
            EventPtr& event = *it;
            if (event->id == eventId) {
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
        uint32_t endTime = time.time + BLOCK_SIZE;

        while (numberOfEvents && events[0]->time <= endTime) {
            time.time = events[0]->time;
            updateClock();
            pop();
            std::unique_ptr<Event> &event = *(events.begin() + numberOfEvents - 1);
            bool needsPush = event->process(time);
            if (needsPush) {
                push();
            }
            else {
                numberOfEvents--;
            }
        }
        time.time = endTime;
        updateClock();
    }


    // TODO: Getters and setters

private:
    void push() {
        std::push_heap(events.begin(), events.begin() + numberOfEvents,
                       compareEventTime);
    }

    void pop() {
        std::pop_heap(events.begin(), events.begin() + numberOfEvents,
                      compareEventTime);
    }

    bool full() {
        return numberOfEvents >= maxEvents;
    }
                

    void updateClock() {
        while (time.time > time.lastBeatTime + time.beatLength) {
            time.beat++;
            time.beatInBar++;
            if (time.beatInBar == time.beatsPerBar) {
                time.bar++;
                time.beatInBar = 0;
            }
            time.lastBeatTime += time.beatLength;
        }
    }

    void addEvent(EventPtr &event) {
        events[numberOfEvents] = std::move(event);
        push();
        numberOfEvents++;
    }

    TimeData time;
    EventArray<maxEvents> events;
    size_t numberOfEvents;
};

}

#endif
