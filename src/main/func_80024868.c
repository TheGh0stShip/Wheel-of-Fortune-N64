#include "wof.h"

typedef struct {
    /* 0x00 */ u8 pad0[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 cursor;
    /* 0x0C */ s32 delay;
} MenuData;

typedef struct {
    /* 0x00 */ u8 pad0[0x30];
    /* 0x30 */ MenuData *data;
} Task;

typedef struct {
    u8 b[32];
} Item;

extern s32 D_80001594;
extern Item D_80058FC8[];
extern s32 D_80058FE0;
extern s32 D_80058FE8;
extern s32 D_80059008;
extern u16 D_800B96B0;
extern s32 D_800B96B4;
extern s8 D_800B9956;
extern s8 D_800B9957;

struct n64dk_r12 func_80024868(s32 arg1) {
    s32 event;
    struct n64dk_r12 result;
    s8 pad0;

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            ((Task *)arg1)->data->cursor = 0;
            ((Task *)arg1)->data->unk_04 = D_80058FE0;
            func_80022784(arg1, (s32)&D_80059008, (s32)&D_80058FE8, 0);
            func_80022784(arg1, (s32)&D_80059008, (s32)D_80058FC8, 1);
            return result;
        }
    }
    if ((D_800B96B0 & 0xA000 & 0xFFFF) != 0) {
        ((Task *)arg1)->data->delay = 0;
        func_80002CE0(42);
        switch (((Task *)arg1)->data->cursor) {
        case 0:
            func_80022BC8(arg1, (s32)&D_80059008, (s32)D_80058FC8, 2);
            break;
        case 1:
            func_80026800();
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        default:
            func_80009F38(&D_80001594);
        }
    }
    if ((D_800B96B0 & 0x5000 & 0xFFFF) != 0) {
        func_80002CE0(42);
        func_80026800();
        result.w[1] = 0;
        result.w[0] = 1;
        return result;
    } else if ((D_800B96B0 & 2048 & 0xFFFF) != 0) {
        func_800229D0(arg1, (s32)&D_80059008, (s32)D_80058FC8, 2);
    } else if ((D_800B96B0 & 1024 & 0xFFFF) != 0) {
        func_80022BC8(arg1, (s32)&D_80059008, (s32)D_80058FC8, 2);
    } else if ((D_800B96B0 & 512 & 0xFFFF) != 0) {
        func_80022DC0(arg1, (s32)&D_80059008, (s32)&D_80058FC8[((Task *)arg1)->data->cursor], 0);
    } else if ((D_800B96B0 & 256 & 0xFFFF) != 0) {
        func_80022FE0(arg1, (s32)&D_80059008, (s32)&D_80058FC8[((Task *)arg1)->data->cursor], 0);
    }
    if (((Task *)arg1)->data->delay <= 0) {
        if (D_800B9956 >= 41) {
            func_80022FE0(arg1, (s32)&D_80059008, (s32)&D_80058FC8[((Task *)arg1)->data->cursor], 0);
        } else if (D_800B9956 < -40) {
            func_80022DC0(arg1, (s32)&D_80059008, (s32)&D_80058FC8[((Task *)arg1)->data->cursor], 0);
        }
        if (D_800B9957 >= 41) {
            func_800229D0(arg1, (s32)&D_80059008, (s32)D_80058FC8, 2);
        } else if (D_800B9957 < -40) {
            func_80022BC8(arg1, (s32)&D_80059008, (s32)D_80058FC8, 2);
        }
    } else {
        ((Task *)arg1)->data->delay -= D_800B96B4;
    }
    return result;
}
