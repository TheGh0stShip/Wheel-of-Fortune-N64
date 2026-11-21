#include "wof.h"

/*
=====================
FreeObjClass

Frees every obj of a class.
=====================
*/
void FreeObjClass(s32 cls, s32 mask) {
    obj_t *node;

    node = FindObj(cls, mask);
    while (node != 0) {
        FreeObj(node);
        node = FindNextObj(node, cls, mask);
    }
}
