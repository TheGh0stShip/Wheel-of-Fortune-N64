#include "wof.h"

typedef struct {
    /* 0x0000 */ u8 pad0[0x140];
    /* 0x0140 */ Mtx unk_0140[100];
    /* 0x1A40 */ Mtx unk_1A40[100];
    /* 0x3340 */ Mtx unk_3340[100];
    /* 0x4C40 */ u8 pad4C40[0x40];
    /* 0x4C80 */ Mtx unk_4C80;
} Scene;

extern Gfx *D_800B81E8;

void func_8000D400(s32 arg0, s32 arg1) {
    Gfx *gfx;

    if (D_800B3994 >= 318) {
        return;
    }
    guTranslate(&((Scene *)arg1)->unk_1A40[((obj_t *)arg0)->index], ((obj_t *)arg0)->x, ((obj_t *)arg0)->y, ((obj_t *)arg0)->z);
    guScale(&((Scene *)arg1)->unk_0140[((obj_t *)arg0)->index], ((obj_t *)arg0)->scale, ((obj_t *)arg0)->scale, ((obj_t *)arg0)->scale);
    guRotateRPY(&((Scene *)arg1)->unk_3340[((obj_t *)arg0)->index], ((obj_t *)arg0)->unk_28, ((obj_t *)arg0)->unk_2C, ((obj_t *)arg0)->unk_30);
    guRotateRPY(&((Scene *)arg1)->unk_4C80, 0, D_800B61AC, 0);
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x1020040;
    gfx->words.w1 = (s32)&((Scene *)arg1)->unk_1A40[((obj_t *)arg0)->index];
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x1000040;
    gfx->words.w1 = (s32)&((Scene *)arg1)->unk_0140[((obj_t *)arg0)->index];
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x1000040;
    gfx->words.w1 = (s32)&((Scene *)arg1)->unk_3340[((obj_t *)arg0)->index];
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x1000040;
    gfx->words.w1 = (s32)&((Scene *)arg1)->unk_4C80;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = (s32)&D_010219C8;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = ((obj_t *)arg0)->unk_48;
}
