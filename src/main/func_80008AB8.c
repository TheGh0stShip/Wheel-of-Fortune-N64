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

struct n64dk_a800B39B8 { s32 m0; u8 pad4[0x14]; s32 m18; s32 m1C; };
extern struct n64dk_a800B39B8 D_800B39B8[];
extern s32 D_80000798;
extern s32 D_800007A4;
extern s32 D_800007AC;
extern s32 D_800007B8;
extern s32 D_800007C4;
extern s32 D_8004B860;
extern s32 D_8004B8C0;
extern s32 D_8004B920;
extern s32 D_8004B980;
extern s32 D_800B39BC;
extern s32 D_800B619C;
extern s32 D_800B9538;
extern s32 D_800BEDA8;
s32 func_80009900();
s32 func_80009AE0();

void func_80008AB8(void) {
    s32 sp10;
    s32 sp14;

    D_800BEDA8 = 0;
    sp10 = 0;
    for (;;) {
        if (sp10 >= 24) {
            return;
        }
        switch (D_800B619C) {
        case 0:
            sp14 = *(s32 *)((sp10 * 4) + ((s32)&D_8004B860));
            break;
        case 1:
            sp14 = *(s32 *)((sp10 * 4) + ((s32)&D_8004B8C0));
            break;
        case 2:
            sp14 = *(s32 *)((sp10 * 4) + ((s32)&D_8004B920));
            break;
        default:
            sp14 = *(s32 *)((sp10 * 4) + ((s32)&D_8004B980));
        }
        D_800B39B8[sp10].m1C = 0;
        if (sp14 == -0x2710) {
            if (D_800B9538 != 0) {
                D_800B39B8[sp10].m0 = -1;
                func_80009900(((sp10 * 32) + ((s32)&D_800B39BC)), ((s32)&D_80000798));
                D_800B39B8[sp10].m18 = 0;
                D_800B39B8[sp10].m1C = 1;
            } else {
                D_800B39B8[sp10].m0 = sp14;
                func_80009900(((sp10 * 32) + ((s32)&D_800B39BC)), ((s32)&D_800007A4));
                D_800B39B8[sp10].m18 = 1;
            }
        } else {
            if (sp14 < -4) {
                D_800B39B8[sp10].m0 = sp14;
                func_80009900(((sp10 * 32) + ((s32)&D_800B39BC)), ((s32)&D_800007AC));
                D_800B39B8[sp10].m18 = 1;
            } else {
                if (sp14 == -1) {
                    D_800B39B8[sp10].m0 = -1;
                    func_80009900(((sp10 * 32) + ((s32)&D_800B39BC)), ((s32)&D_80000798));
                    D_800B39B8[sp10].m18 = 0;
                } else {
                    if (sp14 == -2) {
                        D_800B39B8[sp10].m0 = -2;
                        func_80009900(((sp10 * 32) + ((s32)&D_800B39BC)), ((s32)&D_800007B8));
                        D_800B39B8[sp10].m18 = 0;
                    } else {
                        if (sp14 == -3) {
                            D_800B39B8[sp10].m0 = -3;
                            func_80009900(((sp10 * 32) + ((s32)&D_800B39BC)), ((s32)&D_800007C4));
                            D_800B39B8[sp10].m18 = 1;
                        } else {
                            D_800B39B8[sp10].m0 = sp14;
                            func_80009AE0(((sp10 * 32) + ((s32)&D_800B39BC)), sp14);
                            D_800B39B8[sp10].m18 = 0;
                        }
                    }
                }
            }
        }
        sp10++;
    }
}
