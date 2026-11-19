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
struct gd_10_s32 { u8 pad[0x10]; s32 v; };
struct gd_14_s32 { u8 pad[0x14]; s32 v; };
struct gd_18_s32 { u8 pad[0x18]; s32 v; };
struct gd_1C_s32 { u8 pad[0x1C]; s32 v; };
struct gd_20_s32 { u8 pad[0x20]; s32 v; };
struct gd_24_s32 { u8 pad[0x24]; s32 v; };
struct gd_28_s32 { u8 pad[0x28]; s32 v; };
struct gd_2C_s32 { u8 pad[0x2C]; s32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct gd_34_s32 { u8 pad[0x34]; s32 v; };
struct gd_38_s32 { u8 pad[0x38]; s32 v; };
struct gd_3C_s32 { u8 pad[0x3C]; s32 v; };
struct gd_40_s32 { u8 pad[0x40]; s32 v; };
struct gd_44_s32 { u8 pad[0x44]; s32 v; };
struct gd_48_s32 { u8 pad[0x48]; s32 v; };
struct gd_4C_s32 { u8 pad[0x4C]; s32 v; };
struct gd_50_s32 { u8 pad[0x50]; s32 v; };
struct gd_54_s32 { u8 pad[0x54]; s32 v; };
struct gd_58_s32 { u8 pad[0x58]; s32 v; };
struct gd_5C_s32 { u8 pad[0x5C]; s32 v; };
struct gd_60_s32 { u8 pad[0x60]; s32 v; };
struct gd_64_s32 { u8 pad[0x64]; s32 v; };
struct gd_68_s32 { u8 pad[0x68]; s32 v; };
struct gd_6C_s32 { u8 pad[0x6C]; s32 v; };
struct gd_70_s32 { u8 pad[0x70]; s32 v; };
struct gd_74_s32 { u8 pad[0x74]; s32 v; };
struct gd_78_s32 { u8 pad[0x78]; s32 v; };
struct gd_7C_s32 { u8 pad[0x7C]; s32 v; };
s32 func_8009D67C();

void func_8009D4B8(s32 arg0, s32 arg1) {
    register s32 reg_s0;
    register s32 reg_s1;
    s16 sp10;
    s32 sp14;

    if (arg1 == 0) {
        reg_s0 = arg0;
        reg_s1 = *(s16 *)arg0;
        sp14 = 8;
        if (reg_s1 < 0) {
            sp10 = reg_s1 * -1;
            sp10 = (sp14 >> 1) + ((u16)sp10);
            sp10 = sp10 / sp14;
            sp10 = -((u16)sp10);
        } else {
            sp10 = (reg_s1 + (sp14 >> 1)) / sp14;
        }
        reg_s1 = sp10;
        reg_s1 = reg_s1 & 0xFFFF;
        reg_s1 = reg_s1 | (sp10 << 16);
        (*(s32 *)reg_s0) = reg_s1;
        ((struct gd_4_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_8_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_C_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_10_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_14_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_18_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_1C_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_20_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_24_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_28_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_2C_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_30_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_34_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_38_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_3C_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_40_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_44_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_48_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_4C_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_50_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_54_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_58_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_5C_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_60_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_64_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_68_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_6C_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_70_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_74_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_78_s32 *)reg_s0)->v = reg_s1;
        ((struct gd_7C_s32 *)reg_s0)->v = reg_s1;
        return;
    }
    func_8009D67C(arg0);
    return;
}
