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

struct n64dk_a800584E0 { s32 m0; u8 pad4[0x1C]; };
extern struct n64dk_a800584E0 D_800584E0[];
struct n64dk_a800B99A4 { s32 m0; s32 m4; u8 pad8[0x10C]; };
extern struct n64dk_a800B99A4 D_800B99A4[];
extern f32 D_80001674;
extern s32 D_80058E88;
extern s32 D_80058FE0;
extern s32 D_8005A498;
extern f32 D_800B8298;
extern s32 D_800B96C0;
extern u8 D_800B96C4;
extern s32 D_800B99AC;
extern s32 D_800BEDD8;
s32 func_80009900();

void func_80026FD4(void) {
    s32 sp10;
    s32 sp14;

    D_800B8298 = D_80001674;
    D_800B96C0 = 6;
    sp10 = 0;
    for (;;) {
        if (sp10 >= 3) {
            break;
        }
        D_800584E0[sp10].m0 = 4;
        D_800B99A4[sp10].m0 = 4;
        D_800B99A4[sp10].m4 = sp10;
        (*(s32 *)((sp10 * 4) + ((s32)&D_800BEDD8))) = sp10;
        func_80009900(((sp10 * 276) + ((s32)&D_800B99AC)), ((sp10 * 10) + ((s32)&D_8005A498)));
        sp10++;
    }
    sp14 = 0;
    sp10 = 0;
    for (;;) {
        if (sp10 >= 4) {
            break;
        }
        if (((D_800B96C4 >> sp10) % 2) != 0) {
            D_800584E0[sp14].m0 = sp10;
            D_800B99A4[sp14].m0 = sp10;
            sp14++;
        }
        if (sp14 >= 3) {
            break;
        }
        sp10++;
    }
    D_80058E88 = 1;
    D_80058FE0 = 3;
}
