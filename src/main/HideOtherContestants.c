// HideOtherContestants.c -- frees the pictures of every player but the one whose turn it is

#include "wof.h"

/*
=====================
HideOtherContestants

Frees the pictures of every player but the one whose turn it is.
=====================
*/
void HideOtherContestants(void) {
    s32 i;
    obj_t *obj;
    proc_t *task;

    for (i = 0; i < 3; i++) {
        if (i != curPlayer) {
            task = FindProc(i | 0xA000300, -1);
            if (task != 0) {
                KillProc(task, 1);
                obj = FindObj(i | 0xA020000, -1);
                if (obj != 0) {
                    FreeObj(obj);
                }
            }
        }
    }
}
