// GetLastProc.c -- the last proc of the list, after which CreatProc links a new one; named after
// GetProcBefore

#include "wof.h"

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
