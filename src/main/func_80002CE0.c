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

extern SoundBank *D_800A5090;
extern Sound *D_800A5098;

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
        sp10 = 0.18728799f;
        break;
    case 1:
        sp10 = 0.23596825f;
        break;
    case 2:
        sp10 = 0.2648662f;
        break;
    case 3:
        sp10 = 0.31497958f;
        break;
    case 4:
        sp10 = 0.35355556f;
        break;
    case 5:
        sp10 = 0.3968254f;
        break;
    case 6:
        sp10 = 0.420449f;
        break;
    case 7:
        sp10 = 0.5f;
        break;
    case 8:
        sp10 = 0.5946032f;
        break;
    case 9:
        sp10 = 0.6674195f;
        break;
    case 10:
        sp10 = 1.0f;
        break;
    }
    func_800396B8(D_8004B718, sp10);
    func_80049FC8(D_8004B718);
    return slot;
}
