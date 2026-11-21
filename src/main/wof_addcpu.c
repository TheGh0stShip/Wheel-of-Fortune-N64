// wof_addcpu.c -- the machine's turn procs for the demo and for a game
//
// AddDemoCpu ends off an 8-byte boundary with AddCpu right after, which happens only inside an object.
// Whether CpuTurnProc before it and DrawMovie64 after it are this object's the text does not say.

#include "wof.h"

/*
=====================
AddDemoCpu

A machine turn proc for the demo, of skill 0.65.
=====================
*/
void AddDemoCpu(s32 player) {
    proc_t *task;
    s32 unused;   /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    task = CreatProc(CpuTurnProc, player | 0x2030000);
    task->data->playerProc.player = player;
    task->data->playerProc.skill = 0.65f;
    players[player].controller = 4;
    SetContestantSounds(player);
}

/*
=====================
AddCpu

A machine turn proc of the skill chosen.
=====================
*/
void AddCpu(s32 player) {
    proc_t *task;
    s32 unused;   /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    task = CreatProc(CpuTurnProc, player | 0x2030000);
    task->data->playerProc.player = player;
    task->data->playerProc.skill = cpuSkill;
}
