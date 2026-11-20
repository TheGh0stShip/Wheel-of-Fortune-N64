#include "wof.h"

typedef struct {
    /* 0x0000 */ u8 unk_0000[0x140];
    /* 0x0140 */ Mtx unk_0140[200];
    /* 0x3340 */ Mtx unk_3340[1];
} MtxBuf;

extern Gfx *D_800B81E8;

void func_80012500(s32 arg0, s32 arg1) {
    Gfx *gfx;

    switch (func_80016638()) {
    case 0:
        guScale(&((MtxBuf *)arg1)->unk_0140[((obj_t *)arg0)->index], ((obj_t *)arg0)->scale, ((obj_t *)arg0)->scale, ((obj_t *)arg0)->scale);
        guRotateRPY(&((MtxBuf *)arg1)->unk_3340[((obj_t *)arg0)->index], ((obj_t *)arg0)->unk_28, ((obj_t *)arg0)->unk_2C, ((obj_t *)arg0)->unk_30);
        gfx = D_800B81E8++;
        gfx->words.w0 = 0x1020040;
        gfx->words.w1 = ((obj_t *)arg0)->unk_3C;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0x1000040;
        gfx->words.w1 = (s32)&((MtxBuf *)arg1)->unk_0140[((obj_t *)arg0)->index];
        gfx = D_800B81E8++;
        gfx->words.w0 = 0x1000040;
        gfx->words.w1 = (s32)&((MtxBuf *)arg1)->unk_3340[((obj_t *)arg0)->index];
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xBC00000A;
        gfx->words.w1 = 0xFFFEFFFF;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xBC00040A;
        gfx->words.w1 = 0xFFFEFFFF;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0x6000000;
        gfx->words.w1 = (s32)&D_010219C8;
        gfx = D_800B81E8++;
        gfx->words.w0 = 0x6000000;
        gfx->words.w1 = ((obj_t *)arg0)->unk_48;
        func_80005300(1);
    }
}
