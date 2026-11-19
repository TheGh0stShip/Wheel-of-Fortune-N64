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

struct gd_4_s32 { u8 pad[0x4]; s32 v; };
struct gd_10_s16 { u8 pad[0x10]; s16 v; };
struct gd_12_s16 { u8 pad[0x12]; s16 v; };
struct n64dk_e8 { u8 b[8]; };
extern s32 D_01021970;
extern s32 D_01146E68;
extern s32 D_80057970[][3];
extern struct n64dk_e8 *D_800B81E8;

void func_8000DF2C(s32 arg0, s32 arg1) {
    s32 pad0[2];
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;

    sp10 = (s32)D_800B81E8++;
    (*(s32 *)sp10) = 0x6000000;
    ((struct gd_4_s32 *)sp10)->v = (s32)&D_01021970;
    sp10 = (s32)D_800B81E8++;
    (*(s32 *)sp10) = 0xBA001402;
    ((struct gd_4_s32 *)sp10)->v = 0x200000;
    sp10 = (s32)D_800B81E8++;
    (*(s32 *)sp10) = 0xBA000E02;
    ((struct gd_4_s32 *)sp10)->v = 0x8000;
    sp10 = (s32)D_800B81E8++;
    (*(s32 *)sp10) = 0xFD100000;
    ((struct gd_4_s32 *)sp10)->v = (s32)&D_01146E68;
    sp10 = (s32)D_800B81E8++;
    (*(s32 *)sp10) = 0xE8000000;
    ((struct gd_4_s32 *)sp10)->v = 0;
    sp10 = (s32)D_800B81E8++;
    (*(s32 *)sp10) = 0xF5000100;
    ((struct gd_4_s32 *)sp10)->v = 0x7000000;
    sp10 = (s32)D_800B81E8++;
    (*(s32 *)sp10) = 0xE6000000;
    ((struct gd_4_s32 *)sp10)->v = 0;
    sp10 = (s32)D_800B81E8++;
    (*(s32 *)sp10) = 0xF0000000;
    ((struct gd_4_s32 *)sp10)->v = 0x703C000;
    sp10 = (s32)D_800B81E8++;
    (*(s32 *)sp10) = 0xE7000000;
    ((struct gd_4_s32 *)sp10)->v = 0;
    sp10 = (s32)D_800B81E8++;
    (*(s32 *)sp10) = 0xE7000000;
    ((struct gd_4_s32 *)sp10)->v = 0;
    sp8 = 0;
    for (;;) {
        if (sp8 >= 2) {
            return;
        }
        spC = 0;
        for (;;) {
            if (spC >= 3) {
                break;
            }
            sp10 = (s32)D_800B81E8++;
            (*(s32 *)sp10) = 0xFD500000;
            ((struct gd_4_s32 *)sp10)->v = D_80057970[sp8][spC];
            sp10 = (s32)D_800B81E8++;
            (*(s32 *)sp10) = 0xF5500000;
            ((struct gd_4_s32 *)sp10)->v = 0x7040100;
            sp10 = (s32)D_800B81E8++;
            (*(s32 *)sp10) = 0xE6000000;
            ((struct gd_4_s32 *)sp10)->v = 0;
            sp10 = (s32)D_800B81E8++;
            (*(s32 *)sp10) = 0xF3000000;
            ((struct gd_4_s32 *)sp10)->v = 0x73FF200;
            sp10 = (s32)D_800B81E8++;
            (*(s32 *)sp10) = 0xE7000000;
            ((struct gd_4_s32 *)sp10)->v = 0;
            sp10 = (s32)D_800B81E8++;
            (*(s32 *)sp10) = 0xF5400800;
            ((struct gd_4_s32 *)sp10)->v = 0x40100;
            sp10 = (s32)D_800B81E8++;
            (*(s32 *)sp10) = 0xF2000000;
            ((struct gd_4_s32 *)sp10)->v = 0xFC0FC;
            sp10 = (s32)D_800B81E8++;
            (*(s32 *)sp10) = 0xE7000000;
            ((struct gd_4_s32 *)sp10)->v = 0;
            sp10 = (s32)D_800B81E8++;
            (*(s32 *)sp10) = ((((((((struct gd_10_s16 *)arg0)->v + (spC * 64)) + 63) << 2) & 4095) << 12) | 0xE4000000) | ((((((struct gd_12_s16 *)arg0)->v + (sp8 * 64)) + 63) << 2) & 4095);
            ((struct gd_4_s32 *)sp10)->v = ((((((struct gd_10_s16 *)arg0)->v + (spC * 64)) << 2) & 4095) << 12) | (((((struct gd_12_s16 *)arg0)->v + (sp8 * 64)) << 2) & 4095);
            sp14 = (s32)D_800B81E8++;
            (*(s32 *)sp14) = 0xB4000000;
            ((struct gd_4_s32 *)sp14)->v = 0;
            sp14 = (s32)D_800B81E8++;
            (*(s32 *)sp14) = 0xB3000000;
            ((struct gd_4_s32 *)sp14)->v = 0x10000400;
            sp14 = (s32)D_800B81E8++;
            (*(s32 *)sp14) = 0xE7000000;
            ((struct gd_4_s32 *)sp14)->v = 0;
            spC++;
        }
        sp8++;
    }
}
