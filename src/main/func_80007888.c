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

struct n64dk_e21 { u8 b[21]; };
struct n64dk_a800B966A { s8 m0; };
extern struct n64dk_a800B966A D_800B966A[];
struct n64dk_a800B9990 { s32 m0; u8 pad4[0x4]; s32 m8; s32 mC; u8 pad10[0xE8]; s32 mF8; u8 padFC[0x18]; };
extern struct n64dk_a800B9990 D_800B9990[];
extern s32 D_8004B9FC;
extern s32 D_8004BA04;
extern s32 D_800B9538;
extern s32 D_800B953C;
extern s32 D_800B9601;
extern s32 D_800B9CF8;
extern s32 D_800B9CFC;
extern s32 D_800B9D00;
extern s32 D_800BCA00;
extern s32 D_800FB808;
s32 func_80008F64();
s32 func_8000928C();
s32 func_800099B0();

s32 func_80007888(register s32 arg0, s32 arg1) {
    u8 sp10;
    s32 sp14;
    s32 sp18;
    void *sp1C;

    sp10 = arg0;
    D_800B9CF8 = 1;
    D_800B9CFC = 1;
    D_800B9D00 = 1;
    switch (arg1) {
    case 0:
        sp1C = (void *)func_800099B0(((s32)&D_8004BA04), sp10);
        if (((s32)sp1C) == 0) {
            return -3;
        }
        break;
    case 1:
        sp1C = (void *)func_800099B0(((s32)&D_8004B9FC), sp10);
        if (((s32)sp1C) == 0) {
            return -2;
        }
        break;
    default:
        sp1C = (void *)func_800099B0(((s32)&D_8004B9FC), sp10);
        if (((s32)sp1C) != 0) {
            arg1 = 1;
        } else {
            arg1 = 0;
        }
        break;
    }
    sp1C = (void *)func_800099B0(((s32)&D_800B966A), sp10);
    if (((s32)sp1C) == 0) {
        return -1;
    }
    D_800B966A[((s32)sp1C) - ((s32)&D_800B966A)].m0 = 32;
    sp18 = 0;
    sp14 = 0;
    for (;;) {
        if (sp14 >= 4) {
            break;
        }
        sp1C = (void *)&((struct n64dk_e21 *)&D_800B9601)[sp14];
        for (;;) {
            if (((s32)sp1C) == 0) {
                break;
            }
            sp1C = (void *)func_800099B0(((s32)sp1C), sp10);
            if (((s32)sp1C) != 0) {
                sp18++;
                sp1C++;
            }
        }
        sp14++;
    }
    if (D_800BCA00 != 0) {
        if (arg1 == 0) {
            D_800B9990[D_800FB808].m0 = D_800B9990[D_800FB808].m0 + (D_800B953C * sp18);
        }
        return sp18;
    }
    if ((sp18 > 0) && (arg1 == 0)) {
        if (func_8000928C() > 0) {
            if (func_8000928C() == 0x2710) {
                D_800B9990[D_800FB808].mF8 = D_800B9990[D_800FB808].mF8 + 0x2710;
                D_800B9538 = 1;
                D_800B9990[D_800FB808].mC = 1;
                func_80008F64();
            } else {
                D_800B9990[D_800FB808].m0 = D_800B9990[D_800FB808].m0 + (func_8000928C() * sp18);
            }
            goto L266;
        }
    }
    if (arg1 != 0) {
        D_800B9990[D_800FB808].m0 = D_800B9990[D_800FB808].m0 - 250;
    } else {
        if (sp18 > 0) {
            if (arg1 == 0) {
                if (func_8000928C() < -4) {
                    D_800B9990[D_800FB808].m8 = 1;
                    func_80008F64();
L266: ;
                }
            }
        }
    }
    return sp18;
}
