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

struct gd_8_s32 { u8 pad[0x8]; s32 v; };
struct gd_C_s32 { u8 pad[0xC]; s32 v; };
struct gd_10_s32 { u8 pad[0x10]; s32 v; };
struct gd_11_u8 { u8 pad[0x11]; u8 v; };
struct gd_1F4_s32 { u8 pad[0x1F4]; s32 v; };
struct gd_248_s32 { u8 pad[0x248]; s32 v; };
struct gd_260_s32 { u8 pad[0x260]; s32 v; };
extern s32 D_80086CD0;
extern s32 D_80086D10;
extern s32 D_80086D18;
extern s32 D_80086D28;
extern s32 D_80086D2C;
extern s32 D_80086D30;
extern s32 D_80086D34;
extern s32 D_80086D38;
extern s32 D_800FD298;
extern s32 D_800FD29C;
extern s32 D_800FD2A0;
extern s32 D_800FD2A4;
extern s32 D_800FD2A8;
s32 func_80021090();
s32 func_800A2B08();
s32 func_800A2D38();
s32 func_800A4F74();

void func_8009CAD8(s32 arg0, s32 arg1) {
    register s32 reg_s0;
    register s32 reg_s1;
    s32 pad0;
    s32 sp14;
    s32 sp18[2];
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;

    if (arg1 != 0) {
        sp20 = ((struct gd_10_s32 *)arg1)->v;
    }
    ((struct gd_248_s32 *)arg0)->v++;
    if (D_80086D30 != 0) {
        if (D_80086D38 != -1) {
            if (((struct gd_248_s32 *)arg0)->v > D_80086D38) {
                ((struct gd_1F4_s32 *)arg0)->v = 1;
                if (D_80086D18 != 0) {
                    func_800A2D38(arg0);
                }
                return;
            }
        }
        if (((struct gd_248_s32 *)arg0)->v < D_80086D34) {
            return;
        }
    }
    switch (D_80086D10) {
    case 0:
        break;
    default:
        func_800A4F74(((s32)&D_800FD2A4), 0);
        reg_s0 = D_800FD2A0 - D_800FD2A8;
        reg_s1 = D_800FD29C - D_800FD2A4;
        if (reg_s0 < 0) {
            reg_s0 = reg_s0 + 0xF4240;
            reg_s1 = reg_s1 - 1;
        }
        D_800FD2A0 = D_800FD2A8 + D_800FD298;
        if (0xF423F < D_800FD2A0) {
            D_800FD2A0 = D_800FD2A0 - 0xF4240;
            D_800FD29C = D_800FD2A4 + 1;
        } else {
            D_800FD29C = D_800FD2A4;
        }
        break;
    case -1:
        switch (D_80086D2C) {
        case -1:
            D_80086D10 = *(s32 *)((((struct gd_11_u8 *)arg0)->v * 4) + ((s32)&D_80086CD0));
            func_800A4F74(((s32)&D_800FD29C), 0);
            D_800FD298 = 0xF4240 / D_80086D10;
            break;
        case 0:
            D_80086D10 = 0;
            break;
        default:
            D_80086D10 = D_80086D2C;
            func_800A4F74(((s32)&D_800FD29C), 0);
            D_800FD298 = 0xF4240 / D_80086D10;
            break;
        }
        break;
    }
    if (arg1 == 0) {
        return;
    }
    if (D_80086D28 == 0) {
        if ((*(s32 *)arg1) == 0) {
            sp24 = 16;
            sp28 = ((struct gd_C_s32 *)arg0)->v * sp24;
            sp2C = ((struct gd_8_s32 *)arg0)->v * sp24;
            sp14 = func_800A2B08(sp20, ((s32)&sp18));
            (*(s32 *)arg1) = 0;
        }
        func_80021090(((struct gd_C_s32 *)((struct gd_260_s32 *)arg0)->v)->v);
    }
}
