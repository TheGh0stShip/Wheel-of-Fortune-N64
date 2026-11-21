// AddCpu.c -- a machine turn proc of the skill chosen

#include "wof.h"

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
