#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x64];
    /* 0x64 */ s32 unk_64;
} Obj;

extern s32 D_80107480;
extern s32 D_80107484;
extern s32 D_80107488;

void func_8009CA80(s32 arg0, s32 arg1) {
    ((Obj *)arg1)->unk_64 = 16;
    D_80107480 = 0xF800;
    D_80107484 = 1984;
    D_80107488 = 62;
}
