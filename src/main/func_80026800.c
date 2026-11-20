#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x1C];
} EntryA;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08[0x20];
} EntryB;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
} Vec;

typedef struct {
    /* 0x00 */ u8 unk_00[0x14];
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ u8 unk_1C[0xF8];
} Player;

extern EntryA D_800584E0[];
extern EntryB D_80058B48[];
extern Vec D_8005A474[];
extern Player D_800B9990[];

void func_80026800(void) {
    s32 i;
    s32 j;
    s32 clashes;
    s32 obj;

    obj = func_8000A56C((s32)func_80025150, 0x5000000);
    func_80027218(obj, 0, (s32)func_80022218, 0x5000000);
    func_800258BC();
    for (i = 0; i < 3; i++) {
        if (D_800B9990[i].unk_14 == 4) {
            do {
                clashes = 0;
                for (j = 0; j < 3; j++) {
                    if (i != j) {
                        if (D_800B9990[i].unk_18 == D_800B9990[j].unk_18) {
                            clashes++;
                        }
                    }
                }
                if (clashes != 0) {
                    D_800B9990[i].unk_18++;
                    if (D_800B9990[i].unk_18 >= 6) {
                        D_800B9990[i].unk_18 = 0;
                    }
                }
            } while (clashes > 0);
        }
    }
    i = 0;
    while (i < 3) {
        func_800323C4(D_800B9990[i].unk_18, i, D_8005A474[i].unk_00, D_8005A474[i].unk_04, D_8005A474[i].unk_08);
        switch (D_800584E0[i].unk_00) {
        case 0:
            D_80058B48[i * 3 + 2].unk_00 = (s32)&D_01158068;
            D_80058B48[i * 3 + 2].unk_04 = (s32)&D_01158068;
            break;
        case 1:
            D_80058B48[i * 3 + 2].unk_00 = (s32)&D_01158868;
            D_80058B48[i * 3 + 2].unk_04 = (s32)&D_01158868;
            break;
        case 2:
            D_80058B48[i * 3 + 2].unk_00 = (s32)&D_01159068;
            D_80058B48[i * 3 + 2].unk_04 = (s32)&D_01159068;
            break;
        case 3:
            D_80058B48[i * 3 + 2].unk_00 = (s32)&D_01159868;
            D_80058B48[i * 3 + 2].unk_04 = (s32)&D_01159868;
            break;
        case 4:
            D_80058B48[i * 3 + 2].unk_00 = (s32)&D_01157868;
            D_80058B48[i * 3 + 2].unk_04 = (s32)&D_01157868;
            break;
        }
        i++;
    }
}
