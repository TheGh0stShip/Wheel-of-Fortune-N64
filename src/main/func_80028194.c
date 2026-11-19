typedef unsigned char u8;
typedef signed int s32;
typedef unsigned int u32;

typedef struct {
    /* 0x00 */ u32 w0;
    /* 0x04 */ u32 w1;
} Gfx;

typedef struct {
    /* 0x00 */ u8 unk_00[0x28];
} Sprite;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x24];
} Entry;

extern Entry D_8005A9B8[];
extern s32 D_01021970;
extern s32 D_8005A8C8[];
extern s32 D_8005A930[];
extern Sprite D_8005A998[];
extern Sprite D_8005B710[];
extern Sprite D_8005BE00[];
extern Gfx *D_800B81E8;
extern u8 D_800B966A[];
void func_8002741C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_800278A8(s32 arg0, s32 arg1);

void func_80028194(s32 arg0, s32 arg1) {
    s32 pad0[2];
    s32 i;
    s32 pad1;
    Gfx *gfx;

    gfx = D_800B81E8++;
    gfx->w0 = 0xE7000000;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0x6000000;
    gfx->w1 = (u32)&D_01021970;
    gfx = D_800B81E8++;
    gfx->w0 = 0xBA001402;
    gfx->w1 = 0x200000;
    i = 0;
    while (i < 26) {
        if (D_800B966A[i] == ' ') {
            D_8005A9B8[i].unk_00 = D_8005A8C8[i];
        } else {
            D_8005A9B8[i].unk_00 = D_8005A930[i];
        }
        func_8002741C((s32)&D_8005A998[i], 1, -13, 0);
        i++;
    }
    i = 0;
    while (i < 22) {
        func_800278A8((s32)&D_8005B710[i], 1);
        i++;
    }
    i = 0;
    while (i < 10) {
        func_800278A8((s32)&D_8005BE00[i], 1);
        i++;
    }
}
