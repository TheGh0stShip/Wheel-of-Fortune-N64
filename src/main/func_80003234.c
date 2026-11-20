#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0xE];
    /* 0x0E */ s16 unk_0E;
} Obj;

extern Obj *D_800A5090;

s32 func_80003234(void) {
    return D_800A5090->unk_0E;
}
