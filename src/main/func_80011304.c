#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x18];
} Entry;

extern Entry D_800B9D14[];
extern Entry D_800B9E64[];
extern Entry D_800B9FEC[];
extern Entry D_800BA174[];

void func_80011304(s32 arg0, s32 arg1, s32 arg2) {
    switch (arg0) {
    case 0:
        D_800B9D14[arg1].unk_00 = arg2;
        return;
    case 1:
        D_800B9E64[arg1].unk_00 = arg2;
        return;
    case 2:
        D_800B9FEC[arg1].unk_00 = arg2;
        return;
    case 3:
        D_800BA174[arg1].unk_00 = arg2;
        return;
    }
}
