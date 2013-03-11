#ifndef ELVIN_TIME_DATA_H
#define ELVIN_TIME_DATA_H

#include "thelonious/types.h"
#include "thelonious/rates.h"

using namespace thelonious;

namespace elvin {

struct TimeData {
public:
    TimeData(float bpm) :
        bpm(bpm), time(0.0f), beat(0.0f), beatInBar(0.0f), bar(0.0f),
        beatsPerBar(0.0f), lastBeatTime(0.0f),
        beatLength(SAMPLE_RATE * 60.0f / bpm) {}
        
    float bpm;
    uint32_t time;
    uint32_t beat;
    uint32_t beatInBar;
    uint32_t bar;
    uint32_t beatsPerBar;

    uint32_t lastBeatTime;
    uint32_t beatLength;
};

}

#endif
