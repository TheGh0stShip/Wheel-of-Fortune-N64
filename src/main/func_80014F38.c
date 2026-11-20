#include "wof.h"

typedef struct {
    /* 0x00 */ u32 w0;
    /* 0x04 */ u32 w1;
} Gfx;

typedef struct {
    /* 0x00 */ u8 unk_00[0x40];
} Mtx;

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
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ u8 unk_1C[0xC];
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ u8 unk_34[0x14];
    /* 0x48 */ s32 unk_48;
} Obj;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} DlPair;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x1C];
} Entry;

extern Entry D_800B39D4[];
extern s32 D_010219C8;
extern s32 D_010FA038;
extern DlPair *D_80057F08[];
extern s32 D_800B619C;
extern Gfx *D_800B81E8;
void func_80005300(s32 arg0);
s32 func_80016638(void);
s32 func_8003BFF4(Mtx *, s32, s32, s32);
s32 func_8003C09C(Mtx *, s32, s32, s32);
s32 func_8003C2F0(Mtx *, f32, f32, f32);

void func_80014F38(s32 arg0, s32 arg1) {
    s32 i;
    Gfx *gfx;

    switch (func_80016638()) {
    case 0:
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
        gfx = D_800B81E8++;
        gfx->w0 = 0x6000000;
        gfx->w1 = (u32)&D_010FA038;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00000A;
        gfx->w1 = 0xC8C8C8FF;
        gfx = D_800B81E8++;
        gfx->w0 = 0xBC00040A;
        gfx->w1 = 0xC8C8C8FF;
        i = 0;
        while (i < 24) {
            if (D_800B39D4[i].unk_00 != 0 && D_80057F08[D_800B619C][i].unk_04 != 0) {
                gfx = D_800B81E8++;
                gfx->w0 = 0x6000000;
                gfx->w1 = D_80057F08[D_800B619C][i].unk_04;
            } else {
                gfx = D_800B81E8++;
                gfx->w0 = 0x6000000;
                gfx->w1 = D_80057F08[D_800B619C][i].unk_00;
            }
            i++;
        }
        func_80005300(1);
        gfx = D_800B81E8++;
        gfx->w0 = 0x6000000;
        gfx->w1 = ((Obj *)arg0)->unk_48;
        func_80005300(1);
    }
}
