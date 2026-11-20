#include "wof.h"

void func_8002FEB0(obj_t *obj, frame_t *frame) {
    if (obj->unk_44 == 0) {
        return;
    }
    switch (func_80016638()) {
    case 0:
        gSPLightColor(D_800B81E8++, LIGHT_3, 0xCCCCCCCC);
        gSPLightColor(D_800B81E8++, LIGHT_4, 0xCCCCCCCC);
        gSPTexture(D_800B81E8++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
        gDPPipeSync(D_800B81E8++);
        gDPSetRenderMode(D_800B81E8++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
        gDPSetCombineMode(D_800B81E8++, G_CC_MODULATERGBDECALA, G_CC_MODULATERGBDECALA);
        gDPLoadTextureBlock(D_800B81E8++, obj->unk_44, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 64, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, 6, G_TX_NOLOD, G_TX_NOLOD);
        gDPPipeSync(D_800B81E8++);
        gSPDisplayList(D_800B81E8++, obj->unk_48);
        gDPLoadTextureBlock(D_800B81E8++, obj->unk_44 + 0x1000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 64, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, 6, G_TX_NOLOD, G_TX_NOLOD);
        gSPDisplayList(D_800B81E8++, obj->unk_4C);
        gDPPipeSync(D_800B81E8++);
        func_80005300(3);
        func_80005300(4);
        gDPSetRenderMode(D_800B81E8++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    }
}
