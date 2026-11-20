#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x1C];
} Slot;

typedef struct {
    /* 0x000 */ s32 unk_00;
    /* 0x004 */ s32 unk_04;
    /* 0x008 */ u8 unk_08[0x10C];
} Player;

extern Slot D_800584E0[];
extern Player D_800B99A4[];
extern f32 D_80001674;
extern s32 D_80058E88;
extern s32 D_80058FE0;
extern u8 D_8005A498[][10];
extern f32 D_800B8298;
extern s32 D_800B96C0;
extern u8 D_800B96C4;
extern u8 D_800B99AC[][276]; /* D_800B99A4[i].unk_08 */
extern s32 D_800BEDD8[];

void func_80026FD4(void) {
    s32 i;
    s32 count;

    D_800B8298 = D_80001674;
    D_800B96C0 = 6;
    for (i = 0; i < 3; i++) {
        D_800584E0[i].unk_00 = 4;
        D_800B99A4[i].unk_00 = 4;
        D_800B99A4[i].unk_04 = i;
        D_800BEDD8[i] = i;
        func_80009900((s32)D_800B99AC[i], (s32)D_8005A498[i]);
    }
    count = 0;
    i = 0;
    while (i < 4) {
        if ((D_800B96C4 >> i) % 2 != 0) {
            D_800584E0[count].unk_00 = i;
            D_800B99A4[count].unk_00 = i;
            count++;
        }
        if (count >= 3) {
            break;
        }
        i++;
    }
    D_80058E88 = 1;
    D_80058FE0 = 3;
}
