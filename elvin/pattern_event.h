#ifndef ELVIN_PATTERN_EVENT_H
#define ELVIN_PATTERN_EVENT_H

#include <memory>
#include <array>

#include "event.h"
#include "pattern_value.h"
#include "time_data.h"
#include "indices.h"
#include "collections/interface.h"

namespace elvin {

template <typename CollectionType, typename DurationPattern,
          typename... CallbackArgs>
class PatternEvent : public Event {
public:
    PatternEvent(uint32_t time, CollectionType patterns,
                 DurationPattern durationPattern,
                 void(*callback)(CallbackArgs...)) :
            Event(time), patterns(std::move(patterns)),
            durationPattern(std::move(durationPattern)), callback(callback) {
    }
        
        
    virtual bool process(const TimeData &timeData) {
        PatternValue duration = durationPattern.next();

        if (!duration.exists) {
            // No duration, so don't run the callback or add any further events
            return false;
        }

        auto indices = typename IndexBuilder<sizeof...(CallbackArgs)>::type();
        bool shouldContinue = runCallback(indices);
        if (!shouldContinue) {
            // Pattern hasn't provided a value, so don't process the callback
            // or add any further events
            return false;
        }

        // All okay, so advance the time and re-add the event
        uint32_t dt = duration.value * timeData.beatLength;
        time += dt;
        return true;
    }

private:
    // Runs the callback samples collected from the patterns
    template <size_t... Is>
    bool runCallback(Indices<Is...>) {
        // Collect the next value from each of the patterns
        std::array<float, sizeof...(CallbackArgs)> values;
        for (uint32_t i=0; i<collections::interface::size(patterns); i++) {
            PatternValue value = collections::interface::next(patterns, i);

            if (!value.exists) {
                return false;
            }

            values[i] = value.value;
        }

        // Do the call
        callback(values[Is]...);
        (void) values;
        return true;
    }

    CollectionType patterns;
    DurationPattern durationPattern;
    void(*callback)(CallbackArgs...);
};

template <typename CollectionType, typename DurationPattern,
          typename... CallbackArgs>
using PatternEventPtr = std::unique_ptr<
                            PatternEvent<
                                CollectionType,
                                DurationPattern,
                                CallbackArgs...
                            >
                        >;

template <typename... CallbackArgs>
using PatternEventCallback = typename PatternEvent<CallbackArgs...>::Callback;

}


#endif
