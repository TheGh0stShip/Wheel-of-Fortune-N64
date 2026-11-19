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

struct n64dk_r12 { s32 w[3]; };
struct gd_10_s16 { u8 pad[0x10]; s16 v; };
struct gd_12_s16 { u8 pad[0x12]; s16 v; };
struct gd_20_s32 { u8 pad[0x20]; s32 v; };
struct gd_24_s32 { u8 pad[0x24]; s32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
extern s32 D_800B3CB8;
extern s32 D_800B40C4;
extern s32 D_800B8294;
extern s32 D_800BCA28;
s32 func_8000A850();
s32 func_8000ACE8();
s32 func_8000B9FC();
s32 func_800212C0();
s32 func_800219B8();
s32 func_800A4E58();

struct n64dk_r12 func_80021548(s32 arg1) {
    s32 sp10;
    struct n64dk_r12 sp18;
    s8 pad0;

    sp18.w[1] = 1;
    sp18.w[0] = 0;
    for (;;) {
        sp10 = func_8000ACE8(arg1);
        if (sp10 == 0) {
            break;
        }
        switch (sp10) {
        case 8:
            if (((struct gd_24_s32 *)((struct gd_30_s32 *)arg1)->v)->v > 0) {
                D_800B8294 = ((struct gd_24_s32 *)((struct gd_30_s32 *)arg1)->v)->v;
            }
            D_800B3CB8 = 4;
            break;
        case 34:
            sp18.w[1] = 0;
            sp18.w[0] = 1;
            return sp18;
        }
    }
    func_800212C0(arg1);
    if (D_800B40C4 != 0) {
        func_8000B9FC(1);
        D_800B3CB8 = 0;
        sp18.w[1] = 0;
        sp18.w[0] = 1;
        if (D_800B40C4 == 2) {
            func_800A4E58(0);
            func_800219B8(D_800BCA28, ((struct gd_20_s32 *)((struct gd_30_s32 *)arg1)->v)->v, ((struct gd_10_s16 *)(*(s32 *)((struct gd_30_s32 *)arg1)->v))->v, ((struct gd_12_s16 *)(*(s32 *)((struct gd_30_s32 *)arg1)->v))->v);
        } else {
            if (((struct gd_20_s32 *)((struct gd_30_s32 *)arg1)->v)->v != 0) {
                func_8000A850(((struct gd_20_s32 *)((struct gd_30_s32 *)arg1)->v)->v);
            }
        }
    }
    return sp18;
}
