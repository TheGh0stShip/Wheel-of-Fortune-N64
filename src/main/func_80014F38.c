#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} DlPair;

extern DlPair *D_80057F08[];

void func_80014F38(s32 arg0, s32 arg1) {
    s32 i;
    Gfx *gfx;

    switch (func_80016638()) {
    case 0:
        guTranslate(&((frame_t *)arg1)->translate[((obj_t *)arg0)->index], ((obj_t *)arg0)->x, ((obj_t *)arg0)->y, ((obj_t *)arg0)->z);
        guScale(&((frame_t *)arg1)->scale[((obj_t *)arg0)->index], ((obj_t *)arg0)->scale, ((obj_t *)arg0)->scale, ((obj_t *)arg0)->scale);
        guRotateRPY(&((frame_t *)arg1)->rotate[((obj_t *)arg0)->index], ((obj_t *)arg0)->unk_28, ((obj_t *)arg0)->unk_2C, ((obj_t *)arg0)->unk_30);
        gfx = D_800B81E8++;
        gfx->words.w0 = 0x1020040;
        gfx->words.w1 = (u32)&((frame_t *)arg1)->translate[((obj_t *)arg0)->index];
        gfx = D_800B81E8++;
        gfx->words.w0 = 0x1000040;
        gfx->words.w1 = (u32)&((frame_t *)arg1)->scale[((obj_t *)arg0)->index];
        gfx = D_800B81E8++;
        gfx->words.w0 = 0x1000040;
        gfx->words.w1 = (u32)&((frame_t *)arg1)->rotate[((obj_t *)arg0)->index];
        gfx = D_800B81E8++;
        gfx->words.w0 = 0x6000000;
        gfx->words.w1 = (u32)&D_010219C8;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0x6000000;
        gfx->words.w1 = (u32)&D_010FA038;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xBC00000A;
        gfx->words.w1 = 0xC8C8C8FF;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xBC00040A;
        gfx->words.w1 = 0xC8C8C8FF;
        i = 0;
        while (i < 24) {
            if (D_800B39B8[i].unk_1C != 0 && D_80057F08[D_800B619C][i].unk_04 != 0) {
                gfx = D_800B81E8++;
                gfx->words.w0 = 0x6000000;
                gfx->words.w1 = D_80057F08[D_800B619C][i].unk_04;
            } else {
                gfx = D_800B81E8++;
                gfx->words.w0 = 0x6000000;
                gfx->words.w1 = D_80057F08[D_800B619C][i].unk_00;
            }
            i++;
        }
        func_80005300(1);
        gfx = D_800B81E8++;
        gfx->words.w0 = 0x6000000;
        gfx->words.w1 = ((obj_t *)arg0)->unk_48;
        func_80005300(1);
    }
}
