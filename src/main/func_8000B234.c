#include "wof.h"

s32 func_8000B234(obj_t *obj) {
    obj_t *prev;
    obj_t *next;

    prev = func_8000B060(obj);
    if (prev == 0) {
        return 0;
    }
    next = obj->next;
    prev->next = next;
    obj->unk_0C = 0;
    obj->unk_04 = 0;
    D_800BCA10--;
    return 1;
}
