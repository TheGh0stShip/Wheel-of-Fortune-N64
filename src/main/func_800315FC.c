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
struct n64dk_mAC00_2000 { u8 pad[0xAC00]; struct { u8 b[0x2000]; } m[1]; };
struct gd_4_s32 { u8 pad[0x4]; s32 v; };
struct gd_8_s32 { u8 pad[0x8]; s32 v; };
struct gd_10_s32 { u8 pad[0x10]; s32 v; };
struct gd_18_s32 { u8 pad[0x18]; s32 v; };
struct gd_1C_s32 { u8 pad[0x1C]; s32 v; };
struct gd_24_s32 { u8 pad[0x24]; s32 v; };
struct gd_28_s32 { u8 pad[0x28]; s32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct gd_44_s32 { u8 pad[0x44]; s32 v; };
struct n64dk_o800BEF5C { u8 pad[0x4]; struct { u8 b[0x1E47C]; } a; };
extern struct n64dk_o800BEF5C D_800BEF5C[];
extern s32 D_800B61A0;
extern s32 D_800B96B4;
extern s32 D_800BCD54;
extern s32 D_800BEF60;
s32 func_8000ACE8();
s32 func_80016638();
s32 func_80031340();
s32 func_8003FF78();

struct n64dk_r12 func_800315FC(s32 arg1) {
    struct n64dk_r12 sp10;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;

    sp34 = 0x2000000;
    sp24 = *(s32 *)((struct gd_30_s32 *)arg1)->v;
    sp2C = ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v;
    for (;;) {
        sp20 = func_8000ACE8(arg1);
        if (sp20 == 0) {
            break;
        }
        switch (sp20) {
        case 8:
            ((struct gd_28_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 0;
            ((struct gd_10_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 0;
            ((struct gd_24_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 1;
            break;
        }
    }
    if ((func_80016638() != 0) && (D_800BCD54 != 7)) {
        sp10.w[1] = 1;
        sp10.w[0] = 0;
        return sp10;
    }
    sp30 = ((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v + (((struct gd_10_s32 *)((struct gd_30_s32 *)arg1)->v)->v * 0x2000);
    func_80031340(sp30, sp2C);
    sp28 = func_8003FF78(((s32)&((struct n64dk_mAC00_2000 *)&D_800BEF5C[D_800B61A0].a)->m[sp2C]));
    sp28 = sp28 - func_8003FF78(((D_800B61A0 * 0x1E480) + ((s32)&D_800BEF60)));
    ((struct gd_44_s32 *)sp24)->v = sp34 + sp28;
    ((struct gd_28_s32 *)((struct gd_30_s32 *)arg1)->v)->v = ((struct gd_28_s32 *)((struct gd_30_s32 *)arg1)->v)->v + D_800B96B4;
    if (((struct gd_28_s32 *)((struct gd_30_s32 *)arg1)->v)->v >= 4) {
        ((struct gd_28_s32 *)((struct gd_30_s32 *)arg1)->v)->v = ((struct gd_28_s32 *)((struct gd_30_s32 *)arg1)->v)->v % 4;
        ((struct gd_10_s32 *)((struct gd_30_s32 *)arg1)->v)->v = ((struct gd_10_s32 *)((struct gd_30_s32 *)arg1)->v)->v + ((struct gd_24_s32 *)((struct gd_30_s32 *)arg1)->v)->v;
        if (((struct gd_10_s32 *)((struct gd_30_s32 *)arg1)->v)->v < 0) {
            if (((struct gd_1C_s32 *)((struct gd_30_s32 *)arg1)->v)->v != 0) {
                ((struct gd_10_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 1;
                ((struct gd_24_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 1;
            } else {
                sp10.w[1] = 0;
                sp10.w[0] = 0;
                return sp10;
            }
        } else {
            if (((struct gd_10_s32 *)((struct gd_30_s32 *)arg1)->v)->v >= ((struct gd_18_s32 *)((struct gd_30_s32 *)arg1)->v)->v) {
                if (((struct gd_1C_s32 *)((struct gd_30_s32 *)arg1)->v)->v == 1) {
                    ((struct gd_10_s32 *)((struct gd_30_s32 *)arg1)->v)->v = ((struct gd_18_s32 *)((struct gd_30_s32 *)arg1)->v)->v - 2;
                    ((struct gd_24_s32 *)((struct gd_30_s32 *)arg1)->v)->v = -1;
                } else {
                    if (((struct gd_1C_s32 *)((struct gd_30_s32 *)arg1)->v)->v == 2) {
                        ((struct gd_10_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 0;
                        ((struct gd_24_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 1;
                    } else {
                        sp10.w[1] = 0;
                        sp10.w[0] = 0;
                        return sp10;
                    }
                }
            }
        }
    }
    sp10.w[1] = 1;
    sp10.w[0] = 0;
    return sp10;
}
