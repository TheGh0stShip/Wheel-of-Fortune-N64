#include "wof.h"
#include "mpeg/proto.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} Rect;

typedef struct {
    /* 0x000 */ u8 unk_000[0x8];
    /* 0x008 */ s32 unk_008;
    /* 0x00C */ s32 unk_00C;
    /* 0x010 */ u8 unk_010[0x228];
    /* 0x238 */ s32 unk_238;
    /* 0x23C */ u8 unk_23C[0x4];
    /* 0x240 */ s32 unk_240;
    /* 0x244 */ u8 unk_244[0x1C];
    /* 0x260 */ Rect *unk_260;
} Obj;

void func_8009D300(Obj *arg0) {
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;

    sp18 = arg0->unk_260->unk_00;
    sp1C = arg0->unk_260->unk_04;
    sp20 = arg0->unk_260->unk_08;
    sp24 = arg0->unk_260->unk_0C;
    sp28 = arg0->unk_008 * 16;
    sp2C = arg0->unk_00C * 16;
    sp30 = arg0->unk_240;
    sp34 = arg0->unk_238;
    func_800A2594(sp18, sp1C, sp20, sp24, sp28, sp2C);
}
