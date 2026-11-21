#include "wof.h"


/*
=====================
CpuPickConsonant

The machine's consonant: a right one with the chance of its skill.
=====================
*/
s32 CpuPickConsonant(f32 skill, proc_t *proc) {
    f32 roll;
    u8 result;

    RemoveCalledLetters(cpuConsonants);
    roll = Random(100);
    roll = roll / 100.0f;
    if (roll < skill) {
        result = PickHitLetter(cpuConsonants);
    } else {
        result = PickMissLetter(cpuConsonants);
        if (result == 32) {
            result = PickHitLetter(cpuConsonants);
        }
    }
    return result;
}
