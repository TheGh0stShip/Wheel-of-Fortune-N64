#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ s32 unk_40;
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ s32 unk_48;
    /* 0x4C */ s32 unk_4C;
    /* 0x50 */ s32 unk_50;
    /* 0x54 */ s32 unk_54;
} Task;

typedef struct {
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ u8 unk_16[0x12];
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
} Camera;

typedef struct {
    /* 0x00000 */ u8 unk_00000[0x1E478];
    /* 0x1E478 */ s32 unk_1E478;
} Frame;

extern s32 D_80000520;
extern Gfx *D_800B81E8;

void func_800057A8(s32 arg0) {
    s32 sp10;
    Task *task;
    Camera *cam;
    Gfx *gfx;

    cam = (Camera *)func_8000B5DC(0x3000000, 0xFF000000);
    if (cam != 0) {
        D_800BEE2C = cam->unk_10;
        D_800BEE30 = cam->unk_12;
        D_800BEE34 = cam->unk_14;
        D_800BEE3C = cam->unk_28;
        D_800BEE40 = cam->unk_2C;
        D_800BEE44 = cam->unk_30;
    }
    sp10 = arg0 + 88;
    D_800B81E8 = (Gfx *)(arg0 + 0x4D18);
    gfx = D_800B81E8++;
    gfx->w0 = 0xBC000006;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0xBC000406;
    gfx->w1 = func_8003FF78(D_800BCA08);
    gfx = D_800B81E8++;
    gfx->w0 = 0xBC000806;
    gfx->w1 = func_8003FF78(sp10);
    gfx = D_800B81E8++;
    gfx->w0 = 0x6000000;
    gfx->w1 = (s32)&D_01021948;
    if (D_8004B830 != 0) {
        gfx = D_800B81E8++;
        gfx->w0 = 0x6000000;
        gfx->w1 = (s32)&D_010217E0;
        D_8004B830 = 0;
    }
    gfx = D_800B81E8++;
    gfx->w0 = 0x6000000;
    gfx->w1 = (s32)&D_010218C8;
    gfx = D_800B81E8++;
    gfx->w0 = 0xFE000000;
    gfx->w1 = func_8003FF78((s32)&D_8038F800);
    gfx = D_800B81E8++;
    gfx->w0 = 0xE7000000;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0xBA001402;
    gfx->w1 = 0x300000;
    gfx = D_800B81E8++;
    gfx->w0 = 0xFF10013F;
    gfx->w1 = func_8003FF78((s32)&D_8038F800);
    gfx = D_800B81E8++;
    gfx->w0 = 0xF7000000;
    gfx->w1 = 0xFFFCFFFC;
    gfx = D_800B81E8++;
    gfx->w0 = 0xF64FC3BC;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0xE7000000;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0xFF10013F;
    gfx->w1 = func_8003FF78(((Frame *)arg0)->unk_1E478);
    gfx = D_800B81E8++;
    gfx->w0 = 0xF7000000;
    gfx->w1 = 0x10001;
    gfx = D_800B81E8++;
    gfx->w0 = 0xF64FC3BC;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0xE7000000;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0xBA001402;
    gfx->w1 = 0;
    switch (D_800BCD54) {
    case 1:
    case 5:
    case 7:
    case 8:
        gfx = D_800B81E8++;
        gfx->w0 = 0xED000000;
        gfx->w1 = 0x5003C0;
        break;
    case 4:
        gfx = D_800B81E8++;
        gfx->w0 = 0xED000000;
        gfx->w1 = 0x5002BC;
        break;
    default:
        gfx = D_800B81E8++;
        gfx->w0 = 0xED000000;
        gfx->w1 = 0x5002AC;
    }
    gfx = D_800B81E8++;
    gfx->w0 = 0xB900031D;
    gfx->w1 = 0x552078;
    func_8000B468(sp10);
    func_80005FD0(sp10);
    func_8000B528(sp10);
    gfx = D_800B81E8++;
    gfx->w0 = 0xE9000000;
    gfx->w1 = 0;
    gfx = D_800B81E8++;
    gfx->w0 = 0xB8000000;
    gfx->w1 = 0;
    func_800453B8(arg0 + 88, (s32)D_800B81E8 - (arg0 + 88));
    if (D_800B81E8 - (Gfx *)(sp10 + 0x4CC0) >= 3048) {
        func_80009F38(&D_80000520);
    }
    task = (Task *)arg0;
    task->unk_40 = sp10 + 0x4CC0;
    task->unk_44 = (u32)(D_800B81E8 - (Gfx *)(sp10 + 0x4CC0)) * 8;
    task->unk_10 = 1;
    task->unk_14 = 0;
    task->unk_18 = (s32)&D_800349B8;
    task->unk_1C = (s32)&D_80034A88 - (s32)&D_800349B8;
    task->unk_20 = (s32)&D_80034A88;
    task->unk_28 = (s32)&D_80082BC8;
    task->unk_2C = 2048;
    task->unk_30 = (s32)&D_800B3CC0;
    task->unk_34 = 1024;
    task->unk_38 = 0;
    task->unk_3C = 0;
    task->unk_48 = (s32)&D_800B61E0;
    task->unk_4C = 2304;
    task->unk_00 = 0;
    task->unk_08 = 99;
    task->unk_50 = (s32)&D_800B9688;
    task->unk_54 = arg0 + 0x1E458;
    task->unk_0C = ((Frame *)arg0)->unk_1E478;
    func_8003E4B8(D_800BEEA0, task, 1);
    D_800AB5E8++;
}
