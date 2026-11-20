#include "wof.h"

typedef struct {
    /* 0x00 */ s32 w0;
    /* 0x04 */ s32 w1;
} Gfx;

typedef struct {
    /* 0x00 */ u8 unk_00[0x40];
} Mtx;

typedef struct {
    /* 0x0000 */ u8 unk_0000[0x140];
    /* 0x0140 */ Mtx unk_0140[100];
    /* 0x1A40 */ Mtx unk_1A40[100];
    /* 0x3340 */ Mtx unk_3340[1];
} MtxBuf;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0xC];
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ u8 unk_16[0x2];
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ u8 unk_1C[0xC];
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
} Obj;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x14];
} Layer;

extern Layer D_80057BB0[];
extern s32 D_010219C8;
extern s32 D_01021AC8;
extern s32 D_010308D0;
extern s32 D_010367A8;
extern s32 D_80057B50[][8];
extern Gfx *D_800B81E8;
extern s32 D_800BEEA8[][8];
void func_80005300(s32 arg0);
s32 func_80013440(s32 arg0);
s32 func_80016638(void);
s32 func_8003BFF4(Mtx *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_8003C09C(Mtx *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_8003C2F0(Mtx *arg0, f32 arg1, f32 arg2, f32 arg3);

void func_80013748(s32 arg0, s32 arg1) {
    s32 i;
    s32 j;
    s32 color;
    Gfx *gfx;

    switch (func_80016638()) {
    case 0:
        func_8003C2F0(&((MtxBuf *)arg1)->unk_1A40[((Obj *)arg0)->unk_00], ((Obj *)arg0)->unk_10, ((Obj *)arg0)->unk_12, ((Obj *)arg0)->unk_14);
        func_8003C09C(&((MtxBuf *)arg1)->unk_0140[((Obj *)arg0)->unk_00], ((Obj *)arg0)->unk_18, ((Obj *)arg0)->unk_18, ((Obj *)arg0)->unk_18);
        func_8003BFF4(&((MtxBuf *)arg1)->unk_3340[((Obj *)arg0)->unk_00], ((Obj *)arg0)->unk_28, ((Obj *)arg0)->unk_2C, ((Obj *)arg0)->unk_30);
        gfx = D_800B81E8++;
        gfx->w0 = 0x1020040;
        gfx->w1 = (s32)&((MtxBuf *)arg1)->unk_1A40[((Obj *)arg0)->unk_00];
        gfx = D_800B81E8++;
        gfx->w0 = 0x1000040;
        gfx->w1 = (s32)&((MtxBuf *)arg1)->unk_0140[((Obj *)arg0)->unk_00];
        gfx = D_800B81E8++;
        gfx->w0 = 0x1000040;
        gfx->w1 = (s32)&((MtxBuf *)arg1)->unk_3340[((Obj *)arg0)->unk_00];
        gfx = D_800B81E8++;
        gfx->w0 = 0x6000000;
        gfx->w1 = (s32)&D_01021AC8;
        for (i = 0; i < 3; i++) {
            color = func_80013440((s32)&D_80057BB0[i]);
            gfx = D_800B81E8++;
            gfx->w0 = 0xBC00000A;
            gfx->w1 = color;
            gfx = D_800B81E8++;
            gfx->w0 = 0xBC00040A;
            gfx->w1 = color;
            gfx = D_800B81E8++;
            gfx->w0 = 0xBC00400A;
            gfx->w1 = color;
            gfx = D_800B81E8++;
            gfx->w0 = 0xBC00440A;
            gfx->w1 = color;
            gfx = D_800B81E8++;
            gfx->w0 = 0xBC00600A;
            gfx->w1 = color;
            gfx = D_800B81E8++;
            gfx->w0 = 0xBC00640A;
            gfx->w1 = color;
            gfx = D_800B81E8++;
            gfx->w0 = 0xBC00800A;
            gfx->w1 = color;
            gfx = D_800B81E8++;
            gfx->w0 = 0xBC00840A;
            gfx->w1 = color;
            gfx = D_800B81E8++;
            gfx->w0 = 0x6000000;
            gfx->w1 = D_80057BB0[i].unk_00;
        }
        func_80005300(1);
        func_80005300(3);
        func_80005300(4);
        func_80005300(5);
        gfx = D_800B81E8++;
        gfx->w0 = 0xE7000000;
        gfx->w1 = 0;
        gfx = D_800B81E8++;
        gfx->w0 = 0x6000000;
        gfx->w1 = (s32)&D_010219C8;
        gfx = D_800B81E8++;
        gfx->w0 = 0xB7000000;
        gfx->w1 = 0x22200;
        gfx = D_800B81E8++;
        gfx->w0 = 0xFD100000;
        gfx->w1 = (s32)&D_010367A8;
        gfx = D_800B81E8++;
        gfx->w0 = 0xF5100000;
        gfx->w1 = 0x7094250;
        gfx = D_800B81E8++;
        gfx->w0 = 0xE6000000;
        gfx->w1 = 0;
        gfx = D_800B81E8++;
        gfx->w0 = 0xF3000000;
        gfx->w1 = 0x73FF100;
        gfx = D_800B81E8++;
        gfx->w0 = 0xE7000000;
        gfx->w1 = 0;
        gfx = D_800B81E8++;
        gfx->w0 = 0xF5101000;
        gfx->w1 = 0x94250;
        gfx = D_800B81E8++;
        gfx->w0 = 0xF2000000;
        gfx->w1 = 0x7C07C;
        gfx = D_800B81E8++;
        gfx->w0 = 0xE7000000;
        gfx->w1 = 0;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 8; j++) {
                if (D_800BEEA8[i][j] == (s32)&D_010367A8) {
                    gfx = D_800B81E8++;
                    gfx->w0 = 0x6000000;
                    gfx->w1 = D_80057B50[i][j];
                }
            }
        }
        i = 0;
        while (i < 3) {
            for (j = 0; j < 8; j++) {
                if (D_800BEEA8[i][j] != (s32)&D_010367A8) {
                    gfx = D_800B81E8++;
                    gfx->w0 = 0xFD100000;
                    gfx->w1 = D_800BEEA8[i][j];
                    gfx = D_800B81E8++;
                    gfx->w0 = 0xF5100000;
                    gfx->w1 = 0x7094250;
                    gfx = D_800B81E8++;
                    gfx->w0 = 0xE6000000;
                    gfx->w1 = 0;
                    gfx = D_800B81E8++;
                    gfx->w0 = 0xF3000000;
                    gfx->w1 = 0x73FF100;
                    gfx = D_800B81E8++;
                    gfx->w0 = 0xE7000000;
                    gfx->w1 = 0;
                    gfx = D_800B81E8++;
                    gfx->w0 = 0xF5101000;
                    gfx->w1 = 0x94250;
                    gfx = D_800B81E8++;
                    gfx->w0 = 0xF2000000;
                    gfx->w1 = 0x7C07C;
                    gfx = D_800B81E8++;
                    gfx->w0 = 0xE7000000;
                    gfx->w1 = 0;
                    gfx = D_800B81E8++;
                    gfx->w0 = 0x6000000;
                    gfx->w1 = D_80057B50[i][j];
                }
            }
            i++;
        }
        gfx = D_800B81E8++;
        gfx->w0 = 0x6000000;
        gfx->w1 = (s32)&D_010308D0;
    }
}
