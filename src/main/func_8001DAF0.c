#include "wof.h"

void func_8001DAF0(obj_t *obj, frame_t *frame) {
    gDPPipeSync(glistp++);
    gDPSetRenderMode(glistp++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetCycleType(glistp++, G_CYC_FILL);
    gDPSetFillColor(glistp++, 0x39CF39CF);
    gDPFillRectangle(glistp++, obj->x, obj->y, obj->x + 102, obj->y + 102);
    gSPDisplayList(glistp++, D_01021970);
    gDPSetCycleType(glistp++, G_CYC_COPY);
    gDPLoadTextureBlock(glistp++, obj->unk_44, G_IM_FMT_RGBA, G_IM_SIZ_16b, 48, 32, 0,
                        G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP,
                        6, 5, G_TX_NOLOD, G_TX_NOLOD);
    gDPPipeSync(glistp++);
    gSPTextureRectangle(glistp++, (obj->x + 3) << 2, (obj->y + 3) << 2,
                        (obj->x + 50) << 2, (obj->y + 34) << 2,
                        G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
    gDPPipeSync(glistp++);
    gDPLoadTextureBlock(glistp++, obj->unk_44 + 3072, G_IM_FMT_RGBA, G_IM_SIZ_16b, 48, 32, 0,
                        G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP,
                        6, 5, G_TX_NOLOD, G_TX_NOLOD);
    gDPPipeSync(glistp++);
    gSPTextureRectangle(glistp++, (obj->x + 51) << 2, (obj->y + 3) << 2,
                        (obj->x + 98) << 2, (obj->y + 34) << 2,
                        G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
    gDPPipeSync(glistp++);
    gDPLoadTextureBlock(glistp++, obj->unk_44 + 0x1800, G_IM_FMT_RGBA, G_IM_SIZ_16b, 48, 32, 0,
                        G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP,
                        6, 5, G_TX_NOLOD, G_TX_NOLOD);
    gDPPipeSync(glistp++);
    gSPTextureRectangle(glistp++, (obj->x + 3) << 2, (obj->y + 35) << 2,
                        (obj->x + 50) << 2, (obj->y + 66) << 2,
                        G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
    gDPPipeSync(glistp++);
    gDPLoadTextureBlock(glistp++, obj->unk_44 + 0x2400, G_IM_FMT_RGBA, G_IM_SIZ_16b, 48, 32, 0,
                        G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP,
                        6, 5, G_TX_NOLOD, G_TX_NOLOD);
    gDPPipeSync(glistp++);
    gSPTextureRectangle(glistp++, (obj->x + 51) << 2, (obj->y + 35) << 2,
                        (obj->x + 98) << 2, (obj->y + 66) << 2,
                        G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
    gDPPipeSync(glistp++);
    gDPLoadTextureBlock(glistp++, obj->unk_44 + 0x3000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 48, 32, 0,
                        G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP,
                        6, 5, G_TX_NOLOD, G_TX_NOLOD);
    gDPPipeSync(glistp++);
    gSPTextureRectangle(glistp++, (obj->x + 3) << 2, (obj->y + 67) << 2,
                        (obj->x + 50) << 2, (obj->y + 98) << 2,
                        G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
    gDPPipeSync(glistp++);
    gDPLoadTextureBlock(glistp++, obj->unk_44 + 0x3C00, G_IM_FMT_RGBA, G_IM_SIZ_16b, 48, 32, 0,
                        G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP,
                        6, 5, G_TX_NOLOD, G_TX_NOLOD);
    gDPPipeSync(glistp++);
    gSPTextureRectangle(glistp++, (obj->x + 51) << 2, (obj->y + 67) << 2,
                        (obj->x + 98) << 2, (obj->y + 98) << 2,
                        G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
    gDPPipeSync(glistp++);
    gDPSetCycleType(glistp++, G_CYC_1CYCLE);
    gDPSetRenderMode(glistp++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
}
