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

struct n64dk_a800B9D0C { s32 m0; u8 pad4[0x4]; s32 m8; u8 padC[0x8]; s32 m14; u8 pad18[0x4]; };
extern struct n64dk_a800B9D0C D_800B9D0C[];
struct n64dk_a800B9E5C { s32 m0; u8 pad4[0x4]; s32 m8; u8 padC[0x8]; s32 m14; u8 pad18[0x4]; };
extern struct n64dk_a800B9E5C D_800B9E5C[];
struct n64dk_a800B9FE4 { s32 m0; u8 pad4[0x4]; s32 m8; u8 padC[0x8]; s32 m14; u8 pad18[0x4]; };
extern struct n64dk_a800B9FE4 D_800B9FE4[];
struct n64dk_a800BA16C { s32 m0; u8 pad4[0x4]; s32 m8; u8 padC[0x8]; s32 m14; u8 pad18[0x4]; };
extern struct n64dk_a800BA16C D_800BA16C[];
extern s32 D_010A3388;
extern s32 D_800B9559;
extern s32 D_800B956E;
extern s32 D_800B9583;
extern s32 D_800B9598;

void func_80011F58(void) {
    s32 sp0;

    for (sp0 = 0;;) {
        if (sp0 >= 12) {
            break;
        }
        if ((*(u8 *)(sp0 + ((s32)&D_800B9559))) == 43) {
            D_800B9D0C[sp0].m0 = (s32)&D_010A3388;
            D_800B9D0C[sp0].m14 = 0x88888888;
            D_800B9D0C[sp0].m8 = 0;
        }
        sp0++;
    }
    sp0 = 0;
    for (;;) {
        if (sp0 >= 14) {
            break;
        }
        if ((*(u8 *)(sp0 + ((s32)&D_800B956E))) == 43) {
            D_800B9E5C[sp0].m0 = (s32)&D_010A3388;
            D_800B9E5C[sp0].m14 = 0x88888888;
            D_800B9E5C[sp0].m8 = 0;
        }
        sp0++;
    }
    sp0 = 0;
    for (;;) {
        if (sp0 >= 14) {
            break;
        }
        if ((*(u8 *)(sp0 + ((s32)&D_800B9583))) == 43) {
            D_800B9FE4[sp0].m0 = (s32)&D_010A3388;
            D_800B9FE4[sp0].m14 = 0x88888888;
            D_800B9FE4[sp0].m8 = 0;
        }
        sp0++;
    }
    sp0 = 0;
    for (;;) {
        if (sp0 >= 12) {
            return;
        }
        if ((*(u8 *)(sp0 + ((s32)&D_800B9598))) == 43) {
            D_800BA16C[sp0].m0 = (s32)&D_010A3388;
            D_800BA16C[sp0].m14 = 0x88888888;
            D_800BA16C[sp0].m8 = 0;
        }
        sp0++;
    }
}
