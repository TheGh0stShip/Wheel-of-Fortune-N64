#include "wof.h"

/*
=====================
FreeObj

Unlinks an obj and marks it free.
=====================
*/
s32 FreeObj(obj_t *obj) {
    obj_t *prev;
    obj_t *next;

    prev = GetObjBefore(obj);
    if (prev == 0) {
        return 0;
    }
    next = obj->next;
    prev->next = next;
    obj->draw = 0;
    obj->owner = 0;
    numObjs--;
    return 1;
}
