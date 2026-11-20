#include "wof.h"

typedef struct {
    /* 0x00 */ obj_t *sprite;
    /* 0x04 */ s32 frame;
    /* 0x08 */ s32 timer;
    /* 0x0C */ u8 unk_0C[0x4];
    /* 0x10 */ s32 count;
    /* 0x14 */ f32 x;
    /* 0x18 */ f32 y;
    /* 0x1C */ f32 vx;
    /* 0x20 */ f32 vy;
} State;

struct n64dk_r12 func_80034028(s32 arg1) {
    struct n64dk_r12 ret;
    s32 event;
    s32 i;
    obj_t *sprite;

    sprite = ((State *)((proc_t *)arg1)->unk_30)->sprite;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            ((State *)((proc_t *)arg1)->unk_30)->timer = 0;
            ((State *)((proc_t *)arg1)->unk_30)->frame = 0;
            break;
        }
    }
    ((State *)((proc_t *)arg1)->unk_30)->timer += D_800B96B4;
    if (((State *)((proc_t *)arg1)->unk_30)->timer >= 4) {
        ((State *)((proc_t *)arg1)->unk_30)->timer %= 4;
        ((State *)((proc_t *)arg1)->unk_30)->frame++;
        if (((State *)((proc_t *)arg1)->unk_30)->frame >= 4) {
            ((State *)((proc_t *)arg1)->unk_30)->frame = 0;
            ((State *)((proc_t *)arg1)->unk_30)->count--;
            if (((State *)((proc_t *)arg1)->unk_30)->count < 0) {
                ret.w[1] = 0;
                ret.w[0] = 1;
                return ret;
            }
        }
    }
    i = 0;
    while (i < D_800B96B4) {
        ((State *)((proc_t *)arg1)->unk_30)->vy += D_8005C958;
        ((State *)((proc_t *)arg1)->unk_30)->vx -= D_8005C95C;
        ((State *)((proc_t *)arg1)->unk_30)->x += ((State *)((proc_t *)arg1)->unk_30)->vx;
        ((State *)((proc_t *)arg1)->unk_30)->y += ((State *)((proc_t *)arg1)->unk_30)->vy;
        i++;
    }
    sprite->x = (s32)((State *)((proc_t *)arg1)->unk_30)->x;
    sprite->y = (s32)((State *)((proc_t *)arg1)->unk_30)->y;
    if (sprite->x < 0 || sprite->y < 0 || sprite->x >= 321 || sprite->y >= 201) {
        ret.w[1] = 0;
        ret.w[0] = 1;
        return ret;
    }
    sprite->unk_44 = D_8005C948[((State *)((proc_t *)arg1)->unk_30)->frame];
    ret.w[1] = 1;
    ret.w[0] = 0;
    return ret;
}
