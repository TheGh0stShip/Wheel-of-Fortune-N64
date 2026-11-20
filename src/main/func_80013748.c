#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x14];
} Layer;

extern Layer D_80057BB0[];
extern Gfx *D_800B81E8;

void func_80013748(s32 arg0, s32 arg1) {
    s32 i;
    s32 j;
    s32 color;
    Gfx *gfx;

    switch (func_80016638()) {
    case 0:
        guTranslate(&((frame_t *)arg1)->translate[((obj_t *)arg0)->index], ((obj_t *)arg0)->x, ((obj_t *)arg0)->y, ((obj_t *)arg0)->z);
        guScale(&((frame_t *)arg1)->scale[((obj_t *)arg0)->index], ((obj_t *)arg0)->scale, ((obj_t *)arg0)->scale, ((obj_t *)arg0)->scale);
        guRotateRPY(&((frame_t *)arg1)->rotate[((obj_t *)arg0)->index], ((obj_t *)arg0)->unk_28, ((obj_t *)arg0)->unk_2C, ((obj_t *)arg0)->unk_30);
        gfx = D_800B81E8++;
        gfx->words.w0 = 0x1020040;
        gfx->words.w1 = (s32)&((frame_t *)arg1)->translate[((obj_t *)arg0)->index];
        gfx = D_800B81E8++;
        gfx->words.w0 = 0x1000040;
        gfx->words.w1 = (s32)&((frame_t *)arg1)->scale[((obj_t *)arg0)->index];
        gfx = D_800B81E8++;
        gfx->words.w0 = 0x1000040;
        gfx->words.w1 = (s32)&((frame_t *)arg1)->rotate[((obj_t *)arg0)->index];
        gfx = D_800B81E8++;
        gfx->words.w0 = 0x6000000;
        gfx->words.w1 = (s32)&D_01021AC8;
        for (i = 0; i < 3; i++) {
            color = func_80013440((s32)&D_80057BB0[i]);
            gfx = D_800B81E8++;
            gfx->words.w0 = 0xBC00000A;
            gfx->words.w1 = color;
            gfx = D_800B81E8++;
            gfx->words.w0 = 0xBC00040A;
            gfx->words.w1 = color;
            gfx = D_800B81E8++;
            gfx->words.w0 = 0xBC00400A;
            gfx->words.w1 = color;
            gfx = D_800B81E8++;
            gfx->words.w0 = 0xBC00440A;
            gfx->words.w1 = color;
            gfx = D_800B81E8++;
            gfx->words.w0 = 0xBC00600A;
            gfx->words.w1 = color;
            gfx = D_800B81E8++;
            gfx->words.w0 = 0xBC00640A;
            gfx->words.w1 = color;
            gfx = D_800B81E8++;
            gfx->words.w0 = 0xBC00800A;
            gfx->words.w1 = color;
            gfx = D_800B81E8++;
            gfx->words.w0 = 0xBC00840A;
            gfx->words.w1 = color;
            gfx = D_800B81E8++;
            gfx->words.w0 = 0x6000000;
            gfx->words.w1 = D_80057BB0[i].unk_00;
        }
        func_80005300(1);
        func_80005300(3);
        func_80005300(4);
        func_80005300(5);
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xE7000000;
        gfx->words.w1 = 0;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0x6000000;
        gfx->words.w1 = (s32)&D_010219C8;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xB7000000;
        gfx->words.w1 = 0x22200;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xFD100000;
        gfx->words.w1 = (s32)&D_010367A8;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xF5100000;
        gfx->words.w1 = 0x7094250;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xE6000000;
        gfx->words.w1 = 0;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xF3000000;
        gfx->words.w1 = 0x73FF100;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xE7000000;
        gfx->words.w1 = 0;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xF5101000;
        gfx->words.w1 = 0x94250;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xF2000000;
        gfx->words.w1 = 0x7C07C;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xE7000000;
        gfx->words.w1 = 0;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 8; j++) {
                if (D_800BEEA8[i][j] == (s32)&D_010367A8) {
                    gfx = D_800B81E8++;
                    gfx->words.w0 = 0x6000000;
                    gfx->words.w1 = D_80057B50[i][j];
                }
            }
        }
        i = 0;
        while (i < 3) {
            for (j = 0; j < 8; j++) {
                if (D_800BEEA8[i][j] != (s32)&D_010367A8) {
                    gfx = D_800B81E8++;
                    gfx->words.w0 = 0xFD100000;
                    gfx->words.w1 = D_800BEEA8[i][j];
                    gfx = D_800B81E8++;
                    gfx->words.w0 = 0xF5100000;
                    gfx->words.w1 = 0x7094250;
                    gfx = D_800B81E8++;
                    gfx->words.w0 = 0xE6000000;
                    gfx->words.w1 = 0;
                    gfx = D_800B81E8++;
                    gfx->words.w0 = 0xF3000000;
                    gfx->words.w1 = 0x73FF100;
                    gfx = D_800B81E8++;
                    gfx->words.w0 = 0xE7000000;
                    gfx->words.w1 = 0;
                    gfx = D_800B81E8++;
                    gfx->words.w0 = 0xF5101000;
                    gfx->words.w1 = 0x94250;
                    gfx = D_800B81E8++;
                    gfx->words.w0 = 0xF2000000;
                    gfx->words.w1 = 0x7C07C;
                    gfx = D_800B81E8++;
                    gfx->words.w0 = 0xE7000000;
                    gfx->words.w1 = 0;
                    gfx = D_800B81E8++;
                    gfx->words.w0 = 0x6000000;
                    gfx->words.w1 = D_80057B50[i][j];
                }
            }
            i++;
        }
        gfx = D_800B81E8++;
        gfx->words.w0 = 0x6000000;
        gfx->words.w1 = (s32)&D_010308D0;
    }
}
