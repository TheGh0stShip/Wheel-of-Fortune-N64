typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    u8 unk_00[0x50];
} Slot;

extern s32 D_80000854;
extern Slot D_800B6BF8[];
extern s32 D_800BA5E0[];
void func_80009F38(s32 *arg0);

s32 func_8000A31C(s32 arg0) {
    s32 i;

    for (i = 0; i < 70; i++) {
        if (D_800BA5E0[i] == 0) {
            D_800BA5E0[i] = arg0;
            return (s32)&D_800B6BF8[i];
        }
    }
    func_80009F38(&D_80000854);
    return 0;
}
