#include "wof.h"

void __amHandleDoneMsg(AudioInfo *info) {
    u32 samplesLeft;

    samplesLeft = osAiGetLength() >> 2;
    if (samplesLeft == 0 && firstTime == 0) {
        firstTime = 0;
    }
}
