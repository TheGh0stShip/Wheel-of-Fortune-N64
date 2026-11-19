typedef signed short s16;
typedef signed int s32;

typedef struct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
} Obj;

extern Obj *D_800B81D8;

s32 func_8000326C(void) {
    return D_800B81D8->unk_02;
}
