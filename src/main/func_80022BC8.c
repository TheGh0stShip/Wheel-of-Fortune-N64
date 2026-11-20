#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 index;
    /* 0x0C */ s32 unk_0C;
} State;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x14];
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ void (*callback)(s32);
} Entry;

void func_80022BC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_80002CE0(44);
    func_80022784(arg0, arg1, (s32)&((Entry *)arg2)[((State *)((proc_t *)arg0)->unk_30)->index], 0);
    ((Entry *)arg2)[((State *)((proc_t *)arg0)->unk_30)->index].unk_18 = ((State *)((proc_t *)arg0)->unk_30)->unk_04;
    do {
        ((State *)((proc_t *)arg0)->unk_30)->index++;
        if (((State *)((proc_t *)arg0)->unk_30)->index >= arg3) {
            ((State *)((proc_t *)arg0)->unk_30)->index = 0;
        }
    } while (((Entry *)arg2)[((State *)((proc_t *)arg0)->unk_30)->index].unk_00 == 0);
    ((State *)((proc_t *)arg0)->unk_30)->unk_04 = ((Entry *)arg2)[((State *)((proc_t *)arg0)->unk_30)->index].unk_18;
    if (((Entry *)arg2)[((State *)((proc_t *)arg0)->unk_30)->index].callback != 0) {
        ((Entry *)arg2)[((State *)((proc_t *)arg0)->unk_30)->index].callback(((State *)((proc_t *)arg0)->unk_30)->index);
    }
    func_80022784(arg0, arg1, (s32)&((Entry *)arg2)[((State *)((proc_t *)arg0)->unk_30)->index], 1);
    ((State *)((proc_t *)arg0)->unk_30)->unk_0C = 15;
}
