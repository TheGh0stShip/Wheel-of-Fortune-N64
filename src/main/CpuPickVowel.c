#include "wof.h"


/*
=====================
CpuPickVowel

The machine's vowel: a right one with the chance of its skill.
=====================
*/
s32 CpuPickVowel(f32 skill) {
    f32 roll;
    u8 result;

    RemoveCalledLetters(cpuVowels);
    roll = (f32)Random(100);
    roll = roll / 100.0f;
    if (roll < skill) {
        result = PickHitLetter(cpuVowels);
    } else {
        result = PickMissLetter(cpuVowels);
        if (result == 32) {
            result = PickHitLetter(cpuVowels);
        }
    }
    return result;
}
