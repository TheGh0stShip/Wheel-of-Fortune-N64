typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ s32 count;
    /* 0x1C */ s32 items[1];
} Stack;

extern s32 D_800009B4;
void func_80009F38(void *arg0);

s32 func_8000ACE8(s32 arg0) {
    if (arg0 == 0) {
        func_80009F38(&D_800009B4);
        return 0;
    }
    if (((Stack *)arg0)->count != 0) {
        ((Stack *)arg0)->count--;
        return ((Stack *)arg0)->items[((Stack *)arg0)->count];
    }
    return 0;
}
