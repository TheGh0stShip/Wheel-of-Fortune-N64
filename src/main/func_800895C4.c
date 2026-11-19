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

struct gd_A0_s32 { u8 pad[0xA0]; s32 v; };
struct gd_A4_s32 { u8 pad[0xA4]; s32 v; };
struct gd_C4_s32 { u8 pad[0xC4]; s32 v; };
struct gd_C8_s32 { u8 pad[0xC8]; s32 v; };
struct gd_F0_s32 { u8 pad[0xF0]; s32 v; };
struct gd_F4_s32 { u8 pad[0xF4]; s32 v; };
struct gd_F8_s32 { u8 pad[0xF8]; s32 v; };
struct gd_104_s32 { u8 pad[0x104]; s32 v; };
struct gd_1E0_s32 { u8 pad[0x1E0]; s32 v; };
struct gd_1E4_s32 { u8 pad[0x1E4]; s32 v; };
struct gd_1E8_s32 { u8 pad[0x1E8]; s32 v; };
struct gd_1EC_s32 { u8 pad[0x1EC]; s32 v; };
struct gd_1F0_s32 { u8 pad[0x1F0]; s32 v; };
struct gd_1F4_s32 { u8 pad[0x1F4]; s32 v; };
struct gd_204_s32 { u8 pad[0x204]; s32 v; };
struct gd_23C_s32 { u8 pad[0x23C]; s32 v; };
struct gd_244_s32 { u8 pad[0x244]; s32 v; };
struct gd_248_s32 { u8 pad[0x248]; s32 v; };
struct gd_258_s32 { u8 pad[0x258]; s32 v; };
struct gd_25C_s32 { u8 pad[0x25C]; s32 v; };
struct gd_260_s32 { u8 pad[0x260]; s32 v; };
struct n64dk_f264_s32 { u8 pad[0x264]; s32 m[1]; };
struct n64dk_h20_8_s8 { u8 pad[0x20]; s8 m[1][0x8]; };
struct n64dk_h60_8_s8 { u8 pad[0x60]; s8 m[1][0x8]; };
extern s32 D_80087EA0;
s32 func_800A4C28();

s32 func_800895C4(s32 arg0) {
    s32 sp10;
    s32 sp14;
    s32 sp18;

    if ((u32)arg0 < 4) {
        return 0;
    }
    arg0 = (u32)(arg0 + 3) >> 2;
    sp18 = func_800A4C28(632);
    ((struct gd_C4_s32 *)sp18)->v = ((struct gd_C8_s32 *)sp18)->v = ((struct gd_F0_s32 *)sp18)->v = ((struct gd_F8_s32 *)sp18)->v = ((struct gd_F4_s32 *)sp18)->v = ((struct gd_104_s32 *)sp18)->v = ((struct gd_A0_s32 *)sp18)->v = ((struct gd_A4_s32 *)sp18)->v = 0;
    sp10 = 0;
    for (;;) {
        if (sp10 >= 8) {
            break;
        }
        sp14 = 0;
        for (;;) {
            if (sp14 >= 8) {
                break;
            }
            ((struct n64dk_h20_8_s8 *)sp18)->m[sp10][sp14] = *(u8 *)(((sp10 * 8) + sp14) + ((s32)&D_80087EA0));
            sp14++;
        }
        sp10++;
    }
    sp10 = 0;
    for (;;) {
        if (sp10 >= 8) {
            break;
        }
        sp14 = 0;
        for (;;) {
            if (sp14 >= 8) {
                break;
            }
            ((struct n64dk_h60_8_s8 *)sp18)->m[sp10][sp14] = 16;
            sp14++;
        }
        sp10++;
    }
    ((struct gd_260_s32 *)sp18)->v = ((struct gd_258_s32 *)sp18)->v = ((struct gd_25C_s32 *)sp18)->v = 0;
    sp10 = 0;
    for (;;) {
        if (sp10 >= 5) {
            break;
        }
        ((struct n64dk_f264_s32 *)sp18)->m[sp10] = 0;
        sp10++;
    }
    ((struct gd_1EC_s32 *)sp18)->v = func_800A4C28((arg0 * 4));
    ((struct gd_1F0_s32 *)sp18)->v = arg0 - 1;
    ((struct gd_1E0_s32 *)sp18)->v = 0;
    ((struct gd_1E8_s32 *)sp18)->v = 0;
    ((struct gd_1E4_s32 *)sp18)->v = ((struct gd_1EC_s32 *)sp18)->v;
    ((struct gd_1F4_s32 *)sp18)->v = 0;
    ((struct gd_23C_s32 *)sp18)->v = 0;
    ((struct gd_248_s32 *)sp18)->v = 0;
    ((struct gd_244_s32 *)sp18)->v = 0;
    ((struct gd_204_s32 *)sp18)->v = 0;
    return sp18;
}
