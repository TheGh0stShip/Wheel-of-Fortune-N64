#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8 unk_0C[0xC];
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
} Slot;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} Pair;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x110];
} Player;

typedef struct {
    /* 0x00 */ u8 unk_00[0x44];
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ u8 unk_48[0x4];
    /* 0x4C */ s32 unk_4C;
} Obj;

extern Pair D_8005C3A0[];
extern Slot D_8005C7F0[];
extern Player D_800B99A8[];
extern s32 D_80001A0C;
extern s32 func_8002FEB0;
extern Slot D_8005C3B8[][2];
extern s32 D_800B61A8;
extern s32 D_800B96AC;
extern s32 D_800B9988;
extern s32 D_800BCA60;
extern s32 D_800BCD54;
void func_80009F38(s32 *arg0);
s32 func_8000B924(s32 arg0);
s32 func_8000B978(void);
s32 func_80015848(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80021B4C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80032AD4(s32 arg0);
void func_80032B10(void);

void func_80032BF0(void) {
    Obj *obj;
    s32 pad0;
    Slot *slots;
    s32 i;
    s32 j;
    s32 size;
    s32 sp28;

    sp28 = 0x2000000;
    if (D_800BCD54 == 3) {
        for (i = 0; i < 3; i++) {
            D_800B99A8[i].unk_00 = i;
        }
    }
    D_800BCA60 = func_8000B978();
    for (i = 0; i < 3; i++) {
        if (D_800B99A8[i].unk_00 >= 6) {
            func_80009F38(&D_80001A0C);
        }
        slots = D_8005C3B8[D_800B99A8[i].unk_00];
        for (j = 0; j < 2; j++) {
            if (slots[j].unk_08 > 0) {
                size = slots[j].unk_00 * slots[j].unk_04 * 2;
                slots[j].unk_18 = func_8000B924(size * slots[j].unk_08);
                func_80021B4C(slots[j].unk_1C, slots[j].unk_08, slots[j].unk_18, slots[j].unk_20);
            } else {
                slots[j].unk_18 = 0;
            }
        }
    }
    i = 0;
    while (i < 6) {
        size = D_8005C7F0[i].unk_00 * D_8005C7F0[i].unk_04 * 2;
        D_8005C7F0[i].unk_18 = func_8000B924(size * D_8005C7F0[i].unk_08);
        func_80021B4C(D_8005C7F0[i].unk_1C, D_8005C7F0[i].unk_08, D_8005C7F0[i].unk_18, D_8005C7F0[i].unk_20);
        i++;
    }
    D_800B61A8 = 1;
    D_800B9988 = 0;
    for (i = 0; i < 3; i++) {
        obj = (Obj *)func_80015848(0, D_8005C3A0[i].unk_00, (s32)&func_8002FEB0, i | 0xA020000);
        obj->unk_4C = D_8005C3A0[i].unk_04;
        obj->unk_44 = 0;
    }
    func_80032B10();
    func_80032AD4(4);
    D_800B96AC = 0;
}
