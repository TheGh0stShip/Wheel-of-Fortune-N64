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


void func_80095664(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    s32 sp0;
    s32 sp4;
    s32 sp8;
    s32 spC;

    arg0 = arg0 + ((((arg2 + arg6) * arg4) + arg3) + arg5);
    if (arg9 == 16) {
        if ((arg7 == 0) && (arg8 == 0)) {
            if ((arg5 & 1) != 0) {
                sp0 = 0;
                for (;;) {
                    if (sp0 >= 16) {
                        break;
                    }
                    (*(s8 *)arg1) = *(u8 *)arg0;
                    (*(s8 *)(arg1 + 1)) = *(u8 *)(arg0 + 1);
                    (*(s8 *)(arg1 + 2)) = *(u8 *)(arg0 + 2);
                    (*(s8 *)(arg1 + 3)) = *(u8 *)(arg0 + 3);
                    (*(s8 *)(arg1 + 4)) = *(u8 *)(arg0 + 4);
                    (*(s8 *)(arg1 + 5)) = *(u8 *)(arg0 + 5);
                    (*(s8 *)(arg1 + 6)) = *(u8 *)(arg0 + 6);
                    (*(s8 *)(arg1 + 7)) = *(u8 *)(arg0 + 7);
                    (*(s8 *)(arg1 + 8)) = *(u8 *)(arg0 + 8);
                    (*(s8 *)(arg1 + 9)) = *(u8 *)(arg0 + 9);
                    (*(s8 *)(arg1 + 10)) = *(u8 *)(arg0 + 10);
                    (*(s8 *)(arg1 + 11)) = *(u8 *)(arg0 + 11);
                    (*(s8 *)(arg1 + 12)) = *(u8 *)(arg0 + 12);
                    (*(s8 *)(arg1 + 13)) = *(u8 *)(arg0 + 13);
                    (*(s8 *)(arg1 + 14)) = *(u8 *)(arg0 + 14);
                    (*(s8 *)(arg1 + 15)) = *(u8 *)(arg0 + 15);
                    arg1 = arg1 + 16;
                    arg0 = arg0 + arg4;
                    sp0++;
                }
            } else {
                if ((arg5 & 2) != 0) {
                    sp8 = arg0;
                    spC = arg1;
                    arg4 = arg4 >> 1;
                    sp0 = 0;
                    for (;;) {
                        if (sp0 >= 16) {
                            break;
                        }
                        (*(s16 *)spC) = *(u16 *)sp8;
                        (*(s16 *)(spC + 2)) = *(u16 *)(sp8 + 2);
                        (*(s16 *)(spC + 4)) = *(u16 *)(sp8 + 4);
                        (*(s16 *)(spC + 6)) = *(u16 *)(sp8 + 6);
                        (*(s16 *)(spC + 8)) = *(u16 *)(sp8 + 8);
                        (*(s16 *)(spC + 10)) = *(u16 *)(sp8 + 10);
                        (*(s16 *)(spC + 12)) = *(u16 *)(sp8 + 12);
                        (*(s16 *)(spC + 14)) = *(u16 *)(sp8 + 14);
                        spC = spC + 16;
                        sp8 = sp8 + (arg4 * 2);
                        sp0++;
                    }
                } else {
                    spC = arg0;
                    sp8 = arg1;
                    arg4 = arg4 >> 2;
                    sp0 = 0;
                    for (;;) {
                        if (sp0 >= 16) {
                            break;
                        }
                        (*(s32 *)sp8) = *(s32 *)spC;
                        (*(s32 *)(sp8 + 4)) = *(s32 *)(spC + 4);
                        (*(s32 *)(sp8 + 8)) = *(s32 *)(spC + 8);
                        (*(s32 *)(sp8 + 12)) = *(s32 *)(spC + 12);
                        sp8 = sp8 + 16;
                        spC = spC + (arg4 * 4);
                        sp0++;
                    }
                }
            }
        } else {
            sp4 = (arg0 + arg7) + (arg4 * arg8);
            sp0 = 0;
            for (;;) {
                if (sp0 >= arg9) {
                    break;
                }
                (*(s8 *)arg1) = ((*(u8 *)arg0) + (*(u8 *)sp4)) >> 1;
                (*(s8 *)(arg1 + 1)) = ((*(u8 *)(arg0 + 1)) + (*(u8 *)(sp4 + 1))) >> 1;
                (*(s8 *)(arg1 + 2)) = ((*(u8 *)(arg0 + 2)) + (*(u8 *)(sp4 + 2))) >> 1;
                (*(s8 *)(arg1 + 3)) = ((*(u8 *)(arg0 + 3)) + (*(u8 *)(sp4 + 3))) >> 1;
                (*(s8 *)(arg1 + 4)) = ((*(u8 *)(arg0 + 4)) + (*(u8 *)(sp4 + 4))) >> 1;
                (*(s8 *)(arg1 + 5)) = ((*(u8 *)(arg0 + 5)) + (*(u8 *)(sp4 + 5))) >> 1;
                (*(s8 *)(arg1 + 6)) = ((*(u8 *)(arg0 + 6)) + (*(u8 *)(sp4 + 6))) >> 1;
                (*(s8 *)(arg1 + 7)) = ((*(u8 *)(arg0 + 7)) + (*(u8 *)(sp4 + 7))) >> 1;
                (*(s8 *)(arg1 + 8)) = ((*(u8 *)(arg0 + 8)) + (*(u8 *)(sp4 + 8))) >> 1;
                (*(s8 *)(arg1 + 9)) = ((*(u8 *)(arg0 + 9)) + (*(u8 *)(sp4 + 9))) >> 1;
                (*(s8 *)(arg1 + 10)) = ((*(u8 *)(arg0 + 10)) + (*(u8 *)(sp4 + 10))) >> 1;
                (*(s8 *)(arg1 + 11)) = ((*(u8 *)(arg0 + 11)) + (*(u8 *)(sp4 + 11))) >> 1;
                (*(s8 *)(arg1 + 12)) = ((*(u8 *)(arg0 + 12)) + (*(u8 *)(sp4 + 12))) >> 1;
                (*(s8 *)(arg1 + 13)) = ((*(u8 *)(arg0 + 13)) + (*(u8 *)(sp4 + 13))) >> 1;
                (*(s8 *)(arg1 + 14)) = ((*(u8 *)(arg0 + 14)) + (*(u8 *)(sp4 + 14))) >> 1;
                (*(s8 *)(arg1 + 15)) = ((*(u8 *)(arg0 + 15)) + (*(u8 *)(sp4 + 15))) >> 1;
                arg1 = arg1 + arg9;
                arg0 = arg0 + arg4;
                sp4 = sp4 + arg4;
                sp0++;
            }
        }
        return;
    }
    if ((arg7 == 0) && (arg8 == 0)) {
        if ((arg5 & 1) != 0) {
            sp0 = 0;
            for (;;) {
                if (sp0 >= arg9) {
                    break;
                }
                (*(s8 *)arg1) = *(u8 *)arg0;
                (*(s8 *)(arg1 + 1)) = *(u8 *)(arg0 + 1);
                (*(s8 *)(arg1 + 2)) = *(u8 *)(arg0 + 2);
                (*(s8 *)(arg1 + 3)) = *(u8 *)(arg0 + 3);
                (*(s8 *)(arg1 + 4)) = *(u8 *)(arg0 + 4);
                (*(s8 *)(arg1 + 5)) = *(u8 *)(arg0 + 5);
                (*(s8 *)(arg1 + 6)) = *(u8 *)(arg0 + 6);
                (*(s8 *)(arg1 + 7)) = *(u8 *)(arg0 + 7);
                arg1 = arg1 + 8;
                arg0 = arg0 + arg4;
                sp0++;
            }
        } else {
            if ((arg5 & 2) != 0) {
                spC = arg1;
                sp8 = arg0;
                arg4 = arg4 >> 1;
                sp0 = 0;
                for (;;) {
                    if (sp0 >= arg9) {
                        break;
                    }
                    (*(s16 *)spC) = *(u16 *)sp8;
                    (*(s16 *)(spC + 2)) = *(u16 *)(sp8 + 2);
                    (*(s16 *)(spC + 4)) = *(u16 *)(sp8 + 4);
                    (*(s16 *)(spC + 6)) = *(u16 *)(sp8 + 6);
                    spC = spC + 8;
                    sp8 = sp8 + (arg4 * 2);
                    sp0++;
                }
            } else {
                spC = arg1;
                sp8 = arg0;
                arg4 = arg4 >> 2;
                sp0 = 0;
                for (;;) {
                    if (sp0 >= arg9) {
                        break;
                    }
                    (*(s32 *)spC) = *(s32 *)sp8;
                    (*(s32 *)(spC + 4)) = *(s32 *)(sp8 + 4);
                    spC = spC + 8;
                    sp8 = sp8 + (arg4 * 4);
                    sp0++;
                }
            }
        }
        return;
    }
    sp4 = (arg0 + arg7) + (arg4 * arg8);
    sp0 = 0;
    for (;;) {
        if (sp0 >= arg9) {
            return;
        }
        (*(s8 *)arg1) = ((*(u8 *)arg0) + (*(u8 *)sp4)) >> 1;
        (*(s8 *)(arg1 + 1)) = ((*(u8 *)(arg0 + 1)) + (*(u8 *)(sp4 + 1))) >> 1;
        (*(s8 *)(arg1 + 2)) = ((*(u8 *)(arg0 + 2)) + (*(u8 *)(sp4 + 2))) >> 1;
        (*(s8 *)(arg1 + 3)) = ((*(u8 *)(arg0 + 3)) + (*(u8 *)(sp4 + 3))) >> 1;
        (*(s8 *)(arg1 + 4)) = ((*(u8 *)(arg0 + 4)) + (*(u8 *)(sp4 + 4))) >> 1;
        (*(s8 *)(arg1 + 5)) = ((*(u8 *)(arg0 + 5)) + (*(u8 *)(sp4 + 5))) >> 1;
        (*(s8 *)(arg1 + 6)) = ((*(u8 *)(arg0 + 6)) + (*(u8 *)(sp4 + 6))) >> 1;
        (*(s8 *)(arg1 + 7)) = ((*(u8 *)(arg0 + 7)) + (*(u8 *)(sp4 + 7))) >> 1;
        arg1 = arg1 + arg9;
        arg0 = arg0 + arg4;
        sp4 = sp4 + arg4;
        sp0++;
    }
}
