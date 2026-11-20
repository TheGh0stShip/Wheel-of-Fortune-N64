#include "wof.h"

struct n64dk_r12 { s32 w[3]; };

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 row;
    /* 0x08 */ s32 col;
    /* 0x0C */ u8 unk_0C[0x8];
    /* 0x14 */ u8 *text;
} Cursor;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ Cursor *unk_30;
} Obj;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x18];
} Slot;

extern Slot D_800B9D20[];
extern Slot D_800B9E70[];
extern Slot D_800B9FF8[];
extern Slot D_800BA180[];
extern u8 D_800B9601[][21];
s32 func_80002CE0(s32 arg0);
s32 func_800099B0(s32 arg0, s32 arg1);
void func_8000A850(s32 arg0);
s32 func_8000ACE8(s32 arg0);
void func_80032AD4(s32 arg0);

struct n64dk_r12 func_80010D3C(s32 arg1) {
    struct n64dk_r12 result;
    s32 pad0[2];
    s32 row;
    s32 foundRow;
    s32 foundCol;
    s32 pad1;
    u8 *p;
    u8 c;
    s32 event;

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            result.w[1] = 1;
            result.w[0] = 0;
            return result;
            break;
        case 34:
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        case 49:
            func_8000A850(6);
            result.w[1] = 0;
            result.w[0] = 0;
            return result;
        }
    }
    c = *((Obj *)arg1)->unk_30->text;
    if (c == 0) {
        func_80032AD4(0);
        result.w[1] = 2;
        result.w[0] = 49;
        return result;
    }
    row = ((Obj *)arg1)->unk_30->row;
    while (row < 4) {
        p = &D_800B9601[row][((Obj *)arg1)->unk_30->col];
        while (p != 0) {
            p = (u8 *)func_800099B0((s32)p, c);
            if (p != 0) {
                p++;
                ((Obj *)arg1)->unk_30->row = row;
                ((Obj *)arg1)->unk_30->col = (s32)p - (s32)D_800B9601 - row * 21;
                foundRow = ((Obj *)arg1)->unk_30->row;
                foundCol = ((Obj *)arg1)->unk_30->col - 1;
                switch (foundRow) {
                case 0:
                    D_800B9D20[foundCol].unk_00 = 0x1111AAFF;
                    break;
                case 1:
                    D_800B9E70[foundCol].unk_00 = 0x1111AAFF;
                    break;
                case 2:
                    D_800B9FF8[foundCol].unk_00 = 0x1111AAFF;
                    break;
                case 3:
                    D_800BA180[foundCol].unk_00 = 0x1111AAFF;
                    break;
                }
                func_80002CE0(2);
                result.w[1] = 1;
                result.w[0] = 15;
                return result;
            }
        }
        ((Obj *)arg1)->unk_30->col = 0;
        row++;
    }
    ((Obj *)arg1)->unk_30->text++;
    ((Obj *)arg1)->unk_30->col = 0;
    ((Obj *)arg1)->unk_30->row = 0;
    return result;
}
