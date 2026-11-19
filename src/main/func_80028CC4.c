typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x24];
} Entry;

extern Entry D_8005B730[];

void func_80028CC4(void) {
    s32 i;

    for (i = 0; i < 22; i++) {
        D_8005B730[i].unk_00 = 0;
    }
}
