#include "wof.h"

typedef struct {
    /* 0x00 */ u8 unk_00[0x5];
    /* 0x05 */ s8 type;
} SoundInfo;

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ SoundInfo *info;
} Sound;

typedef struct {
    /* 0x00 */ u8 unk_00[0xE];
    /* 0x0E */ s16 count;
    /* 0x10 */ Sound *sounds[1];
} SoundBank;

extern f32 D_8000046C;
extern f32 D_80000470;
extern f32 D_80000474;
extern f32 D_80000478;
extern f32 D_8000047C;
extern f32 D_80000480;
extern f32 D_80000484;
extern f32 D_80000488;
extern f32 D_8000048C;
extern f32 D_80000490;
extern f32 D_80000494;
extern s32 D_8004B718;
extern SoundBank *D_800A5090;
extern Sound *D_800A5098;
extern s16 *D_800A509C;
s32 func_80002700(void);
s32 func_800396B8(s32, f32);
s32 func_80049EB8(s32 arg0, Sound *arg1);
s32 func_80049FA8(s32 arg0, s32 arg1);
s32 func_80049FC8(s32 arg0);

s32 func_80002CE0(s32 arg0) {
    f32 sp10;
    s32 pad0;
    s32 slot;

    if (arg0 >= D_800A5090->count) {
        arg0 = 0;
    }
    D_800A5098 = D_800A5090->sounds[arg0];
    slot = func_80002700();
    if (slot == -1) {
        return -1;
    }
    D_800A509C[slot] = func_80049EB8(D_8004B718, D_800A5098);
    if (D_800A509C[slot] == -1) {
        return -1;
    }
    func_80049FA8(D_8004B718, D_800A509C[slot]);
    switch (D_800A5098->info->type) {
    case 0:
        sp10 = D_8000046C;
        break;
    case 1:
        sp10 = D_80000470;
        break;
    case 2:
        sp10 = D_80000474;
        break;
    case 3:
        sp10 = D_80000478;
        break;
    case 4:
        sp10 = D_8000047C;
        break;
    case 5:
        sp10 = D_80000480;
        break;
    case 6:
        sp10 = D_80000484;
        break;
    case 7:
        sp10 = D_80000488;
        break;
    case 8:
        sp10 = D_8000048C;
        break;
    case 9:
        sp10 = D_80000490;
        break;
    case 10:
        sp10 = D_80000494;
        break;
    }
    func_800396B8(D_8004B718, sp10);
    func_80049FC8(D_8004B718);
    return slot;
}
