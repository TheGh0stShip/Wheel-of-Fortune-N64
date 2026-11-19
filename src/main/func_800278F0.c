typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ s32 w0;
    /* 0x04 */ s32 w1;
} Gfx;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x24];
} Sprite;

typedef struct {
    /* 0x000 */ s32 unk_00;
    /* 0x004 */ s32 unk_04;
    /* 0x008 */ u8 unk_08[0x10C];
} Player;

extern Sprite D_8005A9B8[];
extern Player D_800B9998[];
extern s32 D_01021970;
extern Sprite D_8005A4B8[][2];
extern Sprite D_8005A5A8[];
extern Sprite D_8005A7B0[];
extern Sprite D_8005A828[];
extern s32 D_8005A8C8[];
extern s32 D_8005A930[];
extern Sprite D_8005A998[];
extern Sprite D_8005ADD0[][7];
extern Sprite D_8005B360[];
extern Sprite D_8005B4C8[];
extern Sprite D_8005B630[];
extern Sprite D_8005B710[];
extern s32 D_800B40C4;
extern s32 D_800B619C;
extern Gfx *D_800B81E8;
extern u8 D_800B966A[];
extern s32 D_800BA2BC;
extern s32 D_800BCA28;
void func_800278A8(s32 arg0, s32 arg1);

void func_800278F0(s32 arg0, s32 arg1) {
    s32 pad0[2];
    s32 i;
    s32 j;
    Gfx *gfx;

    gfx = D_800B81E8++;
    gfx->w0 = 0xE7000000;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0x6000000;
    gfx->w1 = (s32)&D_01021970;
    gfx = D_800B81E8++;
    gfx->w0 = 0xBA001402;
    gfx->w1 = 0x200000;
    i = 2;
    while (i >= 0) {
        j = 0;
        while (j < 2) {
            func_800278A8((s32)&D_8005A4B8[i][j], 1);
            j++;
        }
        i--;
    }
    i = 0;
    while (i < 3) {
        j = 0;
        while (j < 7) {
            func_800278A8((s32)&D_8005ADD0[i][j], 1);
            j++;
        }
        i++;
    }
    if (D_800B619C == 2 && (D_800B40C4 != 0 || D_800BCA28 == 22)) {
        switch (D_800BA2BC) {
        case 3:
        case 18:
            j = 0;
            while (j < 3) {
                func_800278A8((s32)&D_8005B630[j], 1);
                j++;
            }
            j = 0;
            while (j < 9) {
                func_800278A8((s32)&D_8005B4C8[j], 1);
                func_800278A8((s32)&D_8005B360[j], 1);
                j++;
            }
        }
    }
    i = 0;
    while (i < 26) {
        if (D_800B966A[i] == ' ') {
            D_8005A9B8[i].unk_00 = D_8005A8C8[i];
        } else {
            D_8005A9B8[i].unk_00 = D_8005A930[i];
        }
        func_800278A8((s32)&D_8005A998[i], 1);
        i++;
    }
    i = 0;
    while (i < 4) {
        func_800278A8((s32)&D_8005A828[i], 1);
        i++;
    }
    i = 0;
    while (i < 3) {
        if (D_800B9998[i].unk_00 != 0) {
            func_800278A8((s32)&D_8005A7B0[i], 1);
        }
        if (D_800B9998[i].unk_04 != 0) {
            func_800278A8((s32)&D_8005A5A8[i], 1);
        }
        i++;
    }
    i = 0;
    while (i < 22) {
        func_800278A8((s32)&D_8005B710[i], 1);
        i++;
    }
}
