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
struct gd_4_f32 { u8 pad[0x4]; f32 v; };
struct gd_8_s32 { u8 pad[0x8]; s32 v; };
struct gd_2C_f32 { u8 pad[0x2C]; f32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct n64dk_a800B99A4 { s32 m0; u8 pad4[0x110]; };
extern struct n64dk_a800B99A4 D_800B99A4[];
extern f32 D_80000BB4;
extern f32 D_80000BB8;
extern f64 D_80000BBC;
extern f32 D_80000BC4;
extern f32 D_80000BC8;
extern f64 D_80000BCC;
extern f32 D_80000BD4;
extern f32 D_80000BD8;
extern s32 D_800581F0;
extern s32 D_800B96B4;
extern u16 D_800BC6F8;
extern f32 D_800BCCF0;
extern s32 D_800FB808;
s32 func_80002CE0();
s32 func_800051B4();
s32 func_80009108(f32);
s32 func_80009C98();
s32 func_8000ACE8();
s32 func_8000B5DC();

struct n64dk_r12 func_8000F274(s32 arg1) {
    struct n64dk_r12 sp10;
    s32 sp20;
    s32 sp24;
    f32 sp28;
    f32 sp2C;
    s32 sp30;
    s32 sp34;

    for (;;) {
        sp34 = func_8000ACE8(arg1);
        if (sp34 == 0) {
            break;
        }
        switch (sp34) {
        case 34:
            sp10.w[1] = 0;
            sp10.w[0] = 1;
            return sp10;
        }
    }
    sp20 = *(s32 *)((struct gd_30_s32 *)arg1)->v;
    sp10.w[1] = 1;
    sp10.w[0] = 0;
    sp24 = func_8000B5DC(0x4010000, 0xFFFF0000);
    if (sp24 == 0) {
        return sp10;
    }
    sp28 = ((struct gd_2C_f32 *)sp24)->v + ((f32)(*(s32 *)(((((struct gd_8_s32 *)arg1)->v & 255) * 4) + ((s32)&D_800581F0))));
    sp30 = (s32)(sp28 / D_80000BB4);
    sp28 = sp28 - ((f32)(sp30 * 5));
    if (((f64)((D_800BCCF0 / D_80000BB8) * ((f32)D_800B96B4))) > D_80000BBC) {
        sp2C = (sp28 * D_80000BC4) + D_80000BC8;
        if ((((struct gd_8_s32 *)arg1)->v & 255) == D_800FB808) {
            if (D_800B99A4[D_800FB808].m0 < 4) {
                func_800051B4(D_800B99A4[D_800FB808].m0, 2, 1.0);
            }
            if ((u32)D_800BC6F8 < 16) {
                func_80002CE0((func_80009C98(11) + 27));
            }
        }
    } else {
        if (((f64)sp28) > D_80000BCC) {
            if (sp28 < D_80000BD4) {
                sp2C = sp28 * D_80000BD8;
                goto L164;
            }
        }
        sp28 = 0;
        sp2C = 0;
L164: ;
        if ((((struct gd_8_s32 *)arg1)->v & 255) == D_800FB808) {
            if ((sp2C - ((struct gd_2C_f32 *)sp20)->v) < 0.0f) {
                if (((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v > 0) {
                    func_80002CE0((func_80009C98(2) + 25));
                    if (D_800B99A4[D_800FB808].m0 < 4) {
                        func_800051B4(D_800B99A4[D_800FB808].m0, 5, 1.0);
                    }
                }
            }
        }
    }
    if ((((struct gd_8_s32 *)arg1)->v & 255) == D_800FB808) {
        func_80009108((((((struct gd_2C_f32 *)sp24)->v + ((f32)(*(s32 *)((D_800FB808 * 4) + ((s32)&D_800581F0))))) - sp28) + ((struct gd_4_f32 *)((struct gd_30_s32 *)arg1)->v)->v));
    }
    ((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v = (s32)(sp2C - ((struct gd_2C_f32 *)sp20)->v);
    ((struct gd_2C_f32 *)sp20)->v = sp2C;
    return sp10;
}
