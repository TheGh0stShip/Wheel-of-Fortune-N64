#include "wof.h"

typedef struct {
    /* 0x0000 */ u8 unk_0000[0x140];
    /* 0x0140 */ Mtx unk_0140[100];
    /* 0x1A40 */ Mtx unk_1A40[100];
    /* 0x3340 */ Mtx unk_3340[1];
} Frame;

typedef struct {
    /* 0x00 */ s32 index;
    /* 0x04 */ u8 unk_04[0xC];
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ u8 unk_1C[0xC];
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ u8 unk_34[0x14];
    /* 0x48 */ s32 unk_48;
} Obj;

extern Gfx *D_800B81E8;

void func_80014A5C(s32 arg0, s32 arg1) {
    Gfx *gfx;

    func_8003C2F0(&((Frame *)arg1)->unk_1A40[((Obj *)arg0)->index], ((Obj *)arg0)->unk_10, ((Obj *)arg0)->unk_12, ((Obj *)arg0)->unk_14);
    func_8003C09C(&((Frame *)arg1)->unk_0140[((Obj *)arg0)->index], ((Obj *)arg0)->unk_18, ((Obj *)arg0)->unk_18, ((Obj *)arg0)->unk_18);
    func_8003BFF4(&((Frame *)arg1)->unk_3340[((Obj *)arg0)->index], ((Obj *)arg0)->unk_28, ((Obj *)arg0)->unk_2C, ((Obj *)arg0)->unk_30);
    gfx = D_800B81E8++;
    gfx->w0 = 0x1020040;
    gfx->w1 = (u32)&((Frame *)arg1)->unk_1A40[((Obj *)arg0)->index];
    gfx = D_800B81E8++;
    gfx->w0 = 0x1000040;
    gfx->w1 = (u32)&((Frame *)arg1)->unk_0140[((Obj *)arg0)->index];
    gfx = D_800B81E8++;
    gfx->w0 = 0x1000040;
    gfx->w1 = (u32)&((Frame *)arg1)->unk_3340[((Obj *)arg0)->index];
    gfx = D_800B81E8++;
    gfx->w0 = 0x6000000;
    gfx->w1 = (u32)&D_010219C8;
    func_80005300(1);
    gfx = D_800B81E8++;
    gfx->w0 = 0xBC00200A;
    gfx->w1 = 0x55555555;
    gfx = D_800B81E8++;
    gfx->w0 = 0xBC00240A;
    gfx->w1 = 0x55555555;
    gfx = D_800B81E8++;
    gfx->w0 = 0xBC00400A;
    gfx->w1 = 0x55555555;
    gfx = D_800B81E8++;
    gfx->w0 = 0xBC00440A;
    gfx->w1 = 0x55555555;
    gfx = D_800B81E8++;
    gfx->w0 = 0xBC00600A;
    gfx->w1 = 0x55555555;
    gfx = D_800B81E8++;
    gfx->w0 = 0xBC00640A;
    gfx->w1 = 0x55555555;
    gfx = D_800B81E8++;
    gfx->w0 = 0xBC00800A;
    gfx->w1 = 0x55555555;
    gfx = D_800B81E8++;
    gfx->w0 = 0xBC00840A;
    gfx->w1 = 0x55555555;
    gfx = D_800B81E8++;
    gfx->w0 = 0x6000000;
    gfx->w1 = ((Obj *)arg0)->unk_48;
    func_80005300(2);
    func_80005300(3);
    func_80005300(4);
    func_80005300(5);
    if (D_80057F34[D_800B81E0] != 0) {
        gfx = D_800B81E8++;
        gfx->w0 = 0x6000000;
        gfx->w1 = D_80057F34[D_800B81E0];
    }
    func_80005300(1);
}
