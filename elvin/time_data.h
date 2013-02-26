#ifndef ELVIN_TIME_DATA_H
#define ELVIN_TIME_DATA_H

#include "thelonious/types.h"

namespace elvin {

struct TimeData {
public:
    TimeData(Sample bpm) :
        bpm(bpm), time(0), beat(0), beatInBar(0), bar(0), beatsPerBar(0),
        lastBeatTime(0), beatLength(60 / bpm * SAMPLE_RATE) {}
        
    Sample bpm;
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
