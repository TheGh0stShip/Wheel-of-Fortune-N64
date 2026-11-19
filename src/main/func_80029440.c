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

struct n64dk_a8005B710 { s32 m0; u8 pad4[0x4]; s32 m8; u8 padC[0x14]; s32 m20; s32 m24; };
extern struct n64dk_a8005B710 D_8005B710[];
extern s32 D_01017550;
extern s32 D_01017650;
extern s32 D_01017750;
extern s32 D_010178D0;
extern s32 D_01017A50;
extern s32 D_01017BD0;
extern s32 D_80001690;
extern s32 func_80028D3C;
extern s32 func_80029098;
extern s32 D_8005B5A4;
extern s32 D_800B9544;
extern s32 D_800BCD54;
s32 func_80009A74();
s32 func_80009F38();
s32 func_8000A56C();
s32 func_80027218();

void func_80029440(void) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;

    sp10 = func_80009A74(((s32)&D_800B9544));
    if (sp10 >= 21) {
        func_80009F38(((s32)&D_80001690));
    }
    sp1C = 0;
    for (;;) {
        if (sp1C >= 22) {
            break;
        }
        D_8005B710[sp1C].m20 = 0;
        D_8005B710[sp1C].m24 = 0;
        sp1C++;
    }
    sp14 = 152 - (sp10 * 6);
    sp18 = 0;
    D_8005B710[sp18].m24 = (s32)&D_01017550;
    D_8005B710[sp18].m0 = sp14;
    D_8005B710[sp18].m8 = 8;
    if (D_800BCD54 == 8) {
        D_8005B710[sp18].m20 = D_8005B710[sp18].m24;
    }
    sp18++;
    sp14 = sp14 + 8;
    sp1C = 0;
    for (;;) {
        if (sp1C >= sp10) {
            break;
        }
        switch (*(u8 *)(sp1C + ((s32)&D_800B9544))) {
        case 38:
            D_8005B710[sp18].m24 = (s32)&D_01017750;
            break;
        case 45:
            D_8005B710[sp18].m24 = (s32)&D_010178D0;
            break;
        case 32:
            D_8005B710[sp18].m24 = (s32)&D_01017BD0;
            break;
        case 47:
            D_8005B710[sp18].m24 = (s32)&D_01017A50;
            break;
        default:
            D_8005B710[sp18].m24 = *(s32 *)(((*(u8 *)(sp1C + ((s32)&D_800B9544))) * 4) + ((s32)&D_8005B5A4));
        }
        D_8005B710[sp18].m0 = sp14;
        D_8005B710[sp18].m8 = 12;
        if (D_800BCD54 == 8) {
            D_8005B710[sp18].m20 = D_8005B710[sp18].m24;
        }
        sp18++;
        sp14 = sp14 + 12;
        sp1C++;
    }
    D_8005B710[sp18].m24 = (s32)&D_01017650;
    D_8005B710[sp18].m0 = sp14;
    D_8005B710[sp18].m8 = 8;
    if (D_800BCD54 == 8) {
        D_8005B710[sp18].m20 = D_8005B710[sp18].m24;
        return;
    }
    sp20 = func_8000A56C(((s32)&func_80029098), 0x6040000);
    sp24 = func_80027218(sp20, 0, ((s32)&func_80028D3C), 0x5000000);
}
