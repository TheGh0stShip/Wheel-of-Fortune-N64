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
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
extern s32 D_80001594;
extern s32 D_80058FC8;
extern s32 D_80058FE0;
extern s32 D_80058FE8;
extern s32 D_80059008;
extern u16 D_800B96B0;
extern s32 D_800B96B4;
extern s8 D_800B9956;
extern s8 D_800B9957;
s32 func_80002CE0();
s32 func_80009F38();
s32 func_8000ACE8();
s32 func_80022784();
s32 func_800229D0();
s32 func_80022BC8();
s32 func_80022DC0();
s32 func_80022FE0();
s32 func_80026800();

struct n64dk_r12 func_80024868(s32 arg1) {
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
            ((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 0;
            ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v = D_80058FE0;
            func_80022784(arg1, ((s32)&D_80059008), ((s32)&D_80058FE8), 0);
            func_80022784(arg1, ((s32)&D_80059008), ((s32)&D_80058FC8), 1);
            return sp18;
        }
    }
    if (((D_800B96B0 & 0xA000) & 0xFFFF) != 0) {
        ((struct gd_C_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 0;
        func_80002CE0(42);
        switch (((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v) {
        case 0:
            func_80022BC8(arg1, ((s32)&D_80059008), ((s32)&D_80058FC8), 2);
            break;
        case 1:
            func_80026800();
            sp18.w[1] = 0;
            sp18.w[0] = 1;
            return sp18;
        default:
            func_80009F38(((s32)&D_80001594));
        }
    }
    if (((D_800B96B0 & 0x5000) & 0xFFFF) != 0) {
        func_80002CE0(42);
        func_80026800();
        sp18.w[1] = 0;
        sp18.w[0] = 1;
        return sp18;
    } else {
        if (((D_800B96B0 & 2048) & 0xFFFF) != 0) {
            func_800229D0(arg1, ((s32)&D_80059008), ((s32)&D_80058FC8), 2);
        } else {
            if (((D_800B96B0 & 1024) & 0xFFFF) != 0) {
                func_80022BC8(arg1, ((s32)&D_80059008), ((s32)&D_80058FC8), 2);
            } else {
                if (((D_800B96B0 & 512) & 0xFFFF) != 0) {
                    func_80022DC0(arg1, ((s32)&D_80059008), ((((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v * 32) + ((s32)&D_80058FC8)), 0);
                } else {
                    if (((D_800B96B0 & 256) & 0xFFFF) != 0) {
                        func_80022FE0(arg1, ((s32)&D_80059008), ((((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v * 32) + ((s32)&D_80058FC8)), 0);
                    }
                }
            }
        }
    }
    if (((struct gd_C_s32 *)((struct gd_30_s32 *)arg1)->v)->v <= 0) {
        if (D_800B9956 >= 41) {
            func_80022FE0(arg1, ((s32)&D_80059008), ((((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v * 32) + ((s32)&D_80058FC8)), 0);
        } else {
            if (D_800B9956 < -40) {
                func_80022DC0(arg1, ((s32)&D_80059008), ((((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v * 32) + ((s32)&D_80058FC8)), 0);
            }
        }
        if (D_800B9957 >= 41) {
            func_800229D0(arg1, ((s32)&D_80059008), ((s32)&D_80058FC8), 2);
        } else {
            if (D_800B9957 < -40) {
                func_80022BC8(arg1, ((s32)&D_80059008), ((s32)&D_80058FC8), 2);
            }
        }
    } else {
        ((struct gd_C_s32 *)((struct gd_30_s32 *)arg1)->v)->v = ((struct gd_C_s32 *)((struct gd_30_s32 *)arg1)->v)->v - D_800B96B4;
    }
    return sp18;
}
