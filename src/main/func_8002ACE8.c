typedef signed char s8;
typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ union {
        s32 w;
        u8 b[4];
    } unk_04;
    /* 0x08 */ u8 unk_08[0x4];
    /* 0x0C */ s32 unk_0C;
} State;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ State *unk_30;
} Task;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8 unk_0C[0x1C];
} Entry;

extern Entry D_8005A9AC[];
extern s8 D_800B61B5;
extern u8 D_800B966A[];
extern s32 D_800BED88;
s32 func_80002CE0(s32 arg0);

void func_8002ACE8(s32 arg0) {
    s32 i;

    D_800BED88++;
    if (((Task *)arg0)->unk_30->unk_04.w < 13) {
        return;
    }
    i = 0;
    for (;;) {
        if (i >= 13) {
            break;
        }
        if (D_800B966A[i] != 32) {
            break;
        }
        i++;
    }
    if (i == 13) {
        return;
    }
    func_80002CE0(43);
    ((Task *)arg0)->unk_30->unk_04.w = ((Task *)arg0)->unk_30->unk_04.w - 13;
    D_8005A9AC[((Task *)arg0)->unk_30->unk_04.w].unk_08 = D_8005A9AC[((Task *)arg0)->unk_30->unk_04.w].unk_00;
    D_800B61B5 = ((Task *)arg0)->unk_30->unk_04.b[3] + 65;
    ((Task *)arg0)->unk_30->unk_0C = 15;
}
