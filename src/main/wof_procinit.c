// wof_procinit.c -- clearing the procs and finding the last of them
//
// InitProcs ends off an 8-byte boundary with GetLastProc right after, which happens only inside an
// object. The object starts after the 4-byte gap that ends PrintStr. Whether it runs on into
// GetProcBefore the text does not say: the zero word before 0x800007F0 that may open the next object's
// read-only data falls either at that gap or here.

#include "wof.h"

/*
=====================
InitProcs

Clears procst and the data block owners.
=====================
*/
void InitProcs(void) {
    s32 i;

    for (i = 0; i < 70; i++) {
        procst[i].handler = 0;
        procst[i].id = i;
    }
    numProcs = 0;
    procst[0].handler = 0;
    procst[0].next = 0;
    initProcsZero = 0;
    for (i = 0; i < 70; i++) {
        blockOwners[i] = 0;
    }
}

/*
=====================
GetLastProc

The last proc of the list, after which CreatProc links a new one; named after GetProcBefore.
=====================
*/
proc_t *GetLastProc(void) {
    proc_t *next;
    proc_t *node;

    node = &procst[0];
    next = node->next;
    while (next != 0) {
        node = next;
        next = node->next;
    }
    return node;
}
