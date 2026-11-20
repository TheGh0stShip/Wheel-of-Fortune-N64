#include "wof.h"

typedef struct Node {
    /* 0x00 */ struct Node *next;
} Node;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8 unk_0C[0x4];
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ u8 unk_24[0x4];
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
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x08 */ Task task;
} Req;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s16 unk_04;
} Buf;

extern s32 D_800349B8;
extern s32 D_80034A88;
extern s32 D_80037298;
extern s32 D_8004B7B0;
extern s32 D_80083BC8;
extern s32 D_800B96B8;
extern u32 D_800B96BC;
extern u16 D_800B96BE;
extern Node *D_800BA5CC;
extern s32 D_800BCA68[];
extern s32 D_800BCC68;
extern u16 D_800BCD66;
extern s32 D_800BEEA0;

s32 func_80003944(s32 arg0, s32 arg1) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    Task *task;
    s32 count;
    Node *node;

    sp1C = 0;
    count = 0;
    node = D_800BA5CC;
    while (node != 0) {
        count++;
        node = node->next;
    }
    if (count > D_800B96B8) {
        D_800B96B8 = count;
    }
    func_80003FDC();
    sp10 = func_8003FF78(((Req *)arg0)->unk_00);
    if (arg1 != 0) {
        func_800388B8(((Buf *)arg1)->unk_00, ((Buf *)arg1)->unk_04 << 2);
    }
    sp1C = (u32)func_80038748() >> 2;
    ((Req *)arg0)->unk_04 = (D_800BCD66 - (u16)sp1C + 96) & 0xFFF0u;
    if ((u32)((Req *)arg0)->unk_04 < D_800B96BC) {
        ((Req *)arg0)->unk_04 = D_800B96BE;
    }
    sp14 = func_80039980(D_800BCA68[D_8004B7B0], &sp18, sp10, ((Req *)arg0)->unk_04);
    if (sp18 == 0) {
        return 0;
    }
    task = &((Req *)arg0)->task;
    task->unk_00 = 0;
    task->unk_50 = (s32)&D_800BCC68;
    task->unk_54 = arg0 + 0x60;
    task->unk_08 = 2;
    task->unk_40 = D_800BCA68[D_8004B7B0];
    task->unk_44 = (u32)((Gfx *)sp14 - (Gfx *)D_800BCA68[D_8004B7B0]) * 8;
    task->unk_10 = 2;
    task->unk_18 = (s32)&D_800349B8;
    task->unk_1C = (s32)&D_80034A88 - (s32)&D_800349B8;
    task->unk_14 = 2;
    task->unk_20 = (s32)&D_80037298;
    task->unk_28 = (s32)&D_80083BC8;
    task->unk_2C = 2048;
    task->unk_30 = 0;
    task->unk_34 = 0;
    task->unk_38 = 0;
    task->unk_3C = 0;
    task->unk_48 = 0;
    task->unk_4C = 0;
    func_8003E4B8(D_800BEEA0, task, 1);
    D_8004B7B0 ^= 1;
    return 1;
}
