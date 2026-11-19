typedef unsigned char u8;
typedef signed int s32;
struct n64dk_r12 { s32 w[3]; };

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
} State;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ State *state;
} Obj;

extern s32 D_800B96B4;
extern s32 D_800BA5D8;
void func_8000A850(s32 arg0);
s32 func_8000ACE8(s32 arg0);

struct n64dk_r12 func_80016734(s32 arg1) {
    s32 event;
    struct n64dk_r12 result;
    s32 sp28;

    sp28 = ((Obj *)arg1)->state->unk_00;
    result.w[1] = 1;
    result.w[0] = 0;
    for (;;) {
        event = func_8000ACE8(arg1);
        if (event == 0) {
            break;
        }
        switch (event) {
        case 8:
            D_800BA5D8 = ((Obj *)arg1)->state->unk_08 + ((Obj *)arg1)->state->unk_0C * 36;
            return result;
        }
    }
    ((Obj *)arg1)->state->unk_0C += D_800B96B4;
    if (((Obj *)arg1)->state->unk_0C >= ((Obj *)arg1)->state->unk_10) {
        D_800BA5D8 = (((Obj *)arg1)->state->unk_08 - 36) + ((Obj *)arg1)->state->unk_10 * 36;
        func_8000A850(45);
        result.w[1] = 0;
        result.w[0] = 0;
        return result;
    }
    D_800BA5D8 = ((Obj *)arg1)->state->unk_08 + ((Obj *)arg1)->state->unk_0C * 36;
    return result;
}
