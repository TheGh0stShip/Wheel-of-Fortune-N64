#include "wof.h"

s32 func_8000B234(s32 arg0) {
    obj_t *prev;
    obj_t *next;

    prev = (obj_t *)func_8000B060(arg0);
    if (prev == 0) {
        return 0;
    }
    next = ((obj_t *)arg0)->next;
    prev->next = next;
    ((obj_t *)arg0)->unk_0C = 0;
    ((obj_t *)arg0)->unk_04 = 0;
    D_800BCA10--;
    return 1;
}
