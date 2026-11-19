typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;

typedef struct {
    /* 0x00 */ u8 unk_00[0x10];
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
} Obj;

typedef struct {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u8 unk_02[0x2];
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u8 unk_06[0x2];
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ u8 unk_0A[0x2];
} Entry;

extern Entry D_8005A39E[];
extern s32 D_800015D4;
extern s32 D_80058880;
extern u16 D_8005A392;
extern u16 D_8005A396;
extern u16 D_8005A39A;
void func_80009F38(s32 *arg0);
s32 func_8000B5DC(s32 arg0, s32 arg1);

void func_80023B44(void) {
    s32 i;
    Obj *obj;

    for (i = 0; i < 6; i++) {
        obj = (Obj *)func_8000B5DC(i | 0xA020000, -1);
        if (obj == 0) {
            func_80009F38(&D_800015D4);
        }
        if (i == D_80058880) {
            obj->unk_10 = D_8005A392;
            obj->unk_12 = D_8005A396;
            obj->unk_14 = D_8005A39A;
        } else {
            obj->unk_10 = D_8005A39E[i].unk_00;
            obj->unk_12 = D_8005A39E[i].unk_04;
            obj->unk_14 = D_8005A39E[i].unk_08;
        }
    }
}
