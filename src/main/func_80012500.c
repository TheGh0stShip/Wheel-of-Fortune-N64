#include "wof.h"

typedef struct {
    /* 0x0000 */ u8 unk_0000[0x140];
    /* 0x0140 */ Mtx unk_0140[200];
    /* 0x3340 */ Mtx unk_3340[1];
} MtxBuf;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x14];
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ u8 unk_1C[0xC];
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ u8 unk_34[0x8];
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ u8 unk_40[0x8];
    /* 0x48 */ s32 unk_48;
} Obj;

extern Gfx *D_800B81E8;

void func_80012500(s32 arg0, s32 arg1) {
    Gfx *gfx;

    switch (func_80016638()) {
    case 0:
        func_8003C09C(&((MtxBuf *)arg1)->unk_0140[((Obj *)arg0)->unk_00], ((Obj *)arg0)->unk_18, ((Obj *)arg0)->unk_18, ((Obj *)arg0)->unk_18);
        func_8003BFF4(&((MtxBuf *)arg1)->unk_3340[((Obj *)arg0)->unk_00], ((Obj *)arg0)->unk_28, ((Obj *)arg0)->unk_2C, ((Obj *)arg0)->unk_30);
        gfx = D_800B81E8++;
        gfx->w0 = 0x1020040;
        gfx->w1 = ((Obj *)arg0)->unk_3C;
        gfx = D_800B81E8++;
        gfx->w0 = 0x1000040;
        gfx->w1 = (s32)&((MtxBuf *)arg1)->unk_0140[((Obj *)arg0)->unk_00];
        gfx = D_800B81E8++;
        gfx->w0 = 0x1000040;
        gfx->w1 = (s32)&((MtxBuf *)arg1)->unk_3340[((Obj *)arg0)->unk_00];
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00000A;
        gfx->w1 = 0xFFFEFFFF;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00040A;
        gfx->w1 = 0xFFFEFFFF;
        gfx = D_800B81E8++;
        gfx->w0 = 0x6000000;
        gfx->w1 = (s32)&D_010219C8;
        gfx = D_800B81E8++;
        gfx->w0 = 0x6000000;
        gfx->w1 = ((Obj *)arg0)->unk_48;
        func_80005300(1);
    }
}
