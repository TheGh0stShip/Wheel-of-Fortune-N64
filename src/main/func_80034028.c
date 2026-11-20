#include "wof.h"

struct n64dk_r12 func_80034028(s32 arg1) {
    struct n64dk_r12 ret;
    s32 event;
    s32 i;
    obj_t *sprite;

    sprite = ((data80034028_t *)((proc_t *)arg1)->unk_30)->sprite;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            ((data80034028_t *)((proc_t *)arg1)->unk_30)->timer = 0;
            ((data80034028_t *)((proc_t *)arg1)->unk_30)->frame = 0;
            break;
        }
    }
    ((data80034028_t *)((proc_t *)arg1)->unk_30)->timer += D_800B96B4;
    if (((data80034028_t *)((proc_t *)arg1)->unk_30)->timer >= 4) {
        ((data80034028_t *)((proc_t *)arg1)->unk_30)->timer %= 4;
        ((data80034028_t *)((proc_t *)arg1)->unk_30)->frame++;
        if (((data80034028_t *)((proc_t *)arg1)->unk_30)->frame >= 4) {
            ((data80034028_t *)((proc_t *)arg1)->unk_30)->frame = 0;
            ((data80034028_t *)((proc_t *)arg1)->unk_30)->count--;
            if (((data80034028_t *)((proc_t *)arg1)->unk_30)->count < 0) {
                ret.w[1] = 0;
                ret.w[0] = 1;
                return ret;
            }
        }
    }
    i = 0;
    while (i < D_800B96B4) {
        ((data80034028_t *)((proc_t *)arg1)->unk_30)->vy += D_8005C958;
        ((data80034028_t *)((proc_t *)arg1)->unk_30)->vx -= D_8005C95C;
        ((data80034028_t *)((proc_t *)arg1)->unk_30)->x += ((data80034028_t *)((proc_t *)arg1)->unk_30)->vx;
        ((data80034028_t *)((proc_t *)arg1)->unk_30)->y += ((data80034028_t *)((proc_t *)arg1)->unk_30)->vy;
        i++;
    }
    sprite->x = (s32)((data80034028_t *)((proc_t *)arg1)->unk_30)->x;
    sprite->y = (s32)((data80034028_t *)((proc_t *)arg1)->unk_30)->y;
    if (sprite->x < 0 || sprite->y < 0 || sprite->x >= 321 || sprite->y >= 201) {
        ret.w[1] = 0;
        ret.w[0] = 1;
        return ret;
    }
    sprite->unk_44 = D_8005C948[((data80034028_t *)((proc_t *)arg1)->unk_30)->frame];
    ret.w[1] = 1;
    ret.w[0] = 0;
    return ret;
}
