#include "wof.h"

/*
=====================
DrawMenuContestant

The draw function of a contestant in the menus.
=====================
*/
void DrawMenuContestant(obj_t *obj, frame_t *frame) {
    if (obj->image == 0) {
        return;
    }
    guTranslate(&frame->translate[obj->index], (f32)obj->x, (f32)obj->y, (f32)obj->z);
    guScale(&frame->scale[obj->index], obj->scale, obj->scale, obj->scale);
    guRotateRPY(&frame->rotate[obj->index], obj->roll, obj->pitch, obj->heading);
    gSPMatrix(glistp++, &frame->translate[obj->index], G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->scale[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix(glistp++, &frame->rotate[obj->index], G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPDisplayList(glistp++, D_010219C8);
    gSPTexture(glistp++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPPipeSync(glistp++);
    gDPSetRenderMode(glistp++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
    gDPSetCombineMode(glistp++, G_CC_MODULATERGBDECALA, G_CC_MODULATERGBDECALA);
    gDPLoadTextureBlock(glistp++, obj->image, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 64, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                        5, 6, G_TX_NOLOD, G_TX_NOLOD);
    gDPPipeSync(glistp++);
    gSPDisplayList(glistp++, obj->dl);
    gDPLoadTextureBlock(glistp++, obj->image + 0x1000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 64, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                        5, 6, G_TX_NOLOD, G_TX_NOLOD);
    gSPDisplayList(glistp++, obj->secondDl);
    gDPPipeSync(glistp++);
    gDPSetRenderMode(glistp++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
}
