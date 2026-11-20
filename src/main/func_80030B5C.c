#include "wof.h"

void func_80030B5C(obj_t *obj, frame_t *frame) {
    proc_t *actor;
    s16 *pixels;
    Gfx *gfx;

    if (obj->unk_44 == 0) {
        return;
    }
    if (D_800BCD54 == 6) {
        actor = func_8000A990(0xA000400, -1);
        if (actor != 0) {
            pixels = actor->unk_30->vannaAnim.unk_08 + actor->unk_30->vannaAnim.unk_10 * ( 64 * 96 );
            func_8003143C(pixels, actor->unk_30->vannaAnim.unk_20 * D_800B61A8);
        }
    }
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x1020040;
    gfx->words.w1 = (s32)&D_0113AE28;
    guTranslate(&frame->translate[obj->index], obj->x, obj->y, obj->z);
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x1000040;
    gfx->words.w1 = (s32)&frame->translate[obj->index];
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBB000001;
    gfx->words.w1 = -1;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xE7000000;
    gfx->words.w1 = 0;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xB900031D;
    gfx->words.w1 = 0x553078;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xFC127E24;
    gfx->words.w1 = -3079;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xFD100000;
    gfx->words.w1 = obj->unk_44;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xF5100000;
    gfx->words.w1 = 0x7094260;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xE6000000;
    gfx->words.w1 = 0;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xF3000000;
    gfx->words.w1 = 0x77FF080;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xE7000000;
    gfx->words.w1 = 0;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xF5102000;
    gfx->words.w1 = 0x94260;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xF2000000;
    gfx->words.w1 = 0xFC07C;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xE7000000;
    gfx->words.w1 = 0;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = (s32)&D_0113AD08;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xFD100000;
    gfx->words.w1 = obj->unk_44 + 0x1000;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xF5100000;
    gfx->words.w1 = 0x7094260;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xE6000000;
    gfx->words.w1 = 0;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xF3000000;
    gfx->words.w1 = 0x77FF080;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xE7000000;
    gfx->words.w1 = 0;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xF5102000;
    gfx->words.w1 = 0x94260;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xF2000000;
    gfx->words.w1 = 0xFC07C;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = (s32)&D_0113AD28;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xFD100000;
    gfx->words.w1 = obj->unk_44 + 0x2000;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xF5100000;
    gfx->words.w1 = 0x7094260;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xE6000000;
    gfx->words.w1 = 0;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xF3000000;
    gfx->words.w1 = 0x77FF080;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xE7000000;
    gfx->words.w1 = 0;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xF5102000;
    gfx->words.w1 = 0x94260;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xF2000000;
    gfx->words.w1 = 0xFC07C;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = (s32)&D_0113AD48;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xE7000000;
    gfx->words.w1 = 0;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xB900031D;
    gfx->words.w1 = 0x552078;
}
