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
struct gd_4_s32 { u8 pad[0x4]; s32 v; };
struct gd_8_s32 { u8 pad[0x8]; s32 v; };
struct gd_C_s32 { u8 pad[0xC]; s32 v; };
struct gd_10_u8 { u8 pad[0x10]; u8 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct n64dk_a800B9D20 { s32 m0; u8 pad4[0x18]; };
extern struct n64dk_a800B9D20 D_800B9D20[];
struct n64dk_a800B9E70 { s32 m0; u8 pad4[0x18]; };
extern struct n64dk_a800B9E70 D_800B9E70[];
struct n64dk_a800B9FF8 { s32 m0; u8 pad4[0x18]; };
extern struct n64dk_a800B9FF8 D_800B9FF8[];
struct n64dk_a800BA180 { s32 m0; u8 pad4[0x18]; };
extern struct n64dk_a800BA180 D_800BA180[];
extern s32 D_800B61A8;
extern u8 D_800B9601[][21];
extern s32 D_800B96A8;
s32 func_80002CE0();
s32 func_8000A850();
s32 func_8000ACE8();
s32 func_80032AD4();

struct n64dk_r12 func_80010574(s32 arg1) {
    struct n64dk_r12 sp10;
    s32 pad0[2];
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    u8 sp34;
    s32 sp38;

    for (;;) {
        sp38 = func_8000ACE8(arg1);
        if (sp38 == 0) {
            break;
        }
        switch (sp38) {
        case 8:
            ((struct gd_C_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 0;
            ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 0;
            if (D_800B61A8 == 1) {
                ((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 0;
            } else {
                ((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 13;
            }
            D_800B96A8 = D_800B96A8 + 2;
            sp10.w[1] = 1;
            sp10.w[0] = 0;
            return sp10;
            break;
        case 34:
            sp10.w[1] = 0;
            sp10.w[0] = 0;
            return sp10;
        case 49:
            func_8000A850(6);
            sp10.w[1] = 0;
            sp10.w[0] = 0;
            return sp10;
        }
    }
    sp34 = ((struct gd_10_u8 *)((struct gd_30_s32 *)arg1)->v)->v;
    sp2C = ((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v;
    sp30 = ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v;
    if (((struct gd_C_s32 *)((struct gd_30_s32 *)arg1)->v)->v == 0) {
        if (D_800B61A8 == 1) {
            if (sp2C >= 7) {
                func_80032AD4(0);
                ((struct gd_C_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 1;
            }
        } else {
            if (sp2C < 7) {
                func_80032AD4(0);
                ((struct gd_C_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 1;
            }
        }
    }
    while ((sp2C < 14) && (sp2C >= 0)) {
        sp28 = sp30;
        while (!(sp28 >= 4)) {
            sp30 = 0;
            if (sp34 == D_800B9601[sp28][sp2C]) {
                ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v = sp28 + 1;
                ((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v = sp2C;
                if (((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v >= 4) {
                    ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 0;
                    ((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v = sp2C + D_800B61A8;
                }
                switch (sp28) {
                case 0:
                    D_800B9D20[sp2C].m0 = 0x1111AAFF;
                    break;
                case 1:
                    D_800B9E70[sp2C].m0 = 0x1111AAFF;
                    break;
                case 2:
                    D_800B9FF8[sp2C].m0 = 0x1111AAFF;
                    break;
                case 3:
                    D_800BA180[sp2C].m0 = 0x1111AAFF;
                    break;
                }
                func_80002CE0(2);
                sp10.w[1] = 1;
                sp10.w[0] = 15;
                return sp10;
            }
            sp28++;
        }
        sp2C = sp2C + D_800B61A8;
    }
    if (((struct gd_C_s32 *)((struct gd_30_s32 *)arg1)->v)->v == 0) {
        func_80032AD4(0);
        ((struct gd_C_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 1;
    }
    sp10.w[1] = 2;
    sp10.w[0] = 49;
    return sp10;
}
