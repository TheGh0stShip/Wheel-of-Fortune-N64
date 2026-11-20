#include "wof.h"

void func_8002FEB0(obj_t *obj, frame_t *frame) {
    if (obj->unk_44 == 0) {
        return;
    }
    switch (func_80016638()) {
    case 0:
        gSPLightColor(glistp++, LIGHT_3, 0xCCCCCCCC);
        gSPLightColor(glistp++, LIGHT_4, 0xCCCCCCCC);
        gSPTexture(glistp++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
        gDPPipeSync(glistp++);
        gDPSetRenderMode(glistp++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
        gDPSetCombineMode(glistp++, G_CC_MODULATERGBDECALA, G_CC_MODULATERGBDECALA);
        gDPLoadTextureBlock(glistp++, obj->unk_44, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 64, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, 6, G_TX_NOLOD, G_TX_NOLOD);
        gDPPipeSync(glistp++);
        gSPDisplayList(glistp++, obj->unk_48);
        gDPLoadTextureBlock(glistp++, obj->unk_44 + 0x1000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 64, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            5, 6, G_TX_NOLOD, G_TX_NOLOD);
        gSPDisplayList(glistp++, obj->unk_4C);
        gDPPipeSync(glistp++);
        SetLightColor(3);
        SetLightColor(4);
        gDPSetRenderMode(glistp++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    }
}
