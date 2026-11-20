#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x24];
} Entry;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08[0x10C];
} Player;

extern Entry D_8005ADF0[][7];
extern Player D_800B9990[];
extern s32 D_01010FA0;
extern s32 D_8005ACE8[];
s32 func_80009A74(s32 arg0);
void func_80009AE0(s32 arg0, s32 arg1);
void func_80013500(s32 arg0);

void func_80029974(s32 arg0) {
    s32 i;
    s32 j;
    s32 len;
    s32 value;
    s32 pad0[2];
    u8 buf[24];

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 7; j++) {
            D_8005ADF0[i][j].unk_00 = 0;
        }
        if (arg0 != 0) {
            value = D_800B9990[i].unk_04;
        } else {
            value = D_800B9990[i].unk_00;
        }
        func_80009AE0((s32)buf, value);
        len = func_80009A74((s32)buf);
        if (len >= 7) {
            len = 6;
        }
        D_8005ADF0[i][6 - len].unk_00 = (s32)&D_01010FA0;
        for (j = 0; j < len; j++) {
            D_8005ADF0[i][j + 7 - len].unk_00 = D_8005ACE8[buf[j]];
        }
    }
    func_80013500(arg0);
}
