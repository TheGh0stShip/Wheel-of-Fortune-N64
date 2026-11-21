// wof_objinit.c -- clearing the objs and finding the last of them
//
// InitObjs ends off an 8-byte boundary with GetLastObj right after, which happens only inside an
// object. The object starts after the 4-byte gap that ends KillProcClass; whether it runs on into
// GetObjBefore the text does not say.

#include "wof.h"

/*
=====================
InitObjs

Clears objst.
=====================
*/
void InitObjs(void) {
    s32 i;

    for (i = 0; i < 100; i++) {
        objst[i].draw = 0;
        objst[i].index = i;
        objst[i].owner = 0;
    }
    numObjs = 0;
    objst[0].draw = 0;
    objst[0].next = 0;
}

/*
=====================
GetLastObj

The last obj of the list; named after GetObjBefore.
=====================
*/
obj_t *GetLastObj(void) {
    obj_t *next;
    obj_t *node;

    node = &objst[0];
    next = node->next;
    while (next != 0) {
        node = next;
        next = node->next;
    }
    return node;
}
