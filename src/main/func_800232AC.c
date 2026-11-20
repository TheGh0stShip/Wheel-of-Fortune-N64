#include "wof.h"

typedef struct {
    /* 0x00 */ u8 pad0[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 cursor;
    /* 0x0C */ s32 delay;
} MenuData;

typedef struct {
    u8 b[32];
} Item;

extern Item D_800584C8[];
extern s32 D_800584E0;

struct n64dk_r12 func_800232AC(s32 arg1) {
    s32 event;
    s32 cursor;
    struct n64dk_r12 result;
    s8 pad0;

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            ((MenuData *)((proc_t *)arg1)->unk_30)->cursor = 0;
            ((MenuData *)((proc_t *)arg1)->unk_30)->unk_04 = D_800584E0;
            func_80022784(arg1, (s32)&D_80058548, (s32)&D_800584E8, 0);
            func_80022784(arg1, (s32)&D_80058548, (s32)&D_80058508, 0);
            func_80022784(arg1, (s32)&D_80058548, (s32)&D_80058528, 0);
            func_80022784(arg1, (s32)&D_80058548, (s32)D_800584C8, 1);
            return result;
        }
    }
    if ((D_800B96B0 & 0xA000 & 0xFFFF) != 0) {
        ((MenuData *)((proc_t *)arg1)->unk_30)->delay = 0;
        func_80002CE0(42);
        switch (((MenuData *)((proc_t *)arg1)->unk_30)->cursor) {
        case 0:
            func_80022BC8(arg1, (s32)&D_80058548, (s32)D_800584C8, 4);
            break;
        case 1:
            func_80022BC8(arg1, (s32)&D_80058548, (s32)D_800584C8, 4);
            break;
        case 2:
            func_80022BC8(arg1, (s32)&D_80058548, (s32)D_800584C8, 4);
            break;
        case 3:
            func_80023200();
            func_800263DC();
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        default:
            func_80009F38(D_80001594);
        }
    }
    if ((D_800B96B0 & 0x5000 & 0xFFFF) != 0) {
        func_80002CE0(42);
        func_80023200();
        func_80026800();
        result.w[1] = 0;
        result.w[0] = 1;
        return result;
    } else if ((D_800B96B0 & 2048 & 0xFFFF) != 0) {
        func_800229D0(arg1, (s32)&D_80058548, (s32)D_800584C8, 4);
    } else if ((D_800B96B0 & 1024 & 0xFFFF) != 0) {
        func_80022BC8(arg1, (s32)&D_80058548, (s32)D_800584C8, 4);
    } else if ((D_800B96B0 & 512 & 0xFFFF) != 0) {
        func_80022DC0(arg1, (s32)&D_80058548, (s32)&D_800584C8[((MenuData *)((proc_t *)arg1)->unk_30)->cursor], 1);
    } else if ((D_800B96B0 & 256 & 0xFFFF) != 0) {
        func_80022FE0(arg1, (s32)&D_80058548, (s32)&D_800584C8[((MenuData *)((proc_t *)arg1)->unk_30)->cursor], 1);
    } else if ((D_800B96B0 & 0x8000 & 0xFFFF) != 0) {
        return result;
    }
    if (((MenuData *)((proc_t *)arg1)->unk_30)->delay <= 0) {
        if (D_800B9956 >= 41) {
            func_80022FE0(arg1, (s32)&D_80058548, (s32)&D_800584C8[((MenuData *)((proc_t *)arg1)->unk_30)->cursor], 1);
        } else if (D_800B9956 < -40) {
            func_80022DC0(arg1, (s32)&D_80058548, (s32)&D_800584C8[((MenuData *)((proc_t *)arg1)->unk_30)->cursor], 1);
        }
        if (D_800B9957 >= 41) {
            func_800229D0(arg1, (s32)&D_80058548, (s32)D_800584C8, 4);
        } else if (D_800B9957 < -40) {
            func_80022BC8(arg1, (s32)&D_80058548, (s32)D_800584C8, 4);
        }
    } else {
        ((MenuData *)((proc_t *)arg1)->unk_30)->delay -= D_800B96B4;
    }
    cursor = ((MenuData *)((proc_t *)arg1)->unk_30)->cursor;
    if (cursor < 3) {
        switch (((MenuData *)((proc_t *)arg1)->unk_30)->unk_04) {
        case 0:
            D_80058548[(cursor * 4) + 10].unk_20 = (s32)&D_01158068;
            D_80058548[(cursor * 4) + 10].unk_24 = (s32)&D_0115B868;
            break;
        case 1:
            D_80058548[(cursor * 4) + 10].unk_20 = (s32)&D_01158868;
            D_80058548[(cursor * 4) + 10].unk_24 = (s32)&D_0115C068;
            break;
        case 2:
            D_80058548[(cursor * 4) + 10].unk_20 = (s32)&D_01159068;
            D_80058548[(cursor * 4) + 10].unk_24 = (s32)&D_0115C868;
            break;
        case 3:
            D_80058548[(cursor * 4) + 10].unk_20 = (s32)&D_01159868;
            D_80058548[(cursor * 4) + 10].unk_24 = (s32)&D_0115D068;
            break;
        case 4:
            D_80058548[(cursor * 4) + 10].unk_20 = (s32)&D_01157868;
            D_80058548[(cursor * 4) + 10].unk_24 = (s32)&D_0115B068;
            break;
        }
    }
    return result;
}
