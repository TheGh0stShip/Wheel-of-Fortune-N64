typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 width;
    /* 0x0C */ s32 height;
} Image;

typedef struct {
    /* 0x00 */ s32 w0;
    /* 0x04 */ s32 w1;
} Gfx;

extern Gfx *D_800B81E8;
s32 func_8002731C(s32 arg0, s32 arg1);

void func_8002741C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    register s32 reg_s0;
    register s32 reg_s1;
    s32 texture;
    Gfx *gfx;
    Gfx *gfx2;

    texture = func_8002731C(arg0, arg1);
    if (texture != 0) {
        gfx = D_800B81E8++;
        gfx->w0 = 0xFD100000;
        gfx->w1 = texture;
        gfx = D_800B81E8++;
        gfx->w0 = 0xF5100000;
        gfx->w1 = 0x7058160;
        gfx = D_800B81E8++;
        gfx->w0 = 0xE6000000;
        gfx->w1 = 0;
        gfx = D_800B81E8++;
        gfx->w0 = 0xF3000000;
        {
            register Gfx *reg_v0;
            reg_v0 = gfx;
            if (((Image *)arg0)->width / 4 > 0) {
                reg_s0 = ((Image *)arg0)->width / 4;
                reg_s0 = reg_s0 + 2047;
            } else {
                reg_s0 = 2048;
            }
            reg_s1 = ((Image *)arg0)->width * ((Image *)arg0)->height;
            reg_s1 = reg_s1 - 1;
            if (reg_s1 >= 2048) {
                reg_s1 = 2047;
            }
            reg_s1 = reg_s1 & 4095;
            reg_s1 = reg_s1 << 12;
            reg_s1 = reg_s1 | 0x7000000;
            reg_v0->w1 = (((Image *)arg0)->width / 4 > 0) ? (reg_s1 | ((reg_s0 / (((Image *)arg0)->width / 4)) & 4095)) : (reg_s1 | (reg_s0 & 4095));
        }
        gfx = D_800B81E8++;
        gfx->w0 = 0xE7000000;
        gfx->w1 = 0;
        gfx = D_800B81E8++;
        gfx->w0 = ((((((Image *)arg0)->width * 2 + 7) >> 3) & 511) << 9) | 0xF5100000;
        gfx->w1 = 0x58160;
        gfx = D_800B81E8++;
        gfx->w0 = 0xF2000000;
        gfx->w1 = ((((((Image *)arg0)->width - 1) << 2) & 4095) << 12) | (((((Image *)arg0)->height - 1) << 2) & 4095);
        gfx = D_800B81E8++;
        gfx->w0 = 0xE7000000;
        gfx->w1 = 0;
        gfx = D_800B81E8++;
        gfx->w0 = ((((((Image *)arg0)->x + arg2 + ((Image *)arg0)->width - 1) << 2) & 4095) << 12) | 0xE4000000 | (((((Image *)arg0)->y + arg3 + ((Image *)arg0)->height - 1) << 2) & 4095);
        gfx->w1 = ((((((Image *)arg0)->x + arg2) << 2) & 4095) << 12) | (((((Image *)arg0)->y + arg3) << 2) & 4095);
        gfx2 = D_800B81E8++;
        gfx2->w0 = 0xB4000000;
        gfx2->w1 = 0;
        gfx2 = D_800B81E8++;
        gfx2->w0 = 0xB3000000;
        gfx2->w1 = 0x10000400;
        gfx2 = D_800B81E8++;
        gfx2->w0 = 0xE7000000;
        gfx2->w1 = 0;
    }
}
