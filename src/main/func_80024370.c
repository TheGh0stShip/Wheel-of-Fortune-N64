#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} State;

typedef struct {
    /* 0x00 */ u8 unk_00[0x20];
} Item;

extern Item D_80058E70[];

struct n64dk_r12 func_80024370(s32 arg1) {
    s32 event;
    struct n64dk_r12 sp18;
    s8 pad0;

    sp18.w[1] = 1;
    sp18.w[0] = 0;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            ((State *)((proc_t *)arg1)->unk_30)->unk_08 = 0;
            ((State *)((proc_t *)arg1)->unk_30)->unk_04 = D_80058E88;
            func_80022784(arg1, (s32)&D_80058EB0, (s32)&D_80058E90, 0);
            func_80022784(arg1, (s32)&D_80058EB0, (s32)D_80058E70, 1);
            return sp18;
        }
    }
    if ((D_800B96B0 & 0xA000 & 0xFFFF) != 0) {
        ((State *)((proc_t *)arg1)->unk_30)->unk_0C = 0;
        func_80002CE0(42);
        switch (((State *)((proc_t *)arg1)->unk_30)->unk_08) {
        case 0:
            func_80022BC8(arg1, (s32)&D_80058EB0, (s32)D_80058E70, 2);
            break;
        case 1:
            func_80026800();
            sp18.w[1] = 0;
            sp18.w[0] = 1;
            return sp18;
        default:
            func_80009F38("MainMenu1 Proc: button press invalid\n");
        }
    }
    if ((D_800B96B0 & 0x5000 & 0xFFFF) != 0) {
        func_80002CE0(42);
        func_80026800();
        sp18.w[1] = 0;
        sp18.w[0] = 1;
        return sp18;
    } else if ((D_800B96B0 & 2048 & 0xFFFF) != 0) {
        func_800229D0(arg1, (s32)&D_80058EB0, (s32)D_80058E70, 2);
    } else if ((D_800B96B0 & 1024 & 0xFFFF) != 0) {
        func_80022BC8(arg1, (s32)&D_80058EB0, (s32)D_80058E70, 2);
    } else if ((D_800B96B0 & 512 & 0xFFFF) != 0) {
        func_80022DC0(arg1, (s32)&D_80058EB0, (s32)&D_80058E70[((State *)((proc_t *)arg1)->unk_30)->unk_08], 0);
    } else if ((D_800B96B0 & 256 & 0xFFFF) != 0) {
        func_80022FE0(arg1, (s32)&D_80058EB0, (s32)&D_80058E70[((State *)((proc_t *)arg1)->unk_30)->unk_08], 0);
    }
    if (((State *)((proc_t *)arg1)->unk_30)->unk_0C <= 0) {
        if (D_800B9956 >= 41) {
            func_80022FE0(arg1, (s32)&D_80058EB0, (s32)&D_80058E70[((State *)((proc_t *)arg1)->unk_30)->unk_08], 0);
        } else if (D_800B9956 < -40) {
            func_80022DC0(arg1, (s32)&D_80058EB0, (s32)&D_80058E70[((State *)((proc_t *)arg1)->unk_30)->unk_08], 0);
        }
        if (D_800B9957 >= 41) {
            func_800229D0(arg1, (s32)&D_80058EB0, (s32)D_80058E70, 2);
        } else if (D_800B9957 < -40) {
            func_80022BC8(arg1, (s32)&D_80058EB0, (s32)D_80058E70, 2);
        }
    } else {
        ((State *)((proc_t *)arg1)->unk_30)->unk_0C = ((State *)((proc_t *)arg1)->unk_30)->unk_0C - D_800B96B4;
    }
    return sp18;
}
