// AddPlayer.c -- the turn proc of a person

#include "wof.h"

/*
=====================
AddPlayer

The turn proc of a person.
=====================
*/
void AddPlayer(s32 player) {
    proc_t *task;
    s32 unused;   /* NOTE: unused in the original */
    s32 unused2;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    task = CreatProc(PlayerTurnProc, player | 0x2020000);
    task->data->playerProc.player = player;
}
