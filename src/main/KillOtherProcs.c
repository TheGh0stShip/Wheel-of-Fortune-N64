#include "wof.h"

/*
=====================
KillOtherProcs

Kills every proc but one.
=====================
*/
void KillOtherProcs(proc_t *proc) {
    struct procResult_s res;
    proc_t *node;

    node = &procst[0];
    while (node->next != 0) {
        node = node->next;
        if (node != proc) {
            KillProc(node, res.w[0]);  // BUG: res is never set
        }
    }
}
