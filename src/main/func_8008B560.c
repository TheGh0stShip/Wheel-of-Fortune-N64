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

struct gd_A8_s32 { u8 pad[0xA8]; s32 v; };
struct gd_AC_s32 { u8 pad[0xAC]; s32 v; };
struct gd_B0_s32 { u8 pad[0xB0]; s32 v; };
struct gd_B4_s32 { u8 pad[0xB4]; s32 v; };
struct gd_B8_s32 { u8 pad[0xB8]; s32 v; };
struct gd_BC_s32 { u8 pad[0xBC]; s32 v; };
struct gd_C0_s32 { u8 pad[0xC0]; s32 v; };
struct gd_C4_s32 { u8 pad[0xC4]; s32 v; };
struct gd_C8_s32 { u8 pad[0xC8]; s32 v; };
struct gd_1E0_s32 { u8 pad[0x1E0]; s32 v; };
struct gd_1E4_s32 { u8 pad[0x1E4]; s32 v; };
struct gd_1E8_s32 { u8 pad[0x1E8]; s32 v; };
struct gd_234_s32 { u8 pad[0x234]; s32 v; };
struct n64dk_e4 { u8 b[4]; };
struct n64dk_p1E4_4 { u8 pad[0x1E4]; struct n64dk_e4 *v; };
s32 func_800887D8();
s32 func_800888C0();
s32 func_80088A2C();
s32 func_80088C58();
s32 func_800A4C04();

s32 func_8008B560(s32 arg0) {
    s32 sp10;

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
        ((struct gd_A8_s32 *)arg0)->v = 1;
    } else {
        ((struct gd_A8_s32 *)arg0)->v = 0;
    }
    if (((struct gd_1E8_s32 *)arg0)->v < 2) {
        func_800887D8(arg0);
    }
    ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + 5;
    if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
        ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
        ((struct n64dk_p1E4_4 *)arg0)->v++;
        ((struct gd_1E8_s32 *)arg0)->v--;
        if (((struct gd_1E0_s32 *)arg0)->v != 0) {
            ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v | ((u32)(*(s32 *)((struct gd_1E4_s32 *)arg0)->v) >> (u32)(5 - ((struct gd_1E0_s32 *)arg0)->v));
        }
        sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xF8000000) >> 27;
        ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
    } else {
        sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xF8000000) >> 27;
        ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << 5;
    }
    ((struct gd_AC_s32 *)arg0)->v = sp10;
    if (((struct gd_1E8_s32 *)arg0)->v < 2) {
        func_800887D8(arg0);
    }
    ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + 6;
    if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
        ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
        ((struct n64dk_p1E4_4 *)arg0)->v++;
        ((struct gd_1E8_s32 *)arg0)->v--;
        if (((struct gd_1E0_s32 *)arg0)->v != 0) {
            ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v | ((u32)(*(s32 *)((struct gd_1E4_s32 *)arg0)->v) >> (u32)(6 - ((struct gd_1E0_s32 *)arg0)->v));
        }
        sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xFC000000) >> 26;
        ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
    } else {
        sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xFC000000) >> 26;
        ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << 6;
    }
    ((struct gd_B0_s32 *)arg0)->v = sp10;
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
    ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + 6;
    if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
        ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
        ((struct n64dk_p1E4_4 *)arg0)->v++;
        ((struct gd_1E8_s32 *)arg0)->v--;
        if (((struct gd_1E0_s32 *)arg0)->v != 0) {
            ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v | ((u32)(*(s32 *)((struct gd_1E4_s32 *)arg0)->v) >> (u32)(6 - ((struct gd_1E0_s32 *)arg0)->v));
        }
        sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xFC000000) >> 26;
        ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
    } else {
        sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xFC000000) >> 26;
        ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << 6;
    }
    ((struct gd_B4_s32 *)arg0)->v = sp10;
    if (((struct gd_1E8_s32 *)arg0)->v < 2) {
        func_800887D8(arg0);
    }
    ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + 6;
    if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
        ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
        ((struct n64dk_p1E4_4 *)arg0)->v++;
        ((struct gd_1E8_s32 *)arg0)->v--;
        if (((struct gd_1E0_s32 *)arg0)->v != 0) {
            ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v | ((u32)(*(s32 *)((struct gd_1E4_s32 *)arg0)->v) >> (u32)(6 - ((struct gd_1E0_s32 *)arg0)->v));
        }
        sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xFC000000) >> 26;
        ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
    } else {
        sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xFC000000) >> 26;
        ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << 6;
    }
    ((struct gd_B8_s32 *)arg0)->v = sp10;
    if (((struct gd_1E8_s32 *)arg0)->v < 2) {
        func_800887D8(arg0);
    }
    ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + 2;
    if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
        ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
        ((struct n64dk_p1E4_4 *)arg0)->v++;
        ((struct gd_1E8_s32 *)arg0)->v--;
        if (((struct gd_1E0_s32 *)arg0)->v != 0) {
            ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v | ((u32)(*(s32 *)((struct gd_1E4_s32 *)arg0)->v) >> (u32)(2 - ((struct gd_1E0_s32 *)arg0)->v));
        }
        sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xC0000000) >> 30;
        ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
    }
    sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xC0000000) >> 30;
    ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << 2;
    if ((u32)sp10 >= 2) {
        ((struct gd_BC_s32 *)arg0)->v = 1;
        if ((u32)sp10 >= 3) {
            ((struct gd_C0_s32 *)arg0)->v = 1;
        } else {
            ((struct gd_C0_s32 *)arg0)->v = 0;
        }
    } else {
        ((struct gd_BC_s32 *)arg0)->v = 0;
        if (sp10 != 0) {
            ((struct gd_C0_s32 *)arg0)->v = 1;
        } else {
            ((struct gd_C0_s32 *)arg0)->v = 0;
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
        if (((struct gd_C4_s32 *)arg0)->v != 0) {
            func_800A4C04(((struct gd_C4_s32 *)arg0)->v);
            ((struct gd_C4_s32 *)arg0)->v = 0;
        }
        ((struct gd_C4_s32 *)arg0)->v = func_80088A2C(arg0);
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
        if (((struct gd_C8_s32 *)arg0)->v != 0) {
            func_800A4C04(((struct gd_C8_s32 *)arg0)->v);
            ((struct gd_C8_s32 *)arg0)->v = 0;
        }
        ((struct gd_C8_s32 *)arg0)->v = func_80088A2C(arg0);
    }
    return 1;
}
