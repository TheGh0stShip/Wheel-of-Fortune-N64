#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x12];
    /* 0x12 */ union {
        s16 s;
        u16 u;
    } unk_12;
    /* 0x14 */ u8 unk_14[0x18];
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ u8 unk_30[0x18];
    /* 0x48 */ s32 *unk_48;
} State;

struct n64dk_r12 func_8000C310(s32 arg1) {
    struct n64dk_r12 result;
    State *state;
    s32 event;

    state = *(State **)((proc_t *)arg1)->unk_30;
    for (;;) {
        event = func_8000ACE8(arg1);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 34:
        case 36:
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    result.w[1] = 1;
    result.w[0] = 0;
    func_8000AD9C(arg1);
    result.w[1] = 1;
    result.w[0] = 0;
    state->unk_2C -= (f32)D_800B96B4;
    if (D_800B3994 >= 601) {
        state->unk_12.s = state->unk_12.u + D_800B96B6;
    }
    if (state->unk_12.s >= 41) {
        state->unk_12.s = 40;
    }
    if (D_800B3994 % 2 == 1) {
        if (state->unk_48 == &D_011358C0) {
            state->unk_48 = &D_01135908;
        } else {
            state->unk_48 = &D_011358C0;
        }
    }
    return result;
}
