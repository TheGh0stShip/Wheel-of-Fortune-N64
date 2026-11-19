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

struct gd_18_s32 { u8 pad[0x18]; s32 v; };
struct n64dk_a800584E0 { s32 m0; u8 pad4[0x1C]; };
extern struct n64dk_a800584E0 D_800584E0[];
struct n64dk_a80058B48 { s32 m0; s32 m4; u8 pad8[0x20]; };
extern struct n64dk_a80058B48 D_80058B48[];
struct n64dk_a8005A474 { s32 m0; s32 m4; s32 m8; };
extern struct n64dk_a8005A474 D_8005A474[];
struct n64dk_a800B9990 { u8 pad0[0x14]; s32 m14; s32 m18; u8 pad1C[0xF8]; };
extern struct n64dk_a800B9990 D_800B9990[];
extern s32 D_01157868;
extern s32 D_01158068;
extern s32 D_01158868;
extern s32 D_01159068;
extern s32 D_01159868;
extern s32 func_80022218;
extern s32 func_80025150;
s32 func_8000A56C();
s32 func_800258BC();
s32 func_80027218();
s32 func_800323C4();

void func_80026800(void) {
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;

    sp24 = func_8000A56C(((s32)&func_80025150), 0x5000000);
    func_80027218(sp24, 0, ((s32)&func_80022218), 0x5000000);
    func_800258BC();
    sp18 = 0;
    for (;;) {
        if (sp18 >= 3) {
            break;
        }
        if (D_800B9990[sp18].m14 == 4) {
            for (;;) {
                sp20 = 0;
                sp1C = 0;
                for (;;) {
                    if (sp1C >= 3) {
                        break;
                    }
                    if (sp18 != sp1C) {
                        if (D_800B9990[sp18].m18 == D_800B9990[sp1C].m18) {
                            sp20++;
                        }
                    }
                    sp1C++;
                }
                if (sp20 != 0) {
                    D_800B9990[sp18].m18++;
                    if (D_800B9990[sp18].m18 >= 6) {
                        D_800B9990[sp18].m18 = 0;
                    }
                }
                if (sp20 <= 0) {
                    break;
                }
            }
        }
        sp18++;
    }
    sp18 = 0;
    for (;;) {
        if (sp18 >= 3) {
            return;
        }
        func_800323C4(D_800B9990[sp18].m18, sp18, D_8005A474[sp18].m0, D_8005A474[sp18].m4, D_8005A474[sp18].m8);
        switch (D_800584E0[sp18].m0) {
        case 0:
            D_80058B48[(sp18 * 3) + 2].m0 = (s32)&D_01158068;
            D_80058B48[(sp18 * 3) + 2].m4 = (s32)&D_01158068;
            break;
        case 1:
            D_80058B48[(sp18 * 3) + 2].m0 = (s32)&D_01158868;
            D_80058B48[(sp18 * 3) + 2].m4 = (s32)&D_01158868;
            break;
        case 2:
            D_80058B48[(sp18 * 3) + 2].m0 = (s32)&D_01159068;
            D_80058B48[(sp18 * 3) + 2].m4 = (s32)&D_01159068;
            break;
        case 3:
            D_80058B48[(sp18 * 3) + 2].m0 = (s32)&D_01159868;
            D_80058B48[(sp18 * 3) + 2].m4 = (s32)&D_01159868;
            break;
        case 4:
            D_80058B48[(sp18 * 3) + 2].m0 = (s32)&D_01157868;
            D_80058B48[(sp18 * 3) + 2].m4 = (s32)&D_01157868;
            break;
        }
        sp18++;
    }
}
