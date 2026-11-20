#include "wof.h"

obj_t *FindNextObj(obj_t *obj, s32 cls, s32 mask) {
    while (obj->next != 0) {
        obj = obj->next;
        if ((obj->unk_08 & mask) == cls) {
            return obj;
        }
    }
    return 0;
}
