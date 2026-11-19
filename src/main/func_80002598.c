typedef unsigned char u8;
typedef signed int s32;

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

extern s32 D_800A507C[];
extern Obj *D_800B3998;
extern s32 D_800B81D8;
extern s32 D_800BED90[];
s32 func_8003B378(s32);
s32 func_8003B3A8(s32, s32);
s32 func_8003B944(s32, s32);
s32 func_80041188(s32, s32);

void func_80002598(s32 arg0, s32 arg1) {
    s32 sp10;

    sp10 = D_800B81D8 + ((Table *)D_800B81D8)->entries[arg0].offset;
    func_8003B944(D_800A507C[arg1], sp10);
    func_80041188(D_800BED90[arg1], D_800A507C[arg1]);
    func_8003B3A8(D_800BED90[arg1], D_800B3998->unk_04);
    func_8003B378(D_800BED90[arg1]);
}
