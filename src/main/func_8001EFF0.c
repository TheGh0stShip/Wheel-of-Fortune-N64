#include "wof.h"

void func_8001EFF0(obj_t *obj, frame_t *frame) {
    gDPPipeSync(glistp++);
    gDPSetRenderMode(glistp++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gSPDisplayList(glistp++, D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    gDPLoadTextureBlock(glistp++, obj->image, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                        6, 6, G_TX_NOLOD, G_TX_NOLOD);
    gDPPipeSync(glistp++);
    gSPTextureRectangle(glistp++, (obj->x + 3) << 2, (obj->y + 3) << 2,
                        (obj->x + 66) << 2, (obj->y + 34) << 2,
                        G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
    gDPPipeSync(glistp++);
    gDPLoadTextureBlock(glistp++, obj->image + 0x1000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 48, 32, 0,
                        G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP,
                        6, 6, G_TX_NOLOD, G_TX_NOLOD);
    gDPPipeSync(glistp++);
    gSPTextureRectangle(glistp++, (obj->x + 67) << 2, (obj->y + 3) << 2,
                        (obj->x + 114) << 2, (obj->y + 34) << 2,
                        G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
    gDPPipeSync(glistp++);
    gDPLoadTextureBlock(glistp++, obj->image + 0x1C00, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                        6, 6, G_TX_NOLOD, G_TX_NOLOD);
    gDPPipeSync(glistp++);
    gSPTextureRectangle(glistp++, (obj->x + 3) << 2, (obj->y + 35) << 2,
                        (obj->x + 66) << 2, (obj->y + 66) << 2,
                        G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
    gDPPipeSync(glistp++);
    gDPLoadTextureBlock(glistp++, obj->image + 0x2C00, G_IM_FMT_RGBA, G_IM_SIZ_16b, 48, 32, 0,
                        G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP,
                        6, 6, G_TX_NOLOD, G_TX_NOLOD);
    gDPPipeSync(glistp++);
    gSPTextureRectangle(glistp++, (obj->x + 67) << 2, (obj->y + 35) << 2,
                        (obj->x + 114) << 2, (obj->y + 66) << 2,
                        G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
    gDPPipeSync(glistp++);
    gDPLoadTextureBlock(glistp++, obj->image + 0x3800, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 16, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                        6, 6, G_TX_NOLOD, G_TX_NOLOD);
    gDPPipeSync(glistp++);
    gSPTextureRectangle(glistp++, (obj->x + 3) << 2, (obj->y + 67) << 2,
                        (obj->x + 66) << 2, (obj->y + 82) << 2,
                        G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
    gDPPipeSync(glistp++);
    gDPLoadTextureBlock(glistp++, obj->image + 0x4000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 48, 16, 0,
                        G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP,
                        6, 6, G_TX_NOLOD, G_TX_NOLOD);
    gDPPipeSync(glistp++);
    gSPTextureRectangle(glistp++, (obj->x + 67) << 2, (obj->y + 67) << 2,
                        (obj->x + 114) << 2, (obj->y + 82) << 2,
                        G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
    gDPPipeSync(glistp++);
    gDPSetCycleType(glistp++, G_CYC_1CYCLE);
    gDPSetRenderMode(glistp++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
}
