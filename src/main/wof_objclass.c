// wof_objclass.c -- the next obj of a class, and freeing every obj of a class
//
// FindNextObj ends off an 8-byte boundary with FreeObjClass right after, which happens only inside an
// object. Whether FindObj before it and InitMemStack after it are this object's the text does not
// say.

#include "wof.h"

/*
=====================
FindNextObj

The next such obj after one.
=====================
*/
obj_t *FindNextObj(obj_t *obj, s32 cls, s32 mask) {
    while (obj->next != 0) {
        obj = obj->next;
        if ((obj->cls & mask) == cls) {
            return obj;
        }
    }
    return 0;
}

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
