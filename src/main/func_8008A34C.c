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
struct gd_8_s32 { u8 pad[0x8]; s32 v; };
struct gd_C_s32 { u8 pad[0xC]; s32 v; };
struct gd_10_s8 { u8 pad[0x10]; s8 v; };
struct gd_11_s8 { u8 pad[0x11]; s8 v; };
struct gd_14_s32 { u8 pad[0x14]; s32 v; };
struct gd_18_s32 { u8 pad[0x18]; s32 v; };
struct gd_1C_s32 { u8 pad[0x1C]; s32 v; };
struct gd_A0_s32 { u8 pad[0xA0]; s32 v; };
struct gd_A4_s32 { u8 pad[0xA4]; s32 v; };
struct gd_1E0_s32 { u8 pad[0x1E0]; s32 v; };
struct gd_1E4_s32 { u8 pad[0x1E4]; s32 v; };
struct gd_1E8_s32 { u8 pad[0x1E8]; s32 v; };
struct gd_234_s32 { u8 pad[0x234]; s32 v; };
struct gd_240_s32 { u8 pad[0x240]; s32 v; };
struct gd_264_s32 { u8 pad[0x264]; s32 v; };
struct n64dk_e4 { u8 b[4]; };
struct n64dk_p1E4_4 { u8 pad[0x1E4]; struct n64dk_e4 *v; };
struct n64dk_f264_s32 { u8 pad[0x264]; s32 m[1]; };
struct n64dk_h20_8_s8 { u8 pad[0x20]; s8 m[1][0x8]; };
struct n64dk_h60_8_s8 { u8 pad[0x60]; s8 m[1][0x8]; };
struct n64dk_a80087A98 { s32 m0; s32 m4; };
extern struct n64dk_a80087A98 D_80087A98[];
s32 func_800887D8();
s32 func_800888C0();
s32 func_80088A2C();
s32 func_80088C58();
s32 func_80089984();
s32 func_800A4C04();

