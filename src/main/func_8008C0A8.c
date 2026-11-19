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

struct gd_10_s32 { u8 pad[0x10]; s32 v; };
struct gd_14_s32 { u8 pad[0x14]; s32 v; };
struct gd_BC_s32 { u8 pad[0xBC]; s32 v; };
struct gd_CC_s32 { u8 pad[0xCC]; s32 v; };
struct gd_D0_s32 { u8 pad[0xD0]; s32 v; };
struct gd_D4_s32 { u8 pad[0xD4]; s32 v; };
struct gd_D8_s32 { u8 pad[0xD8]; s32 v; };
struct gd_DC_s32 { u8 pad[0xDC]; s32 v; };
struct gd_E0_s32 { u8 pad[0xE0]; s32 v; };
struct gd_E4_s32 { u8 pad[0xE4]; s32 v; };
struct gd_E8_s32 { u8 pad[0xE8]; s32 v; };
struct gd_EC_s32 { u8 pad[0xEC]; s32 v; };
struct gd_F0_s32 { u8 pad[0xF0]; s32 v; };
struct gd_F4_s32 { u8 pad[0xF4]; s32 v; };
struct gd_F8_s32 { u8 pad[0xF8]; s32 v; };
struct gd_10C_s32 { u8 pad[0x10C]; s32 v; };
struct gd_1E0_s32 { u8 pad[0x1E0]; s32 v; };
struct gd_1E4_s32 { u8 pad[0x1E4]; s32 v; };
struct gd_1E8_s32 { u8 pad[0x1E8]; s32 v; };
struct gd_234_s32 { u8 pad[0x234]; s32 v; };
struct gd_258_s32 { u8 pad[0x258]; s32 v; };
struct gd_25C_s32 { u8 pad[0x25C]; s32 v; };
struct gd_260_s32 { u8 pad[0x260]; s32 v; };
struct n64dk_e4 { u8 b[4]; };
struct n64dk_p1E4_4 { u8 pad[0x1E4]; struct n64dk_e4 *v; };
struct n64dk_f264_s32 { u8 pad[0x264]; s32 m[1]; };
extern s32 D_80085308;
extern s32 D_8008530C;
extern s32 D_80087EE0;
s32 func_80009F38();
s32 func_800887D8();
s32 func_800888C0();
s32 func_80088A2C();
s32 func_80088C58();
s32 func_800890C8();
s32 func_800A4C04();
s32 func_800A4CBC();

