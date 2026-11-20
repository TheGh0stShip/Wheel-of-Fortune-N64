#include "wof.h"
#include "mpeg/proto.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0xC];
    /* 0x0C */ s32 unk_0C;
} Sub;

typedef struct {
    /* 0x000 */ u8 unk_000[0x8];
    /* 0x008 */ s32 unk_008;
    /* 0x00C */ s32 unk_00C;
    /* 0x010 */ u8 unk_010;
    /* 0x011 */ u8 unk_011;
    /* 0x012 */ u8 unk_012[0x1E2];
    /* 0x1F4 */ s32 unk_1F4;
    /* 0x1F8 */ u8 unk_1F8[0x50];
    /* 0x248 */ s32 unk_248;
    /* 0x24C */ u8 unk_24C[0x14];
    /* 0x260 */ Sub *unk_260;
} Ctx;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0xC];
    /* 0x10 */ s32 unk_10;
} Req;

void func_8009CAD8(s32 arg0, s32 arg1) {
    register s32 usec;
    register s32 sec;
    s32 pad0;
    s32 sp14;
    s32 sp18[2];
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;

    if (arg1 != 0) {
        sp20 = ((Req *)arg1)->unk_10;
    }
    ((Ctx *)arg0)->unk_248++;
    if (D_80086D30 != 0) {
        if (D_80086D38 != -1 && ((Ctx *)arg0)->unk_248 > D_80086D38) {
            ((Ctx *)arg0)->unk_1F4 = 1;
            if (D_80086D18 != 0) {
                func_800A2D38(arg0);
            }
            return;
        }
        if (((Ctx *)arg0)->unk_248 < D_80086D34) {
            return;
        }
    }
    switch (D_80086D10) {
    case 0:
        break;
    default:
        func_800A4F74((s32)&D_800FD2A4, 0);
        usec = D_800FD2A0 - D_800FD2A8;
        sec = D_800FD29C - D_800FD2A4;
        if (usec < 0) {
            usec = usec + 1000000;
            sec = sec - 1;
        }
        D_800FD2A0 = D_800FD2A8 + D_800FD298;
        if (D_800FD2A0 > 999999) {
            D_800FD2A0 = D_800FD2A0 - 1000000;
            D_800FD29C = D_800FD2A4 + 1;
        } else {
            D_800FD29C = D_800FD2A4;
        }
        break;
    case -1:
        switch (D_80086D2C) {
        case -1:
            D_80086D10 = D_80086CD0[((Ctx *)arg0)->unk_011];
            func_800A4F74((s32)&D_800FD29C, 0);
            D_800FD298 = 1000000 / D_80086D10;
            break;
        case 0:
            D_80086D10 = 0;
            break;
        default:
            D_80086D10 = D_80086D2C;
            func_800A4F74((s32)&D_800FD29C, 0);
            D_800FD298 = 1000000 / D_80086D10;
            break;
        }
        break;
    }
    if (arg1 == 0) {
        return;
    }
    if (D_80086D28 == 0) {
        if (((Req *)arg1)->unk_00 == 0) {
            sp24 = 16;
            sp28 = ((Ctx *)arg0)->unk_00C * sp24;
            sp2C = ((Ctx *)arg0)->unk_008 * sp24;
            sp14 = func_800A2B08(sp20, (s32)&sp18);
            ((Req *)arg1)->unk_00 = 0;
        }
        func_80021090(((Ctx *)arg0)->unk_260->unk_0C);
    }
}
