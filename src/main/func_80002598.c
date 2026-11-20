#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 offset;
} TableEntry;

typedef struct {
    TableEntry entries[1];
} Table;

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
} Obj;

extern Obj *D_800B3998;
extern s32 D_800B81D8;

void func_80002598(s32 arg0, s32 arg1) {
    s32 sp10;

    sp10 = D_800B81D8 + ((Table *)D_800B81D8)->entries[arg0].offset;
    alCSeqNew(D_800A507C[arg1], sp10);
    alCSPSetSeq(D_800BED90[arg1], D_800A507C[arg1]);
    alCSPSetBank(D_800BED90[arg1], D_800B3998->unk_04);
    alCSPPlay(D_800BED90[arg1]);
}