s32 func_8008A34C(s32 arg0, s32 arg1) {
    s32 sp10;
    s32 sp14;
    s32 sp18;

    sp18 = ((struct gd_240_s32 *)arg0)->v;
    if (arg0 == 0) {
    }
    if (((struct gd_1E8_s32 *)arg0)->v < 2) {
        func_800887D8(arg0);
    }
    ((struct n64dk_p1E4_4 *)arg0)->v++;
    ((struct gd_1E8_s32 *)arg0)->v--;
    ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
    if (((struct gd_1E8_s32 *)arg0)->v < 2) {
        func_800887D8(arg0);
    }
    ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + 12;
    if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
        ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
        ((struct n64dk_p1E4_4 *)arg0)->v++;
        ((struct gd_1E8_s32 *)arg0)->v--;
        if (((struct gd_1E0_s32 *)arg0)->v != 0) {
            ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v | ((u32)(*(s32 *)((struct gd_1E4_s32 *)arg0)->v) >> (u32)(12 - ((struct gd_1E0_s32 *)arg0)->v));
        }
        sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xFFF00000) >> 20;
        ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
    } else {
        sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xFFF00000) >> 20;
        ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << 12;
    }
    (*(s32 *)arg0) = sp10;
    if (((struct gd_1E8_s32 *)arg0)->v < 2) {
        func_800887D8(arg0);
    }
    ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + 12;
    if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
        ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
        ((struct n64dk_p1E4_4 *)arg0)->v++;
        ((struct gd_1E8_s32 *)arg0)->v--;
        if (((struct gd_1E0_s32 *)arg0)->v != 0) {
            ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v | ((u32)(*(s32 *)((struct gd_1E4_s32 *)arg0)->v) >> (u32)(12 - ((struct gd_1E0_s32 *)arg0)->v));
        }
        sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xFFF00000) >> 20;
        ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
    } else {
        sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xFFF00000) >> 20;
        ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << 12;
    }
    ((struct gd_4_s32 *)arg0)->v = sp10;
    ((struct gd_C_s32 *)arg0)->v = (u32)((*(s32 *)arg0) + 15) >> 4;
    ((struct gd_8_s32 *)arg0)->v = (u32)(((struct gd_4_s32 *)arg0)->v + 15) >> 4;
    if (((struct gd_264_s32 *)arg0)->v == 0) {
        sp14 = 0;
        for (;;) {
            if (sp14 >= 5) {
                break;
            }
            ((struct n64dk_f264_s32 *)arg0)->m[sp14] = func_80089984(arg0, arg1);
            sp14++;
        }
    }
    if (((struct gd_1E8_s32 *)arg0)->v < 2) {
        func_800887D8(arg0);
    }
    ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + 4;
    if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
        ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
        ((struct n64dk_p1E4_4 *)arg0)->v++;
        ((struct gd_1E8_s32 *)arg0)->v--;
        if (((struct gd_1E0_s32 *)arg0)->v != 0) {
            ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v | ((u32)(*(s32 *)((struct gd_1E4_s32 *)arg0)->v) >> (u32)(4 - ((struct gd_1E0_s32 *)arg0)->v));
        }
        sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xF0000000) >> 28;
        ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
    } else {
        sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xF0000000) >> 28;
        ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << 4;
    }
    ((struct gd_10_s8 *)arg0)->v = sp10;
    if (((struct gd_1E8_s32 *)arg0)->v < 2) {
        func_800887D8(arg0);
    }
    ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + 4;
    if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
        ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
        ((struct n64dk_p1E4_4 *)arg0)->v++;
        ((struct gd_1E8_s32 *)arg0)->v--;
        if (((struct gd_1E0_s32 *)arg0)->v != 0) {
            ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v | ((u32)(*(s32 *)((struct gd_1E4_s32 *)arg0)->v) >> (u32)(4 - ((struct gd_1E0_s32 *)arg0)->v));
        }
        sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xF0000000) >> 28;
        ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
    } else {
        sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xF0000000) >> 28;
        ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << 4;
    }
    ((struct gd_11_s8 *)arg0)->v = sp10;
    if (((struct gd_1E8_s32 *)arg0)->v < 2) {
        func_800887D8(arg0);
    }
    ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + 18;
    if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
        ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
        ((struct n64dk_p1E4_4 *)arg0)->v++;
        ((struct gd_1E8_s32 *)arg0)->v--;
        if (((struct gd_1E0_s32 *)arg0)->v != 0) {
            ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v | ((u32)(*(s32 *)((struct gd_1E4_s32 *)arg0)->v) >> (u32)(18 - ((struct gd_1E0_s32 *)arg0)->v));
        }
        sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & -0x4000) >> 14;
        ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
    } else {
        sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & -0x4000) >> 14;
        ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << 18;
    }
    ((struct gd_14_s32 *)arg0)->v = sp10;
    if (arg0 == 0) {
    }
    if (((struct gd_1E8_s32 *)arg0)->v < 2) {
        func_800887D8(arg0);
    }
    ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + 1;
    if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
        ((struct gd_1E8_s32 *)arg0)->v--;
        ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
        ((struct n64dk_p1E4_4 *)arg0)->v++;
        ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
    } else {
        ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << 1;
    }
    if (((struct gd_1E8_s32 *)arg0)->v < 2) {
        func_800887D8(arg0);
    }
    ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + 10;
    if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
        ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
        ((struct n64dk_p1E4_4 *)arg0)->v++;
        ((struct gd_1E8_s32 *)arg0)->v--;
        if (((struct gd_1E0_s32 *)arg0)->v != 0) {
            ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v | ((u32)(*(s32 *)((struct gd_1E4_s32 *)arg0)->v) >> (u32)(10 - ((struct gd_1E0_s32 *)arg0)->v));
        }
        sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xFFC00000) >> 22;
        ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
    } else {
        sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xFFC00000) >> 22;
        ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << 10;
    }
    ((struct gd_18_s32 *)arg0)->v = sp10;
    if (((struct gd_1E8_s32 *)arg0)->v < 2) {
        func_800887D8(arg0);
    }
    sp10 = (u32)((struct gd_234_s32 *)arg0)->v >> 31;
    ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << 1;
    ((struct gd_1E0_s32 *)arg0)->v++;
    if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
        ((struct gd_1E0_s32 *)arg0)->v = 0;
        ((struct n64dk_p1E4_4 *)arg0)->v++;
        ((struct gd_234_s32 *)arg0)->v = *(s32 *)((struct gd_1E4_s32 *)arg0)->v;
        ((struct gd_1E8_s32 *)arg0)->v--;
    }
    if (sp10 != 0) {
        ((struct gd_1C_s32 *)arg0)->v = 1;
    } else {
        ((struct gd_1C_s32 *)arg0)->v = 0;
    }
    if (((struct gd_1E8_s32 *)arg0)->v < 2) {
        func_800887D8(arg0);
    }
    sp10 = (u32)((struct gd_234_s32 *)arg0)->v >> 31;
    ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << 1;
    ((struct gd_1E0_s32 *)arg0)->v++;
    if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
        ((struct gd_1E0_s32 *)arg0)->v = 0;
        ((struct n64dk_p1E4_4 *)arg0)->v++;
        ((struct gd_234_s32 *)arg0)->v = *(s32 *)((struct gd_1E4_s32 *)arg0)->v;
        ((struct gd_1E8_s32 *)arg0)->v--;
    }
    if (sp10 != 0) {
        sp14 = 0;
        for (;;) {
            if (sp14 >= 64) {
                break;
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
                sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xFF000000) >> 24;
                ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
            } else {
                sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xFF000000) >> 24;
                ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << 8;
            }
            ((struct n64dk_h20_8_s8 *)arg0)->m[D_80087A98[sp14].m4][D_80087A98[sp14].m0] = sp10;
            sp14++;
        }
    }
    if (((struct gd_1E8_s32 *)arg0)->v < 2) {
        func_800887D8(arg0);
    }
    sp10 = (u32)((struct gd_234_s32 *)arg0)->v >> 31;
    ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << 1;
    ((struct gd_1E0_s32 *)arg0)->v++;
    if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
        ((struct gd_1E0_s32 *)arg0)->v = 0;
        ((struct n64dk_p1E4_4 *)arg0)->v++;
        ((struct gd_234_s32 *)arg0)->v = *(s32 *)((struct gd_1E4_s32 *)arg0)->v;
        ((struct gd_1E8_s32 *)arg0)->v--;
    }
    if (sp10 != 0) {
        sp14 = 0;
        for (;;) {
            if (sp14 >= 64) {
                break;
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
                sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xFF000000) >> 24;
                ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
            } else {
                sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xFF000000) >> 24;
                ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << 8;
            }
            ((struct n64dk_h60_8_s8 *)arg0)->m[D_80087A98[sp14].m4][D_80087A98[sp14].m0] = sp10;
            sp14++;
        }
    }
    func_80088C58(arg0);
    if (func_800888C0(32, 437, arg0) != 0) {
        if (arg0 == 0) {
        }
        if (((struct gd_1E8_s32 *)arg0)->v < 2) {
            func_800887D8(arg0);
        }
        ((struct n64dk_p1E4_4 *)arg0)->v++;
        ((struct gd_1E8_s32 *)arg0)->v--;
        ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
        if (((struct gd_A0_s32 *)arg0)->v != 0) {
            func_800A4C04(((struct gd_A0_s32 *)arg0)->v);
            ((struct gd_A0_s32 *)arg0)->v = 0;
        }
        ((struct gd_A0_s32 *)arg0)->v = func_80088A2C(arg0);
    }
    if (func_800888C0(32, 434, arg0) != 0) {
        if (arg0 == 0) {
        }
        if (((struct gd_1E8_s32 *)arg0)->v < 2) {
            func_800887D8(arg0);
        }
        ((struct n64dk_p1E4_4 *)arg0)->v++;
        ((struct gd_1E8_s32 *)arg0)->v--;
        ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
        if (((struct gd_A4_s32 *)arg0)->v != 0) {
            func_800A4C04(((struct gd_A4_s32 *)arg0)->v);
            ((struct gd_A4_s32 *)arg0)->v = 0;
        }
        ((struct gd_A4_s32 *)arg0)->v = func_80088A2C(arg0);
    }
    return 1;
}
