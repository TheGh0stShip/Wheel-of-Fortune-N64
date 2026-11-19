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
struct gd_18_s32 { u8 pad[0x18]; s32 v; };
struct gd_1C_s32 { u8 pad[0x1C]; s32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
s32 func_80002CE0();
s32 func_80022784();

void func_80022BC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_80002CE0(44);
    func_80022784(arg0, arg1, ((((struct gd_8_s32 *)((struct gd_30_s32 *)arg0)->v)->v * 32) + arg2), 0);
    ((struct gd_18_s32 *)((((struct gd_8_s32 *)((struct gd_30_s32 *)arg0)->v)->v * 32) + arg2))->v = ((struct gd_4_s32 *)((struct gd_30_s32 *)arg0)->v)->v;
    for (;;) {
        ((struct gd_8_s32 *) ((struct gd_30_s32 *) arg0)->v)->v++;
        if (((struct gd_8_s32 *)((struct gd_30_s32 *)arg0)->v)->v >= arg3) {
            ((struct gd_8_s32 *)((struct gd_30_s32 *)arg0)->v)->v = 0;
        }
        if ((*(s32 *)((((struct gd_8_s32 *)((struct gd_30_s32 *)arg0)->v)->v * 32) + arg2)) != 0) {
            break;
        }
    }
    ((struct gd_4_s32 *)((struct gd_30_s32 *)arg0)->v)->v = ((struct gd_18_s32 *)((((struct gd_8_s32 *)((struct gd_30_s32 *)arg0)->v)->v * 32) + arg2))->v;
    if (((struct gd_1C_s32 *)((((struct gd_8_s32 *)((struct gd_30_s32 *)arg0)->v)->v * 32) + arg2))->v != 0) {
        ((s32 (*)())((struct gd_1C_s32 *)((((struct gd_8_s32 *)((struct gd_30_s32 *)arg0)->v)->v * 32) + arg2))->v)(((struct gd_8_s32 *)((struct gd_30_s32 *)arg0)->v)->v);
    }
    func_80022784(arg0, arg1, ((((struct gd_8_s32 *)((struct gd_30_s32 *)arg0)->v)->v * 32) + arg2), 1);
    ((struct gd_C_s32 *)((struct gd_30_s32 *)arg0)->v)->v = 15;
}
