#include "wof.h"

typedef struct {
    /* 0x00000 */ u8 unk_00000[0xAC00];
    /* 0x0AC00 */ u8 blocks[9][0x2000];
    /* 0x1CC00 */ u8 unk_1CC00[0x187C];
} BankData;

typedef struct {
    /* 0x00000 */ s32 unk_00000;
    /* 0x00004 */ BankData data;
} Bank;

typedef struct {
    /* 0x00 */ u8 unk_00[0x44];
    /* 0x44 */ s32 unk_44;
} Target;

typedef struct {
    /* 0x00 */ Target *unk_00;
    /* 0x04 */ u8 unk_04[0xC];
    /* 0x10 */ s32 unk_10;
} Ref;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ Ref *unk_30;
} Obj;

extern Bank D_800BEF5C[];
extern u8 *D_800B998C;
extern u8 D_800BEF60[][0x1E480];

void func_800213CC(Obj *arg0) {
    s32 sp10;
    s32 pad0;
    s32 pad1[6];
    s32 pad2;
    s32 sp34;

    sp34 = 0x2000000;
    sp10 = func_8003FF78(D_800BEF5C[D_800B61A0].data.blocks[arg0->unk_30->unk_10]);
    sp10 = sp10 - func_8003FF78(D_800BEF60[D_800B61A0]);
    arg0->unk_30->unk_00->unk_44 = sp34 + sp10;
    D_800B998C = D_800BEF5C[D_800B61A0].data.blocks[arg0->unk_30->unk_10];
    if (D_800B40C4 == 0) {
        D_800B40C4 = func_8009D244();
    }
}
