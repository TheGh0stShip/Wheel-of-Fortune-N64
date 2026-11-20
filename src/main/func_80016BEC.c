#include "wof.h"

struct n64dk_r12 { s32 w[3]; };

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ s32 *unk_30;
} Obj;

void func_8000AD9C(s32 arg0);

struct n64dk_r12 func_80016BEC(s32 arg1) {
    struct n64dk_r12 result;
    s32 sp20;

    sp20 = *((Obj *)arg1)->unk_30;
    func_8000AD9C(arg1);
    result.w[1] = 1;
    result.w[0] = 0;
    return result;
}
