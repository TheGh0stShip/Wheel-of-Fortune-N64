// wof_graphics.c -- the graphics: the colours of the scene's lights, segment 1 and the framebuffers,
// loading a screen's data, the frame's graphics task and the scissor
//
// SetLightColor ends off an 8-byte boundary with InitGraphics right after, which happens only inside an
// object; a 4-byte gap ends the text after ResetScissor. guess: the boundary before SetLightColor (see
// wof_controller.c) and the joins after InitGraphics, LoadSceneData and createGfxTask, where nothing in
// the image decides and the project's ruling takes the join.

#include "wof.h"

// The RCS run at 0x800004F0 opens this object's read-only data: it is the #ident line of the system
// header the object included, and zeros to an 8-byte boundary follow it before SetLightColor's jump
// table, which needs that boundary itself. With the boundary after ResetMotors (guess: see
// wof_controller.c), no other object lies between ReadControllers's read-only data and this one's to
// hold the run.
#ident "$Revision: 1.17 $"

/*
=====================
SetLightColor

GSPLightColor on one of the six lights.
=====================
*/
void SetLightColor(s32 light) {
    switch (light) {
    case 1:
        gSPLightColor(glistp++, LIGHT_1, 0x505050FF);
        return;
    case 2:
        gSPLightColor(glistp++, LIGHT_2, 0x8C8C8CFF);
        return;
    case 3:
        gSPLightColor(glistp++, LIGHT_3, 0x8C8C8CFF);
        return;
    case 4:
        gSPLightColor(glistp++, LIGHT_4, 0x8C8C8CFF);
        return;
    case 5:
        gSPLightColor(glistp++, LIGHT_5, 0x8C8C8CFF);
        return;
    case 6:
        gSPLightColor(glistp++, LIGHT_6, 0x141414FF);
        return;
    }
}

/*
=====================
InitGraphics

Loads segment 1 from the cartridge and gives each gfxInfo its framebuffer.
=====================
*/
void InitGraphics(void) {
    s32 size;

    size = staticSize;
    camX = camY = camZ = camRoll = camPitch = camHeading = 0.0f;
    staticSegment = AllocMem(size);
    ReadRom(staticRom, staticSegment, size);
    gfxInfo[0].msg.type = OS_SC_DONE_MSG;
    gfxInfo[0].framebuffer = framebuffer0;
    gfxInfo[1].msg.type = OS_SC_DONE_MSG;
    gfxInfo[1].framebuffer = framebuffer1;
    osViSetSpecialFeatures(64);
}

/*
=====================
LoadSceneData

Waits for the graphics, saves the memory stack and reads a block from the cartridge; each screen
starts with it.
=====================
*/
void LoadSceneData(void) {
    s32 size;

    size = sceneDataSize;
    while (pendingGfx != 0 && retraceCount < 100) {
    }
    PushMemStack();
    sceneData = AllocMem(size);
    ReadRom(sceneDataRom, sceneData, size);
}

// guess: the lights of every scene are this object's. They lie between the audio manager's data and
// firstframe with no fill on either side, so they are the data of this object, of one of the objects
// between the audio manager and createGfxTask, or of an object of their own; their content is the
// graphics'.
Lights7 sceneLights = {
    { { { 0, 0, 0 }, 0, { 0, 0, 0 }, 0 } },
    {
        { { { 80, 80, 80 }, 0, { 80, 80, 80 }, 0, { 0, 100, 0 }, 0 } },
        { { { 140, 140, 140 }, 0, { 140, 140, 140 }, 0, { 0, 0, 100 }, 0 } },
        { { { 140, 140, 140 }, 0, { 140, 140, 140 }, 0, { 0, 0, -100 }, 0 } },
        { { { 140, 140, 140 }, 0, { 140, 140, 140 }, 0, { -100, 0, 0 }, 0 } },
        { { { 140, 140, 140 }, 0, { 140, 140, 140 }, 0, { 100, 0, 0 }, 0 } },
        { { { 10, 10, 10 }, 0, { 10, 10, 10 }, 0, { 0, -100, 0 }, 0 } },
        { { { 0, 0, 0 }, 0, { 0, 0, 0 }, 0, { 100, 0, 0 }, 0 } }
    }
};
s32 firstframe = 1;

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
    gSPDisplayList(glistp++, setup_rspstate);
    if (firstframe != 0) {
        gSPDisplayList(glistp++, rdpstateinit_dl);
        firstframe = 0;
    }
    gSPDisplayList(glistp++, setup_rdpstate);
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
        FatalError("GFX Error: GLIST OVERFLOW\n");
    }
    t = &info->task;
    t->list.t.data_ptr = (u64 *)frame->glist;
    t->list.t.data_size = (s32)(glistp - frame->glist) * sizeof(Gfx);
    t->list.t.type = M_GFXTASK;
    t->list.t.flags = 0x0;
    t->list.t.ucode_boot = (u64 *)rspbootTextStart;
    t->list.t.ucode_boot_size = (s32)rspbootTextEnd - (s32)rspbootTextStart;
    t->list.t.ucode = (u64 *)gfxUcodeText;
    t->list.t.ucode_data = (u64 *)gfxUcodeData;
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

/*
=====================
ResetScissor

Sets the scissor back to the whole screen between the two DrawObjs passes.
=====================
*/
void ResetScissor(frame_t *frame) {
    s32 unused;  /* NOTE: unused in the original */

    gDPPipeSync(glistp++);
    gDPSetScissor(glistp++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
    gDPPipeSync(glistp++);
    gDPPipeSync(glistp++);
}
