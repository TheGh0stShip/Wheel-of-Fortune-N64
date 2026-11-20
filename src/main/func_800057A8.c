#include "wof.h"

void func_800057A8(gfxInfo_t *info) {
    frame_t *frame;
    OSScTask *t;
    obj_t *cam;
    Gfx *gfx;

    cam = (obj_t *)func_8000B5DC(0x3000000, 0xFF000000);
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
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBC000006;
    gfx->words.w1 = 0;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBC000406;
    gfx->words.w1 = osVirtualToPhysical(D_800BCA08);
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBC000806;
    gfx->words.w1 = osVirtualToPhysical(frame);
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = (s32)D_01021948;
    if (D_8004B830 != 0) {
        gfx = D_800B81E8++;
        gfx->words.w0 = 0x6000000;
        gfx->words.w1 = (s32)D_010217E0;
        D_8004B830 = 0;
    }
    gfx = D_800B81E8++;
    gfx->words.w0 = 0x6000000;
    gfx->words.w1 = (s32)D_010218C8;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xFE000000;
    gfx->words.w1 = osVirtualToPhysical(D_8038F800);
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xE7000000;
    gfx->words.w1 = 0;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBA001402;
    gfx->words.w1 = 0x300000;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xFF10013F;
    gfx->words.w1 = osVirtualToPhysical(D_8038F800);
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xF7000000;
    gfx->words.w1 = 0xFFFCFFFC;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xF64FC3BC;
    gfx->words.w1 = 0;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xE7000000;
    gfx->words.w1 = 0;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xFF10013F;
    gfx->words.w1 = osVirtualToPhysical(info->framebuffer);
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xF7000000;
    gfx->words.w1 = 0x10001;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xF64FC3BC;
    gfx->words.w1 = 0;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xE7000000;
    gfx->words.w1 = 0;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xBA001402;
    gfx->words.w1 = 0;
    switch (D_800BCD54) {
    case 1:
    case 5:
    case 7:
    case 8:
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xED000000;
        gfx->words.w1 = 0x5003C0;
        break;
    case 4:
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xED000000;
        gfx->words.w1 = 0x5002BC;
        break;
    default:
        gfx = D_800B81E8++;
        gfx->words.w0 = 0xED000000;
        gfx->words.w1 = 0x5002AC;
    }
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xB900031D;
    gfx->words.w1 = 0x552078;
    func_8000B468(frame);
    func_80005FD0(frame);
    func_8000B528(frame);
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xE9000000;
    gfx->words.w1 = 0;
    gfx = D_800B81E8++;
    gfx->words.w0 = 0xB8000000;
    gfx->words.w1 = 0;
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