s32 func_8008C0A8(s32 arg0, s32 arg1) {
    s32 sp10;
    s32 sp14;

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
    ((struct gd_CC_s32 *)arg0)->v = sp10;
    if (((struct gd_1E8_s32 *)arg0)->v < 2) {
        func_800887D8(arg0);
    }
    ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + 3;
    if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
        ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
        ((struct n64dk_p1E4_4 *)arg0)->v++;
        ((struct gd_1E8_s32 *)arg0)->v--;
        if (((struct gd_1E0_s32 *)arg0)->v != 0) {
            ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v | ((u32)(*(s32 *)((struct gd_1E4_s32 *)arg0)->v) >> (u32)(3 - ((struct gd_1E0_s32 *)arg0)->v));
        }
        sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xE0000000) >> 29;
        ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
    } else {
        sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xE0000000) >> 29;
        ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << 3;
    }
    ((struct gd_D0_s32 *)arg0)->v = sp10;
    if ((((struct gd_D0_s32 *)arg0)->v == 3) && ((D_8008530C != 0) || ((((struct gd_25C_s32 *)arg0)->v == 0) || ((((struct gd_258_s32 *)arg0)->v == 0) && (((struct gd_BC_s32 *)arg0)->v == 0))))) {
        return -10;
    }
    if ((((struct gd_D0_s32 *)arg0)->v == 2) && ((D_80085308 != 0) || (((struct gd_25C_s32 *)arg0)->v == 0))) {
        return -10;
    }
    if (((struct gd_1E8_s32 *)arg0)->v < 2) {
        func_800887D8(arg0);
    }
    ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + 16;
    if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
        ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
        ((struct n64dk_p1E4_4 *)arg0)->v++;
        ((struct gd_1E8_s32 *)arg0)->v--;
        if (((struct gd_1E0_s32 *)arg0)->v != 0) {
            ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v | ((u32)(*(s32 *)((struct gd_1E4_s32 *)arg0)->v) >> (u32)(16 - ((struct gd_1E0_s32 *)arg0)->v));
        }
        sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xFFFF0000) >> 16;
        ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
    } else {
        sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xFFFF0000) >> 16;
        ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << 16;
    }
    ((struct gd_D4_s32 *)arg0)->v = sp10;
    if ((((struct gd_D0_s32 *)arg0)->v == 2) || (((struct gd_D0_s32 *)arg0)->v == 3)) {
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
            ((struct gd_D8_s32 *)arg0)->v = 1;
        } else {
            ((struct gd_D8_s32 *)arg0)->v = 0;
        }
        if (((struct gd_1E8_s32 *)arg0)->v < 2) {
            func_800887D8(arg0);
        }
        ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + 3;
        if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
            ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
            ((struct n64dk_p1E4_4 *)arg0)->v++;
            ((struct gd_1E8_s32 *)arg0)->v--;
            if (((struct gd_1E0_s32 *)arg0)->v != 0) {
                ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v | ((u32)(*(s32 *)((struct gd_1E4_s32 *)arg0)->v) >> (u32)(3 - ((struct gd_1E0_s32 *)arg0)->v));
            }
            sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xE0000000) >> 29;
            ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
        } else {
            sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xE0000000) >> 29;
            ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << 3;
        }
        ((struct gd_DC_s32 *)arg0)->v = sp10 - 1;
        ((struct gd_E0_s32 *)arg0)->v = 1 << ((struct gd_DC_s32 *)arg0)->v;
    }
    if (((struct gd_D0_s32 *)arg0)->v == 3) {
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
            ((struct gd_E4_s32 *)arg0)->v = 1;
        } else {
            ((struct gd_E4_s32 *)arg0)->v = 0;
        }
        if (((struct gd_1E8_s32 *)arg0)->v < 2) {
            func_800887D8(arg0);
        }
        ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + 3;
        if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
            ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
            ((struct n64dk_p1E4_4 *)arg0)->v++;
            ((struct gd_1E8_s32 *)arg0)->v--;
            if (((struct gd_1E0_s32 *)arg0)->v != 0) {
                ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v | ((u32)(*(s32 *)((struct gd_1E4_s32 *)arg0)->v) >> (u32)(3 - ((struct gd_1E0_s32 *)arg0)->v));
            }
            sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xE0000000) >> 29;
            ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
        } else {
            sp10 = (u32)(((struct gd_234_s32 *)arg0)->v & 0xE0000000) >> 29;
            ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << 3;
        }
        ((struct gd_E8_s32 *)arg0)->v = sp10 - 1;
        ((struct gd_EC_s32 *)arg0)->v = 1 << ((struct gd_E8_s32 *)arg0)->v;
    }
    if (((struct gd_F0_s32 *)arg0)->v != 0) {
        func_800A4C04(((struct gd_F0_s32 *)arg0)->v);
        ((struct gd_F0_s32 *)arg0)->v = 0;
    }
    ((struct gd_F0_s32 *)arg0)->v = func_800890C8(arg0);
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
        if (((struct gd_F4_s32 *)arg0)->v != 0) {
            func_800A4C04(((struct gd_F4_s32 *)arg0)->v);
            ((struct gd_F4_s32 *)arg0)->v = 0;
        }
        ((struct gd_F4_s32 *)arg0)->v = func_80088A2C(arg0);
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
        if (((struct gd_F8_s32 *)arg0)->v != 0) {
            func_800A4C04(((struct gd_F8_s32 *)arg0)->v);
            ((struct gd_F8_s32 *)arg0)->v = 0;
        }
        ((struct gd_F8_s32 *)arg0)->v = func_80088A2C(arg0);
    }
    sp14 = 0;
    for (;;) {
        if (((struct gd_10_s32 *)((struct n64dk_f264_s32 *)arg0)->m[sp14])->v == 0) {
            break;
        }
        if ((++sp14) >= 5) {
            func_80009F38(((s32)&D_80087EE0));
            func_800A4CBC(1);
        }
    }
    ((struct gd_260_s32 *)arg0)->v = ((struct n64dk_f264_s32 *)arg0)->m[sp14];
    ((struct gd_14_s32 *)((struct gd_260_s32 *)arg0)->v)->v = arg1;
    ((struct gd_10C_s32 *)arg0)->v = -1;
    return 1;
}
