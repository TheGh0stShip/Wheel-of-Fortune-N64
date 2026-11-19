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

struct gd_1E0_s32 { u8 pad[0x1E0]; s32 v; };
struct gd_1E4_s32 { u8 pad[0x1E4]; s32 v; };
struct gd_1E8_s32 { u8 pad[0x1E8]; s32 v; };
struct gd_234_s32 { u8 pad[0x234]; s32 v; };
struct n64dk_e4 { u8 b[4]; };
struct n64dk_p1E4_4 { u8 pad[0x1E4]; struct n64dk_e4 *v; };
s32 func_800887D8();

s32 func_80088C58(s32 arg0) {
    s32 sp10;
    s32 sp14;
    s32 sp18;

    if (arg0 == 0) {
        return -1;
    }
    if (((struct gd_1E8_s32 *)arg0)->v < 4) {
        func_800887D8(arg0);
    }
    sp14 = ((struct gd_1E0_s32 *)arg0)->v % 8;
    if (sp14 != 0) {
        if (arg0 == 0) {
        }
        if (((struct gd_1E8_s32 *)arg0)->v < 2) {
            func_800887D8(arg0);
        }
        ((struct gd_1E0_s32 *)arg0)->v += 8 - sp14;
        if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
            ((struct gd_1E8_s32 *)arg0)->v--;
            ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
            ((struct n64dk_p1E4_4 *)arg0)->v++;
            ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
        } else {
            ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << (8 - sp14);
        }
    }
    sp10 = 0;
    for (;;) {
        if (((struct gd_1E8_s32 *)arg0)->v <= 0) {
            break;
        }
        if (((struct gd_1E8_s32 *)arg0)->v < 4) {
            func_800887D8(arg0);
        }
        if (((struct gd_1E8_s32 *)arg0)->v < 2) {
            func_800887D8(arg0);
        }
        ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + 8;
        if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
            ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
            ((struct n64dk_p1E4_4 *)arg0)->v++;
            ((struct gd_1E8_s32 *)arg0)->v--;
            if (((struct gd_1E0_s32 *)arg0)->v != 0) {
                ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v | ((u32)(*(s32 *)((struct gd_1E4_s32 *)arg0)->v) >> (u32)(8 - ((struct gd_1E0_s32 *)arg0)->v));
            }
            sp18 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xFF000000) >> 24;
            ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
        } else {
            sp18 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xFF000000) >> 24;
            ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << 8;
        }
        if (sp18 == 0) {
            if (sp10 < 2) {
                sp10++;
            }
        } else {
            if (sp18 == 1) {
                if (sp10 == 2) {
                    sp10++;
                } else {
                    sp10 = 0;
                }
            } else {
                sp10 = 0;
            }
        }
        if (sp10 == 3) {
            ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 24;
            if (((struct gd_1E0_s32 *)arg0)->v < 0) {
                ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + 32;
                ((struct gd_1E8_s32 *)arg0)->v++;
                ((struct n64dk_p1E4_4 *)arg0)->v--;
                ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
            } else {
                ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
            }
            return 1;
        }
    }
    return -2;
}
