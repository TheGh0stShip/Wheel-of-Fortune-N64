#include "wof.h"

void createGfxTask(gfxInfo_t *info) {
    frame_t *frame;
    OSScTask *t;
    obj_t *cam;

    cam = FindObj(0x3000000, 0xFF000000);
    if (cam != 0) {
        camX = cam->x;
        camY = cam->y;
        camZ = cam->z;
        camRoll = cam->roll;
        camPitch = cam->pitch;
        camHeading = cam->heading;
    }
    frame = &info->frame;
    glistp = info->frame.glist;
    gSPSegment(glistp++, 0, 0x0);
    gSPSegment(glistp++, 1, osVirtualToPhysical(staticSegment));
    gSPSegment(glistp++, 2, osVirtualToPhysical(frame));
    gSPDisplayList(glistp++, D_01021948);
    if (D_8004B830 != 0) {
        gSPDisplayList(glistp++, D_010217E0);
        D_8004B830 = 0;
    }
    gSPDisplayList(glistp++, D_010218C8);
    gDPSetDepthImage(glistp++, osVirtualToPhysical(zbuffer));
    gDPPipeSync(glistp++);
    gDPSetCycleType(glistp++, G_CYC_FILL);
    gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, osVirtualToPhysical(zbuffer));
    gDPSetFillColor(glistp++, GPACK_ZDZ(G_MAXFBZ, 0) << 16 | GPACK_ZDZ(G_MAXFBZ, 0));
    gDPFillRectangle(glistp++, 0, 0, 320 - 1, 240 - 1);
    gDPPipeSync(glistp++);
    gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320,
                     osVirtualToPhysical(info->framebuffer));
    gDPSetFillColor(glistp++, GPACK_RGBA5551(0, 0, 0, 1) << 16 | GPACK_RGBA5551(0, 0, 0, 1));
    gDPFillRectangle(glistp++, 0, 0, 320 - 1, 240 - 1);
    gDPPipeSync(glistp++);
    gDPSetCycleType(glistp++, G_CYC_1CYCLE);
    switch (gameMode) {
    case 1:
    case 5:
    case 7:
    case 8:
        gDPSetScissor(glistp++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
        break;
    case 4:
        gDPSetScissor(glistp++, G_SC_NON_INTERLACE, 0, 0, 320, 175);
        break;
    default:
        gDPSetScissor(glistp++, G_SC_NON_INTERLACE, 0, 0, 320, 171);
    }
    gDPSetRenderMode(glistp++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    DrawObjs(frame);
    ResetScissor(frame);
    DrawTopObjs(frame);
    gDPFullSync(glistp++);
    gSPEndDisplayList(glistp++);
    osWritebackDCache(&info->frame, (s32)glistp - (s32)&info->frame);
    if (glistp - frame->glist >= 3048) {
        func_80009F38("GFX Error: GLIST OVERFLOW\n");
    }
    t = &info->task;
    t->list.t.data_ptr = (u64 *)frame->glist;
    t->list.t.data_size = (s32)(glistp - frame->glist) * sizeof(Gfx);
    t->list.t.type = M_GFXTASK;
    t->list.t.flags = 0x0;
    t->list.t.ucode_boot = (u64 *)D_800349B8;
    t->list.t.ucode_boot_size = (s32)D_80034A88 - (s32)D_800349B8;
    t->list.t.ucode = (u64 *)D_80034A88;
    t->list.t.ucode_data = (u64 *)D_80082BC8;
    t->list.t.ucode_data_size = SP_UCODE_DATA_SIZE;
    t->list.t.dram_stack = (u64 *)dram_stack;
    t->list.t.dram_stack_size = SP_DRAM_STACK_SIZE8;
    t->list.t.output_buff = (u64 *)0x0;
    t->list.t.output_buff_size = (u64 *)0x0;
    t->list.t.yield_data_ptr = (u64 *)gfxYieldBuf;
    // OS_YIELD_DATA_SIZE as it was before F3DEX: the headers of today make it 0xC00
    t->list.t.yield_data_size = 0x900;
    t->next = 0;
    t->flags = OS_SC_NEEDS_RSP | OS_SC_NEEDS_RDP | OS_SC_LAST_TASK | OS_SC_SWAPBUFFER;
    t->msgQ = &gfxMsgQ;
    t->msg = (OSMesg)&info->msg;
    t->framebuffer = (void *)info->framebuffer;
    osSendMesg(sched_cmdQ, (OSMesg)t, OS_MESG_BLOCK);
    numGfxTasks++;
}
