#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x24];
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ u8 unk_2C[0x24];
} Entry;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x24];
} Slot;

extern Entry D_8005A4C8[];
extern Slot D_8005ADE0[][7];
void func_800278F0(void);
void func_8002CBF4(void);
extern s32 D_800B9974;
extern s32 D_800BCA14;
s32 func_8000A56C(s32 arg0, s32 arg1);
s32 func_80027218(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_8002EDC0(void);

void func_8002EC60(void) {
    s32 sp10;
    s32 i;
    s32 j;

    for (i = 0; i < 3; i++) {
        D_8005A4C8[i].unk_00 = 0;
        D_8005A4C8[i].unk_28 = 0;
        for (j = 0; j < 7; j++) {
            D_8005ADE0[i][j].unk_00 = 0;
        }
    }
    func_8002EDC0();
    sp10 = func_8000A56C((s32)func_8002CBF4, 0x5000000);
    func_80027218(sp10, 0, (s32)func_800278F0, 0x5000000);
    D_800BCA14 = 0;
    D_800B9974 = 0;
}
