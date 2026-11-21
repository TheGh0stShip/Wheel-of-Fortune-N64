// PlayContestantClip.c -- plays a movie as a player's picture, if the contestant has one; prints
// InitContestants' and InitAnim's messages

#include "wof.h"

/*
=====================
PlayContestantClip

Plays a movie as a player's picture, if the contestant has one; prints InitContestants' and
InitAnim's messages.
=====================
*/
s32 PlayContestantClip(s32 arg0, s32 arg1, s32 arg2) {
    obj_t *obj;
    proc_t *other;
    s32 unused;  /* NOTE: unused in the original */
    clip_t *slots;
    s32 unused2;  /* NOTE: unused in the original */
    s32 unused3;  /* NOTE: unused in the original */
    s32 unused4;  /* NOTE: unused in the original */
    s32 sp34;

    sp34 = 0x2000000;
    if (players[arg2].contestant >= 6) {
        func_80009F38("InitContestants: invalid image num");
    }
    slots = contestantMovies[players[arg2].contestant];
    if (slots[arg0].count > 0) {
        obj = FindObj(arg2 | 0xA020000, -1);
        if (obj == 0) {
            func_80009F38(D_800019BC);
        }
        other = FindProc(arg2 | 0xA000300, -1);
        if (other != 0) {
            KillProc(other, 0);
        }
        PlayClip(slots[arg0].movie, slots[arg0].unk_20, obj, arg2, arg1);
        return 1;
        return; /* dead, kept for the match */
    }
    return 0;
}
