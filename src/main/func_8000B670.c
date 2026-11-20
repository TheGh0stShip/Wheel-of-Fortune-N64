#include "wof.h"

obj_t *func_8000B670(obj_t *obj, s32 arg1, s32 arg2) {
    while (obj->next != 0) {
        obj = obj->next;
        if ((obj->unk_08 & arg2) == arg1) {
            return obj;
        }
    }
    return 0;
}
