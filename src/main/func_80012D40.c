#include "wof.h"

void func_80012D40(s32 arg0, s32 arg1) {
    Gfx *gfx;

    switch (func_800166C0()) {
    case 0:
        guTranslate((s32)&((frame_t *)arg1)->translate[((obj_t *)arg0)->index], ((obj_t *)arg0)->x, ((obj_t *)arg0)->y, ((obj_t *)arg0)->z);
        guScale((s32)&((frame_t *)arg1)->scale[((obj_t *)arg0)->index], ((obj_t *)arg0)->scale, ((obj_t *)arg0)->scale, ((obj_t *)arg0)->scale);
        guRotateRPY((s32)&((frame_t *)arg1)->rotate[((obj_t *)arg0)->index], ((obj_t *)arg0)->unk_28, ((obj_t *)arg0)->unk_2C, ((obj_t *)arg0)->unk_30);
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
        gfx->words.w1 = (s32)D_010219C8;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0x6000000;
        gfx->words.w1 = ((obj_t *)arg0)->unk_48;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0x6000000;
        gfx->words.w1 = (s32)&D_01093D50;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xFD100000;
        gfx->words.w1 = (s32)D_010A2B88;
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
        gfx->words.w0 = 0xB7000000;
        gfx->words.w1 = 0x22200;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xE7000000;
        gfx->words.w1 = 0;
        func_80012838(D_800B9D08, 12, 1);
        func_80012838(D_800B9E58, 14, 1);
        func_80012838(D_800B9FE0, 14, 1);
        func_80012838(D_800BA168, 12, 1);
        if (D_800BCD54 != 6) {
            gfx = D_800B81E8++;
            gfx->words.w0 = 0x6000000;
            gfx->words.w1 = (s32)&D_01021A20;
            func_80012838(D_800B9D08, 12, 0);
            func_80012838(D_800B9E58, 14, 0);
            func_80012838(D_800B9FE0, 14, 0);
            func_80012838(D_800BA168, 12, 0);
        }
        func_80005300(2);
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xE7000000;
        gfx->words.w1 = 0;
    }
}
