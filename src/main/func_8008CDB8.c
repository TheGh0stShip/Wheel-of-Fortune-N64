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

struct gd_C_s32 { u8 pad[0xC]; s32 v; };
struct gd_FC_s32 { u8 pad[0xFC]; s32 v; };
struct gd_100_s32 { u8 pad[0x100]; s32 v; };
struct gd_104_s32 { u8 pad[0x104]; s32 v; };
struct gd_108_s32 { u8 pad[0x108]; s32 v; };
struct gd_140_s32 { u8 pad[0x140]; s32 v; };
struct gd_144_s32 { u8 pad[0x144]; s32 v; };
struct gd_148_s32 { u8 pad[0x148]; s32 v; };
struct gd_14C_s32 { u8 pad[0x14C]; s32 v; };
struct gd_150_s32 { u8 pad[0x150]; s32 v; };
struct gd_1D4_s16 { u8 pad[0x1D4]; s16 v; };
struct gd_1D6_s16 { u8 pad[0x1D6]; s16 v; };
struct gd_1D8_s16 { u8 pad[0x1D8]; s16 v; };
struct gd_1E0_s32 { u8 pad[0x1E0]; s32 v; };
struct gd_1E4_s32 { u8 pad[0x1E4]; s32 v; };
struct gd_1E8_s32 { u8 pad[0x1E8]; s32 v; };
struct gd_234_s32 { u8 pad[0x234]; s32 v; };
struct n64dk_e4 { u8 b[4]; };
struct n64dk_p1E4_4 { u8 pad[0x1E4]; struct n64dk_e4 *v; };
s32 func_800887D8();
s32 func_800890C8();
s32 func_800A4C04();

s32 func_8008CDB8(s32 arg0) {
    s32 sp10;

    if (arg0 == 0) {
    }
    if (((struct gd_1E8_s32 *)arg0)->v < 2) {
        func_800887D8(arg0);
    }
    ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v + 24;
    if ((((struct gd_1E0_s32 *)arg0)->v & 32) != 0) {
        ((struct gd_1E8_s32 *)arg0)->v--;
        ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E0_s32 *)arg0)->v - 32;
        ((struct n64dk_p1E4_4 *)arg0)->v++;
        ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
    } else {
        ((struct gd_234_s32 *)arg0)->v = ((struct gd_234_s32 *)arg0)->v << 24;
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
    ((struct gd_FC_s32 *)arg0)->v = sp10;
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
    ((struct gd_100_s32 *)arg0)->v = sp10;
    if (((struct gd_104_s32 *)arg0)->v != 0) {
        func_800A4C04(((struct gd_104_s32 *)arg0)->v);
        ((struct gd_104_s32 *)arg0)->v = 0;
    }
    ((struct gd_104_s32 *)arg0)->v = func_800890C8(arg0);
    ((struct gd_140_s32 *)arg0)->v = -2;
    ((struct gd_144_s32 *)arg0)->v = 0;
    ((struct gd_148_s32 *)arg0)->v = 0;
    ((struct gd_14C_s32 *)arg0)->v = 0;
    ((struct gd_150_s32 *)arg0)->v = 0;
    ((struct gd_108_s32 *)arg0)->v = ((((struct gd_FC_s32 *)arg0)->v - 1) * ((struct gd_C_s32 *)arg0)->v) - 1;
    ((struct gd_1D4_s16 *)arg0)->v = 0x2000;
    ((struct gd_1D6_s16 *)arg0)->v = 0x2000;
    ((struct gd_1D8_s16 *)arg0)->v = 0x2000;
    return 1;
}
