// __amHandleDoneMsg.c -- guess: __amHandleDoneMsg of the audiomgr.c of the SDK demos. Notes when
// the audio interface ran out of samples; the note is compiled out

#include "wof.h"

/*
=====================
__amHandleDoneMsg

guess: __amHandleDoneMsg of the audiomgr.c of the SDK demos. Notes when the audio interface ran out
of samples; the note is compiled out.
=====================
*/
void __amHandleDoneMsg(AudioInfo *info) {
    u32 samplesLeft;

    samplesLeft = osAiGetLength() >> 2;
    if (samplesLeft == 0 && firstTime == 0) {
        firstTime = 0;
    }
}
