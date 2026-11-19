typedef unsigned char u8;
typedef signed int s32;

typedef struct Node {
    /* 0x00 */ u8 unk_00[0x8];
    /* 0x08 */ s32 flags;
    /* 0x0C */ u8 unk_0C[0x34];
    /* 0x40 */ struct Node *next;
} Node;

s32 func_8000AA24(s32 arg0, s32 arg1, s32 arg2) {
    while (((Node *)arg0)->next != 0) {
        arg0 = (s32)((Node *)arg0)->next;
        if ((((Node *)arg0)->flags & arg2) == arg1) {
            return arg0;
        }
    }
    return 0;
}
