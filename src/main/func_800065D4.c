#ifndef N64DK_M2C_PRELUDE
#define N64DK_M2C_PRELUDE
typedef signed char s8; typedef unsigned char u8; typedef signed short s16; typedef unsigned short u16;
typedef signed int s32; typedef unsigned int u32; typedef signed long long s64; typedef unsigned long long u64;
typedef float f32; typedef double f64;
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
/* unhandled instructions become calls to an unprototyped function: any argument list compiles */
extern s32 m2c_unhandled();
#define M2C_ERROR m2c_unhandled
#define M2C_TRAP_IF m2c_unhandled
#define M2C_BREAK m2c_unhandled
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
#define MULT_HI(a, b) ((s32)(((s64)(a) * (s64)(b)) >> 32))
#define MULTU_HI(a, b) ((u32)(((u64)(a) * (u64)(b)) >> 32))
#define M2C_CARRY 0
#ifndef NULL
#define NULL ((void *)0)
#endif
#endif

extern s32 D_800AD950;
extern s32 D_800B3970;
extern s32 D_800B61A0;
extern s32 D_800B8294;
extern s32 D_800B9688;
extern s32 D_800B96AC;
extern u8 D_800B96C4;
extern s32 D_800B9D04;
extern s32 D_800BCA20;
extern s32 D_800BEDE4;
extern s32 D_800FB80C;
extern u64 D_800FB810;
s32 func_80002CE0();
s32 func_80005258();
s32 func_800068F0();
s32 func_8000BB10();
s32 func_8003E318();
s32 func_800447D8();
s32 func_800481F8();

void func_800065D4(s32 arg0) {
    s32 sp10;

    sp10 = 0;
    D_800B61A0 = 0;
    D_800BEDE4 = 0;
    D_800FB80C = 0;
    func_800068F0();
    func_800447D8(((s32)&D_800AD950));
    for (;;) {
        goto L13;
        return;
L13: ;
        func_8003E318(((s32)&D_800B9688), ((s32)&sp10), 1);
        switch (*(s16 *)sp10) {
        case 1:
            D_800B96AC++;
            D_800FB810++;
            if ((D_800B96C4 != 0) && (D_800FB80C == 0)) {
                D_800FB80C = 1;
                func_8000BB10();
                func_800481F8(((s32)&D_800B3970));
            } else {
                if (D_800B96C4 == 0) {
                    D_800B9D04 = 0;
                }
            }
            break;
        case 2:
            D_800BEDE4--;
            if (D_800B8294 != 0) {
                D_800BCA20 = func_80002CE0(D_800B8294);
                D_800B8294 = 0;
            }
            break;
        case 4:
            D_800BEDE4 = D_800BEDE4 + 2;
            func_80005258();
            break;
        }
    }
}
