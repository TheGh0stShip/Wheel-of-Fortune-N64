#include "wof.h"

typedef struct {
    /* 0x00 */ obj_t *unk_00;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 unk_08;
} State;

struct n64dk_r12 func_800103B4(s32 arg1) {
    struct n64dk_r12 sp10;
    obj_t *sprite;
    s32 event;
    s8 pad0;

    sprite = ((State *)((proc_t *)arg1)->unk_30)->unk_00;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            ((State *)((proc_t *)arg1)->unk_30)->unk_08 = 0;
            sprite->unk_48 = &D_01136108;
            break;
        case 2:
            sprite->unk_48 = &D_01135FF8;
            sp10.w[1] = 0;
            sp10.w[0] = 0;
            return sp10;
        }
    }
    ((State *)((proc_t *)arg1)->unk_30)->unk_08 = ((State *)((proc_t *)arg1)->unk_30)->unk_08 + D_800B96B4;
    if (((State *)((proc_t *)arg1)->unk_30)->unk_08 >= 6) {
        ((State *)((proc_t *)arg1)->unk_30)->unk_08 = 0;
        if (sprite->unk_48 == &D_01136080) {
            sprite->unk_48 = &D_01136108;
        } else {
            sprite->unk_48 = &D_01136080;
        }
    }
    sp10.w[1] = 3;
    sp10.w[0] = -1;
    return sp10;
}
