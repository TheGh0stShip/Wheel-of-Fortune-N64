typedef unsigned char u8;
typedef signed int s32;

typedef struct Obj {
    /* 0x00 */ u8 unk_00[0x40];
    /* 0x40 */ struct Obj *next;
} Obj;

extern s32 D_800007F0;
extern Obj D_800B82A0;
void func_80009F38(s32 *arg0);

s32 func_8000A158(s32 arg0) {
    Obj *cur;
    Obj *prev;

    prev = &D_800B82A0;
    cur = prev->next;
    while (cur != 0) {
        if ((s32)cur == arg0) {
            return (s32)prev;
        }
        prev = cur;
        cur = prev->next;
    }
    func_80009F38(&D_800007F0);
    return 0;
}
