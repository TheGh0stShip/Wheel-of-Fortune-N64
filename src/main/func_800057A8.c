#include "wof.h"

void func_800057A8(gfxInfo_t *info) {
    frame_t *frame;
    OSScTask *t;
    obj_t *cam;

    cam = func_8000B5DC(0x3000000, 0xFF000000);
    if (cam != 0) {
        D_800BEE2C = cam->x;
        D_800BEE30 = cam->y;
        D_800BEE34 = cam->z;
        D_800BEE3C = cam->unk_28;
        D_800BEE40 = cam->unk_2C;
        D_800BEE44 = cam->unk_30;
    }
    frame = &info->frame;
    D_800B81E8 = info->frame.glist;
    gSPSegment(D_800B81E8++, 0, 0x0);
    gSPSegment(D_800B81E8++, 1, osVirtualToPhysical(D_800BCA08));
    gSPSegment(D_800B81E8++, 2, osVirtualToPhysical(frame));
    gSPDisplayList(D_800B81E8++, D_01021948);
    if (D_8004B830 != 0) {
        gSPDisplayList(D_800B81E8++, D_010217E0);
        D_8004B830 = 0;
    }
    gSPDisplayList(D_800B81E8++, D_010218C8);
    gDPSetDepthImage(D_800B81E8++, osVirtualToPhysical(D_8038F800));
    gDPPipeSync(D_800B81E8++);
    gDPSetCycleType(D_800B81E8++, G_CYC_FILL);
    gDPSetColorImage(D_800B81E8++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, osVirtualToPhysical(D_8038F800));
    gDPSetFillColor(D_800B81E8++, GPACK_ZDZ(G_MAXFBZ, 0) << 16 | GPACK_ZDZ(G_MAXFBZ, 0));
    gDPFillRectangle(D_800B81E8++, 0, 0, 320 - 1, 240 - 1);
    gDPPipeSync(D_800B81E8++);
    gDPSetColorImage(D_800B81E8++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320,
                     osVirtualToPhysical(info->framebuffer));
    gDPSetFillColor(D_800B81E8++, GPACK_RGBA5551(0, 0, 0, 1) << 16 | GPACK_RGBA5551(0, 0, 0, 1));
    gDPFillRectangle(D_800B81E8++, 0, 0, 320 - 1, 240 - 1);
    gDPPipeSync(D_800B81E8++);
    gDPSetCycleType(D_800B81E8++, G_CYC_1CYCLE);
    switch (D_800BCD54) {
    case 1:
    case 5:
    case 7:
    case 8:
        gDPSetScissor(D_800B81E8++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
        break;
    case 4:
        gDPSetScissor(D_800B81E8++, G_SC_NON_INTERLACE, 0, 0, 320, 175);
        break;
    default:
        gDPSetScissor(D_800B81E8++, G_SC_NON_INTERLACE, 0, 0, 320, 171);
    }
    gDPSetRenderMode(D_800B81E8++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    func_8000B468(frame);
    func_80005FD0(frame);
    func_8000B528(frame);
    gDPFullSync(D_800B81E8++);
    gSPEndDisplayList(D_800B81E8++);
    osWritebackDCache(&info->frame, (s32)D_800B81E8 - (s32)&info->frame);
    if (D_800B81E8 - frame->glist >= 3048) {
        func_80009F38("GFX Error: GLIST OVERFLOW\n");
    }
    t = &info->task;
    t->list.t.data_ptr = (u64 *)frame->glist;
    t->list.t.data_size = (s32)(D_800B81E8 - frame->glist) * sizeof(Gfx);
    t->list.t.type = M_GFXTASK;
    t->list.t.flags = 0x0;
    t->list.t.ucode_boot = (u64 *)D_800349B8;
    t->list.t.ucode_boot_size = (s32)D_80034A88 - (s32)D_800349B8;
    t->list.t.ucode = (u64 *)D_80034A88;
    t->list.t.ucode_data = (u64 *)D_80082BC8;
    t->list.t.ucode_data_size = SP_UCODE_DATA_SIZE;
    t->list.t.dram_stack = (u64 *)D_800B3CC0;
    t->list.t.dram_stack_size = SP_DRAM_STACK_SIZE8;
    t->list.t.output_buff = (u64 *)0x0;
    t->list.t.output_buff_size = (u64 *)0x0;
    t->list.t.yield_data_ptr = (u64 *)D_800B61E0;
    // OS_YIELD_DATA_SIZE as it was before F3DEX: the headers of today make it 0xC00
    t->list.t.yield_data_size = 0x900;
    t->next = 0;
    t->flags = OS_SC_NEEDS_RSP | OS_SC_NEEDS_RDP | OS_SC_LAST_TASK | OS_SC_SWAPBUFFER;
    t->msgQ = &D_800B9688;
    t->msg = (OSMesg)&info->msg;
    t->framebuffer = (void *)info->framebuffer;
    osSendMesg(D_800BEEA0, (OSMesg)t, OS_MESG_BLOCK);
    D_800AB5E8++;
}
