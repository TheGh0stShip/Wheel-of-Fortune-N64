#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x2C];
    /* 0x2C */ f32 unk_2C;
} Actor;

extern u16 D_800B9954;

struct n64dk_r12 func_8000F740(s32 arg1) {
    struct n64dk_r12 result;
    Actor *actor;

    actor = *(Actor **)((proc_t *)arg1)->unk_30;
    func_8000AD9C(arg1);
    result.w[1] = 1;
    result.w[0] = 0;
    if ((D_800B9954 & 16 & 0xFFFF) != 0) {
        actor->unk_2C = actor->unk_2C - 0.25;
    }
    if ((D_800B9954 & 32 & 0xFFFF) != 0) {
        actor->unk_2C = actor->unk_2C + 0.25;
    }
    return result;
}
