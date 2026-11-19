typedef unsigned char u8;
typedef signed short s16;
typedef signed int s32;
typedef float f32;

typedef struct {
    u8 unk_00[0x40];
} Mtx;

typedef struct {
    /* 0x0000 */ u8 unk_0000[0x140];
    /* 0x0140 */ Mtx unk_0140[100];
    /* 0x1A40 */ Mtx unk_1A40[100];
    /* 0x3340 */ Mtx unk_3340[1];
} Pool;

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
} Model;

typedef struct {
    /* 0x00 */ s32 w0;
    /* 0x04 */ s32 w1;
} Gfx;

extern s32 D_01021A70;
extern s32 D_80057988[];
extern Gfx *D_800B81E8;
void func_80005300(s32 arg0);
s32 func_8003BFF4(Mtx *, s32, s32, s32);
s32 func_8003C09C(Mtx *, s32, s32, s32);
s32 func_8003C2F0(Mtx *, f32, f32, f32);

void func_80014208(s32 arg0, s32 arg1) {
    s32 i;
    Gfx *gfx;

    func_8003C2F0(&((Pool *)arg1)->unk_1A40[((Model *)arg0)->index], ((Model *)arg0)->unk_10, ((Model *)arg0)->unk_12, ((Model *)arg0)->unk_14);
    func_8003C09C(&((Pool *)arg1)->unk_0140[((Model *)arg0)->index], ((Model *)arg0)->unk_18, ((Model *)arg0)->unk_18, ((Model *)arg0)->unk_18);
    func_8003BFF4(&((Pool *)arg1)->unk_3340[((Model *)arg0)->index], ((Model *)arg0)->unk_28, ((Model *)arg0)->unk_2C, ((Model *)arg0)->unk_30);
    gfx = D_800B81E8++;
    gfx->w0 = 0x1020040;
    gfx->w1 = (s32)&((Pool *)arg1)->unk_1A40[((Model *)arg0)->index];
    gfx = D_800B81E8++;
    gfx->w0 = 0x1000040;
    gfx->w1 = (s32)&((Pool *)arg1)->unk_0140[((Model *)arg0)->index];
    gfx = D_800B81E8++;
    gfx->w0 = 0x1000040;
    gfx->w1 = (s32)&((Pool *)arg1)->unk_3340[((Model *)arg0)->index];
    gfx = D_800B81E8++;
    gfx->w0 = 0x6000000;
    gfx->w1 = ((Model *)arg0)->unk_48;
    gfx = D_800B81E8++;
    gfx->w0 = 0x6000000;
    gfx->w1 = (s32)&D_01021A70;
    for (i = 0; i < 26; i++) {
        gfx = D_800B81E8++;
        gfx->w0 = 0x6000000;
        gfx->w1 = D_80057988[i];
    }
    func_80005300(1);
}
