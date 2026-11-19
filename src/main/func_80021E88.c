typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ s32 w0;
    /* 0x04 */ s32 w1;
} Gfx;

typedef struct {
    u8 unk_00[0x28];
} Entry;

extern s32 D_01021970;
extern Entry D_80058548[];
extern Entry D_80059120[];
extern Gfx *D_800B81E8;
extern u8 D_800B96C4;
void func_800278A8(s32 arg0, s32 arg1);

void func_80021E88(s32 arg0, s32 arg1) {
    s32 pad0[2];
    s32 i;
    s32 pad1;
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
    for (i = 0; i < 118; i++) {
        func_800278A8((s32)&D_80059120[i], 1);
    }
    i = 0;
    while (i < 20) {
        if (i >= 2 && i < 6) {
            if ((D_800B96C4 >> (i - 2)) % 2 != 0) {
                func_800278A8((s32)&D_80058548[i], 1);
            }
        } else {
            func_800278A8((s32)&D_80058548[i], 1);
        }
        i++;
    }
}
