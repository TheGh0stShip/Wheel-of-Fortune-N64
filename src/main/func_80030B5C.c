#include "wof.h"

void func_80030B5C(obj_t *obj, frame_t *frame) {
    proc_t *actor;
    s16 *pixels;

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
    gSPMatrix(D_800B81E8++, &D_0113AE28, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    guTranslate(&frame->translate[obj->index], obj->x, obj->y, obj->z);
    gSPMatrix(D_800B81E8++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPTexture(D_800B81E8++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPPipeSync(D_800B81E8++);
    gDPSetRenderMode(D_800B81E8++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
    gDPSetCombineMode(D_800B81E8++, G_CC_MODULATERGBDECALA, G_CC_MODULATERGBDECALA);
    gDPLoadTextureBlock(D_800B81E8++, obj->unk_44, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                        6, 5, G_TX_NOLOD, G_TX_NOLOD);
    gDPPipeSync(D_800B81E8++);
    gSPDisplayList(D_800B81E8++, D_0113AD08);
    gDPLoadTextureBlock(D_800B81E8++, obj->unk_44 + 0x1000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                        6, 5, G_TX_NOLOD, G_TX_NOLOD);
    gSPDisplayList(D_800B81E8++, D_0113AD28);
    gDPLoadTextureBlock(D_800B81E8++, obj->unk_44 + 0x2000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                        6, 5, G_TX_NOLOD, G_TX_NOLOD);
    gSPDisplayList(D_800B81E8++, D_0113AD48);
    gDPPipeSync(D_800B81E8++);
    gDPSetRenderMode(D_800B81E8++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
}
