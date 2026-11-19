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
struct gd_14_s32 { u8 pad[0x14]; s32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct n64dk_a800B9D20 { s32 m0; u8 pad4[0x18]; };
extern struct n64dk_a800B9D20 D_800B9D20[];
struct n64dk_a800B9E70 { s32 m0; u8 pad4[0x18]; };
extern struct n64dk_a800B9E70 D_800B9E70[];
struct n64dk_a800B9FF8 { s32 m0; u8 pad4[0x18]; };
extern struct n64dk_a800B9FF8 D_800B9FF8[];
struct n64dk_a800BA180 { s32 m0; u8 pad4[0x18]; };
extern struct n64dk_a800BA180 D_800BA180[];
extern s32 D_800B9601;
s32 func_80002CE0();
s32 func_800099B0();
s32 func_8000A850();
s32 func_8000ACE8();
s32 func_80032AD4();

struct n64dk_r12 func_80010D3C(s32 arg1) {
    struct n64dk_r12 sp10;
    s32 pad0[2];
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 pad1;
    s32 sp38;
    u8 sp3C;
    s32 sp40;

    sp10.w[1] = 1;
    sp10.w[0] = 0;
    for (;;) {
        sp40 = func_8000ACE8(arg1);
        if (sp40 == 0) {
            break;
        }
        switch (sp40) {
        case 8:
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
    sp3C = *(u8 *)((struct gd_14_s32 *)((struct gd_30_s32 *)arg1)->v)->v;
    if (sp3C == 0) {
        func_80032AD4(0);
        sp10.w[1] = 2;
        sp10.w[0] = 49;
        return sp10;
    }
    sp28 = ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v;
    for (;;) {
        if (sp28 >= 4) {
            break;
        }
        sp38 = (((s32)&D_800B9601) + (sp28 * 21)) + ((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v;
        for (;;) {
            if (sp38 == 0) {
                break;
            }
            sp38 = func_800099B0(sp38, sp3C);
            if (sp38 != 0) {
                sp38++;
                ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v = sp28;
                ((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v = (sp38 - ((s32)&D_800B9601)) - (sp28 * 21);
                sp2C = ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v;
                sp30 = ((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v - 1;
                switch (sp2C) {
                case 0:
                    D_800B9D20[sp30].m0 = 0x1111AAFF;
                    break;
                case 1:
                    D_800B9E70[sp30].m0 = 0x1111AAFF;
                    break;
                case 2:
                    D_800B9FF8[sp30].m0 = 0x1111AAFF;
                    break;
                case 3:
                    D_800BA180[sp30].m0 = 0x1111AAFF;
                    break;
                }
                func_80002CE0(2);
                sp10.w[1] = 1;
                sp10.w[0] = 15;
                return sp10;
            }
        }
        ((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 0;
        sp28++;
    }
    ((struct gd_14_s32 *)((struct gd_30_s32 *)arg1)->v)->v++;
    ((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 0;
    ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 0;
    return sp10;
}
