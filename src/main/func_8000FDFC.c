#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} State;

struct n64dk_r12 func_8000FDFC(s32 arg1) {
    struct n64dk_r12 ret;
    s32 sp20;
    s32 event;
    s8 pad0;

    sp20 = ((State *)((proc_t *)arg1)->unk_30)->unk_00;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            func_80016098();
            func_80032B10();
            func_80032AD4(1);
            ((State *)((proc_t *)arg1)->unk_30)->unk_04 = 0;
            D_800B96A8++;
            func_8000AAB0(arg1, 41, 0);
            return func_8000FC3C(arg1);
        case 41:
            D_800B96A8 += D_800B9990[D_800FB808].unk_000 / 5000;
            return func_8000FC3C(arg1);
        case 34:
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    return func_8000FC3C(arg1);
}
