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
struct gd_18_s32 { u8 pad[0x18]; s32 v; };
struct gd_1C_s32 { u8 pad[0x1C]; s32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct gd_34_s32 { u8 pad[0x34]; s32 v; };
struct gd_38_s32 { u8 pad[0x38]; s32 v; };
struct gd_40_s32 { u8 pad[0x40]; s32 v; };
extern s32 D_80000870;
s32 func_80009F38();
s32 func_8000A0E4();
s32 func_8000A204();
s32 func_8000A31C();

s32 func_8000A56C(s32 arg0, s32 arg1) {
    s32 sp10;
    s32 sp14;
    s8 pad0;

    sp10 = func_8000A0E4();
    sp14 = func_8000A204();
    if (sp14 == 0) {
        func_80009F38(((s32)&D_80000870));
        return 0;
    }
    ((struct gd_40_s32 *)sp10)->v = sp14;
    (*(s32 *)sp14) = arg0;
    ((struct gd_8_s32 *)sp14)->v = arg1;
    ((struct gd_C_s32 *)sp14)->v = 0;
    ((struct gd_10_s32 *)sp14)->v = 0;
    ((struct gd_1C_s32 *)sp14)->v = 8;
    ((struct gd_18_s32 *)sp14)->v = 1;
    ((struct gd_40_s32 *)sp14)->v = 0;
    ((struct gd_34_s32 *)sp14)->v = 0;
    ((struct gd_38_s32 *)sp14)->v = 0;
    ((struct gd_30_s32 *)sp14)->v = func_8000A31C(((struct gd_4_s32 *)sp14)->v);
    return sp14;
}
