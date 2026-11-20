#include "wof.h"

typedef struct {
    /* 0x0000 */ u8 unk_0000[0x1A40];
    /* 0x1A40 */ Mtx mtx[1];
} Scene;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0xC];
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ u8 unk_16[0x2E];
    /* 0x44 */ s32 unk_44;
} Obj;

typedef struct {
    /* 0x00 */ u8 unk_00[0x8];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8 unk_0C[0x4];
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ u8 unk_14[0xC];
    /* 0x20 */ s32 unk_20;
} Image;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ Image *unk_30;
} Actor;

extern s32 D_0113AD08;
extern s32 D_0113AD28;
extern s32 D_0113AD48;
extern s32 D_0113AE28;
extern s32 D_800B61A8;
extern Gfx *D_800B81E8;
extern s32 D_800BCD54;

void func_80030B5C(s32 arg0, s32 arg1) {
    Actor *actor;
    s32 pixels;
    Gfx *gfx;

    if (((Obj *)arg0)->unk_44 == 0) {
        return;
    }
    if (D_800BCD54 == 6) {
        actor = (Actor *)func_8000A990(0xA000400, -1);
        if (actor != 0) {
            pixels = actor->unk_30->unk_08 + actor->unk_30->unk_10 * 0x3000;
            func_8003143C(pixels, actor->unk_30->unk_20 * D_800B61A8);
        }
    }
    gfx = D_800B81E8++;
    gfx->w0 = 0x1020040;
    gfx->w1 = (s32)&D_0113AE28;
    func_8003C2F0(&((Scene *)arg1)->mtx[((Obj *)arg0)->unk_00], ((Obj *)arg0)->unk_10, ((Obj *)arg0)->unk_12, ((Obj *)arg0)->unk_14);
    gfx = D_800B81E8++;
    gfx->w0 = 0x1000040;
    gfx->w1 = (s32)&((Scene *)arg1)->mtx[((Obj *)arg0)->unk_00];
    gfx = D_800B81E8++;
    gfx->w0 = 0xBB000001;
    gfx->w1 = -1;
    gfx = D_800B81E8++;
    gfx->w0 = 0xE7000000;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0xB900031D;
    gfx->w1 = 0x553078;
    gfx = D_800B81E8++;
    gfx->w0 = 0xFC127E24;
    gfx->w1 = -3079;
    gfx = D_800B81E8++;
    gfx->w0 = 0xFD100000;
    gfx->w1 = ((Obj *)arg0)->unk_44;
    gfx = D_800B81E8++;
    gfx->w0 = 0xF5100000;
    gfx->w1 = 0x7094260;
    gfx = D_800B81E8++;
    gfx->w0 = 0xE6000000;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0xF3000000;
    gfx->w1 = 0x77FF080;
    gfx = D_800B81E8++;
    gfx->w0 = 0xE7000000;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0xF5102000;
    gfx->w1 = 0x94260;
    gfx = D_800B81E8++;
    gfx->w0 = 0xF2000000;
    gfx->w1 = 0xFC07C;
    gfx = D_800B81E8++;
    gfx->w0 = 0xE7000000;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0x6000000;
    gfx->w1 = (s32)&D_0113AD08;
    gfx = D_800B81E8++;
    gfx->w0 = 0xFD100000;
    gfx->w1 = ((Obj *)arg0)->unk_44 + 0x1000;
    gfx = D_800B81E8++;
    gfx->w0 = 0xF5100000;
    gfx->w1 = 0x7094260;
    gfx = D_800B81E8++;
    gfx->w0 = 0xE6000000;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0xF3000000;
    gfx->w1 = 0x77FF080;
    gfx = D_800B81E8++;
    gfx->w0 = 0xE7000000;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0xF5102000;
    gfx->w1 = 0x94260;
    gfx = D_800B81E8++;
    gfx->w0 = 0xF2000000;
    gfx->w1 = 0xFC07C;
    gfx = D_800B81E8++;
    gfx->w0 = 0x6000000;
    gfx->w1 = (s32)&D_0113AD28;
    gfx = D_800B81E8++;
    gfx->w0 = 0xFD100000;
    gfx->w1 = ((Obj *)arg0)->unk_44 + 0x2000;
    gfx = D_800B81E8++;
    gfx->w0 = 0xF5100000;
    gfx->w1 = 0x7094260;
    gfx = D_800B81E8++;
    gfx->w0 = 0xE6000000;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0xF3000000;
    gfx->w1 = 0x77FF080;
    gfx = D_800B81E8++;
    gfx->w0 = 0xE7000000;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0xF5102000;
    gfx->w1 = 0x94260;
    gfx = D_800B81E8++;
    gfx->w0 = 0xF2000000;
    gfx->w1 = 0xFC07C;
    gfx = D_800B81E8++;
    gfx->w0 = 0x6000000;
    gfx->w1 = (s32)&D_0113AD48;
    gfx = D_800B81E8++;
    gfx->w0 = 0xE7000000;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0xB900031D;
    gfx->w1 = 0x552078;
}
