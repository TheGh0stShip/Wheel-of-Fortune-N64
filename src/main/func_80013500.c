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

struct n64dk_a800B9990 { s32 m0; s32 m4; u8 pad8[0x10C]; };
extern struct n64dk_a800B9990 D_800B9990[];
extern s32 D_01035FA8;
extern s32 D_010367A8;
extern s32 D_80057A68;
extern s32 D_800BEEA8[][8];
s32 func_80009A74();
s32 func_80009AE0();

void func_80013500(s32 arg0) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 pad0[2];
    s32 sp28[6];

    sp10 = 0;
    for (;;) {
        if (sp10 >= 3) {
            return;
        }
        sp14 = 0;
        for (;;) {
            if (sp14 >= 8) {
                break;
            }
            D_800BEEA8[sp10][sp14] = (s32)&D_010367A8;
            sp14++;
        }
        if (arg0 != 0) {
            sp1C = D_800B9990[sp10].m4;
        } else {
            sp1C = D_800B9990[sp10].m0;
        }
        func_80009AE0(((s32)&sp28), sp1C);
        sp18 = func_80009A74(((s32)&sp28));
        if (sp18 >= 8) {
            sp18 = 7;
        }
        D_800BEEA8[sp10][7 - sp18] = (s32)&D_01035FA8;
        sp14 = 0;
        for (;;) {
            if (sp14 >= sp18) {
                break;
            }
            D_800BEEA8[sp10][(sp14 + 8) - sp18] = *(s32 *)(((*(u8 *)(((s32)&sp28) + sp14)) * 4) + ((s32)&D_80057A68));
            sp14++;
        }
        sp10++;
    }
}
