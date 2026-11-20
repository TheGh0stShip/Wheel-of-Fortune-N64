#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0xC];
    /* 0x0C */ s32 unk_0C;
} Inner;

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ Inner *unk_04;
} Header;

extern s32 D_8004B718;
extern s32 D_8004B71C;
extern s32 D_8006DD04;
extern s32 D_8006DD08;
extern s32 D_8006DD0C;
extern s32 D_800A5084;
extern s32 D_800A5088;
extern s32 *D_800A508C;
extern s32 D_800A5090;
extern s16 *D_800A509C;
extern s32 D_800B3990;
extern s32 D_800B9960;
extern s32 D_800BED90;

void func_80002348(void) {
    s32 size;
    s32 pad0;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 pad1;
    s32 sp28;
    s32 *sp2C;
    s32 sp30;
    u8 sp34;
    s32 *sp38;
    s32 pad2;
    s32 sp40;
    s32 sp44;
    u8 sp48;
    u8 sp49;
    s32 *sp4C;
    s32 sp50;
    s32 sp54;
    s32 sp58;
    s32 pad3;
    s32 sp60;
    s32 sp64;
    s32 sp68;
    s32 pad4;
    s32 heap;
    s32 i;

    heap = func_8000B924(0x30D40);
    func_8003A5F8(&D_800B9960, heap, 0x30D40);
    sp18 = 32;
    sp1C = 32;
    sp20 = 48;
    sp28 = 0;
    sp34 = 6;
    sp30 = 0;
    sp2C = &D_800B9960;
    sp38 = &D_8004B71C;
    sp60 = 0x5622;
    sp64 = 1;
    sp68 = 0x1000;
    func_800032A8((s32)&sp18, 12, (s32)&sp60);
    sp40 = 32;
    sp44 = 48;
    sp48 = 32;
    sp4C = &D_800B9960;
    sp50 = 0;
    sp54 = 0;
    sp58 = 0;
    sp49 = 7;
    D_800BED90 = func_8000B924(136);
    func_800422B8(D_800BED90, &sp40);
    D_800A5084 = 32;
    D_800A5088 = 64;
    D_800A508C = &D_800B9960;
    func_8004AABC(D_8004B718, &D_800A5084);
    size = D_8006DD08 - D_8006DD04;
    D_800B3990 = func_8000B924(size);
    func_80006828(D_8006DD04, D_800B3990, size);
    func_8003EA1C(D_800B3990, D_8006DD0C);
    D_800A5090 = ((Header *)D_800B3990)->unk_04->unk_0C;
    D_800A509C = (s16 *)func_8000B924(64);
    i = 0;
    while (i < 32) {
        D_800A509C[i] = -1;
        i++;
    }
}
