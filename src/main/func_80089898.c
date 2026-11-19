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
struct gd_1E0_s32 { u8 pad[0x1E0]; s32 v; };
struct gd_1E4_s32 { u8 pad[0x1E4]; s32 v; };
struct gd_1E8_s32 { u8 pad[0x1E8]; s32 v; };
struct gd_1EC_s32 { u8 pad[0x1EC]; s32 v; };
struct gd_1F4_s32 { u8 pad[0x1F4]; s32 v; };
struct gd_204_s32 { u8 pad[0x204]; s32 v; };
struct gd_234_s32 { u8 pad[0x234]; s32 v; };
struct gd_248_s32 { u8 pad[0x248]; s32 v; };
struct gd_250_f64 { u8 pad[0x250]; f64 v; };
struct gd_258_s32 { u8 pad[0x258]; s32 v; };
struct gd_25C_s32 { u8 pad[0x25C]; s32 v; };
struct gd_260_s32 { u8 pad[0x260]; s32 v; };
struct n64dk_f264_s32 { u8 pad[0x264]; s32 m[1]; };
f64 func_80089490();

void func_80089898(s32 arg0) {
    s32 sp10;

    ((struct gd_260_s32 *)arg0)->v = ((struct gd_258_s32 *)arg0)->v = ((struct gd_25C_s32 *)arg0)->v = 0;
    sp10 = 0;
    for (;;) {
        if (sp10 >= 5) {
            break;
        }
        ((struct gd_10_s32 *)((struct n64dk_f264_s32 *)arg0)->m[sp10])->v = 0;
        sp10++;
    }
    ((struct gd_1E0_s32 *)arg0)->v = ((struct gd_1E8_s32 *)arg0)->v = 0;
    ((struct gd_1E4_s32 *)arg0)->v = ((struct gd_1EC_s32 *)arg0)->v;
    ((struct gd_234_s32 *)arg0)->v = 0;
    ((struct gd_1F4_s32 *)arg0)->v = 0;
    ((struct gd_250_f64 *)arg0)->v = func_80089490();
    ((struct gd_248_s32 *)arg0)->v = 0;
    ((struct gd_204_s32 *)arg0)->v = 0;
}
