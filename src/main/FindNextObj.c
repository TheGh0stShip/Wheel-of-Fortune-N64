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
