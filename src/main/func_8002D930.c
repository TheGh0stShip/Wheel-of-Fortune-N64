#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    union {
        /* 0x04 */ s32 index;
        /* 0x04 */ u8 bytes[4];
    } unk_04;
    /* 0x08 */ u8 unk_08[0x4];
    /* 0x0C */ s32 unk_0C;
} State;

extern u8 D_800B966A[];

struct n64dk_r12 func_8002D930(s32 arg1) {
    s32 event;
    struct n64dk_r12 result;
    s8 pad0;

    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = func_8000ACE8(arg1);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            func_8002D8B0(arg1);
            D_8005A998[((State *)((proc_t *)arg1)->unk_30)->unk_04.index].unk_10 = 1;
            ((State *)((proc_t *)arg1)->unk_30)->unk_0C = 0;
            return result;
        case 23:
            D_8005A998[((State *)((proc_t *)arg1)->unk_30)->unk_04.index].unk_10 = 0;
            func_8000A850(5);
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case 33:
            func_8000A850(5);
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case 34:
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    D_800B61B5 = ((State *)((proc_t *)arg1)->unk_30)->unk_04.bytes[3] + 65;
    D_8005A998[((State *)((proc_t *)arg1)->unk_30)->unk_04.index].unk_10 = 0;
    if (D_800B9990[D_800FB808].unk_014 == 4) {
        D_8005A998[((State *)((proc_t *)arg1)->unk_30)->unk_04.index].unk_10 = 1;
        return result;
    }
    if ((D_800B96B0 & 0xA000) != 0) {
        D_800BED88++;
        if (D_800B966A[((State *)((proc_t *)arg1)->unk_30)->unk_04.index] != ' ') {
            D_800B61B5 = ((State *)((proc_t *)arg1)->unk_30)->unk_04.bytes[3] + 65;
            func_8000A850(5);
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        } else {
            if (D_800B619C != 6) {
                D_800B61B5 = ((State *)((proc_t *)arg1)->unk_30)->unk_04.bytes[3] + 65;
                func_8000A850(5);
                result.w[1] = 0;
                result.w[0] = 0;
                return result;
            } else {
                func_80002CE0(1);
            }
            return result;
        }
    }
    if (((State *)((proc_t *)arg1)->unk_30)->unk_0C <= 0) {
        if ((D_800B9954.button & 0x800) != 0) {
            func_8002ACE8(arg1);
        } else if ((D_800B9954.button & 0x400) != 0) {
            func_8002AE60(arg1);
        } else if ((D_800B9954.button & 0x200) != 0) {
            func_8002A8C8(arg1, 1);
        } else if ((D_800B9954.button & 0x100) != 0) {
            func_8002AAD0(arg1, 1, 1);
        } else {
            if (D_800B9954.stick_x < -40) {
                func_8002A8C8(arg1, 1);
            }
            if (D_800B9954.stick_x >= 41) {
                func_8002AAD0(arg1, 1, 1);
            }
            if (D_800B9954.stick_y < -40) {
                func_8002AE60(arg1);
            }
            if (D_800B9954.stick_y >= 41) {
                func_8002ACE8(arg1);
            }
        }
    } else {
        ((State *)((proc_t *)arg1)->unk_30)->unk_0C -= D_800B96B4;
    }
    if (((State *)((proc_t *)arg1)->unk_30)->unk_04.index < 0) {
        ((State *)((proc_t *)arg1)->unk_30)->unk_04.index = 25;
    } else if (((State *)((proc_t *)arg1)->unk_30)->unk_04.index >= 26) {
        ((State *)((proc_t *)arg1)->unk_30)->unk_04.index = 0;
    }
    D_8005A998[((State *)((proc_t *)arg1)->unk_30)->unk_04.index].unk_10 = 1;
    return result;
}
