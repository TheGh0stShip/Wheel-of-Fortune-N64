#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} State;

typedef struct {
    u8 unk_00[0x20];
} Item;

extern Item D_80058AA8[];

struct n64dk_r12 func_80025150(s32 arg1) {
    s32 event;
    struct n64dk_r12 ret;
    s8 pad0;

    ret.w[1] = 1;
    ret.w[0] = 0;
    for (;;) {
        event = func_8000ACE8(arg1);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            ((State *)((proc_t *)arg1)->unk_30)->unk_08 = 0;
            ((State *)((proc_t *)arg1)->unk_30)->unk_04 = 0;
            func_80022784(arg1, (s32)&D_80058B28, (s32)&D_80058AA8, 1);
            func_80022784(arg1, (s32)&D_80058B28, (s32)&D_80058AC8, 0);
            func_80022784(arg1, (s32)&D_80058B28, (s32)&D_80058AE8, 0);
            func_80022784(arg1, (s32)&D_80058B28, (s32)&D_80058B08, 0);
            return ret;
        case 36:
            func_8000ADEC(arg1);
            func_8000AF00();
            func_8000B9FC(1);
            func_8000BE6C();
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    if ((D_800B96B0 & 0xA000 & 0xFFFF) != 0) {
        func_80002CE0(42);
        ((State *)((proc_t *)arg1)->unk_30)->unk_0C = 0;
        switch (((State *)((proc_t *)arg1)->unk_30)->unk_08) {
        case 0:
            func_8002500C();
            func_8000B9FC(1);
            func_8000315C();
            func_8000AAB0(arg1, 36, 0);
            ret.w[1] = 1;
            ret.w[0] = 2;
            return ret;
            break;
        case 1:
            func_8000AE70(0xA000300, -256, 1);
            func_80025FA8();
            ret.w[1] = 0;
            ret.w[0] = 1;
            break;
        case 2:
            func_8000AE70(0xA000300, -256, 1);
            func_80026DEC();
            ret.w[1] = 0;
            ret.w[0] = 1;
            break;
        case 3:
            func_8000AE70(0xA000300, -256, 1);
            func_80026E50();
            ret.w[1] = 0;
            ret.w[0] = 1;
            break;
        default:
            func_80009F38("MainMenu3 Proc: button press invalid\n");
        }
    }
    if ((D_800B96B0 & 0x1000 & 0xFFFF) != 0) {
        func_80002CE0(42);
        func_8002500C();
        func_8000315C();
        func_8000B9FC(1);
        func_8000AAB0(arg1, 36, 0);
        ret.w[1] = 1;
        ret.w[0] = 2;
        return ret;
    } else if ((D_800B96B0 & 0x800 & 0xFFFF) != 0) {
        func_800229D0(arg1, (s32)&D_80058B28, (s32)&D_80058AA8, 4);
    } else if ((D_800B96B0 & 0x400 & 0xFFFF) != 0) {
        func_80022BC8(arg1, (s32)&D_80058B28, (s32)&D_80058AA8, 4);
    } else if ((D_800B96B0 & 0x200 & 0xFFFF) != 0) {
        func_80022DC0(arg1, (s32)&D_80058B28, (s32)&D_80058AA8[((State *)((proc_t *)arg1)->unk_30)->unk_08], 0);
    } else if ((D_800B96B0 & 0x100 & 0xFFFF) != 0) {
        func_80022FE0(arg1, (s32)&D_80058B28, (s32)&D_80058AA8[((State *)((proc_t *)arg1)->unk_30)->unk_08], 0);
    } else if ((D_800B96B0 & 0x4 & 0xFFFF) != 0) {
        return ret;
    } else if ((D_800B96B0 & 0x8 & 0xFFFF) != 0) {
        return ret;
    } else if ((D_800B96B0 & 0x4000 & 0xFFFF) != 0) {
        return ret;
    }
    if (((State *)((proc_t *)arg1)->unk_30)->unk_0C <= 0) {
        if (D_800B9954.stick_x >= 41) {
            func_80022FE0(arg1, (s32)&D_80058B28, (s32)&D_80058AA8[((State *)((proc_t *)arg1)->unk_30)->unk_08], 0);
        } else if (D_800B9954.stick_x < -40) {
            func_80022DC0(arg1, (s32)&D_80058B28, (s32)&D_80058AA8[((State *)((proc_t *)arg1)->unk_30)->unk_08], 0);
        }
        if (D_800B9954.stick_y >= 41) {
            func_800229D0(arg1, (s32)&D_80058B28, (s32)&D_80058AA8, 4);
        } else if (D_800B9954.stick_y < -40) {
            func_80022BC8(arg1, (s32)&D_80058B28, (s32)&D_80058AA8, 4);
        }
    } else {
        ((State *)((proc_t *)arg1)->unk_30)->unk_0C = ((State *)((proc_t *)arg1)->unk_30)->unk_0C - D_800B96B4;
    }
    return ret;
}
