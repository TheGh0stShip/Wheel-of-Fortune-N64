typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08[0x4];
    /* 0x0C */ s32 unk_0C;
} State;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ State *state;
} Obj;

typedef struct {
    /* 0x00 */ u8 unk_00[0xC];
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
} Menu;

extern u8 D_800B96C4;
s32 func_80002CE0(s32 arg0);
void func_800226BC(s32 arg0, s32 arg1, s32 arg2);

void func_80022DC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_80002CE0(43);
    func_800226BC((((Menu *)arg2)->unk_0C + ((Obj *)arg0)->state->unk_04 * ((Menu *)arg2)->unk_14) * 40 + arg1,
                  ((Menu *)arg2)->unk_14, 0);
    ((Obj *)arg0)->state->unk_04--;
    if (((Obj *)arg0)->state->unk_04 < 0) {
        ((Obj *)arg0)->state->unk_04 = ((Menu *)arg2)->unk_10 - 1;
    }
    if (arg3 != 0) {
        while ((D_800B96C4 >> ((Obj *)arg0)->state->unk_04) % 2 == 0 && ((Obj *)arg0)->state->unk_04 != 4) {
            ((Obj *)arg0)->state->unk_04--;
            if (((Obj *)arg0)->state->unk_04 < 0) {
                ((Obj *)arg0)->state->unk_04 = ((Menu *)arg2)->unk_10 - 1;
            }
        }
    }
    ((Menu *)arg2)->unk_18 = ((Obj *)arg0)->state->unk_04;
    func_800226BC((((Menu *)arg2)->unk_0C + ((Obj *)arg0)->state->unk_04 * ((Menu *)arg2)->unk_14) * 40 + arg1,
                  ((Menu *)arg2)->unk_14, 1);
    ((Obj *)arg0)->state->unk_0C = 15;
}
