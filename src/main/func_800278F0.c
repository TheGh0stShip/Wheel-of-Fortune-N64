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

struct gd_4_s32 { u8 pad[0x4]; s32 v; };
struct n64dk_e8 { u8 b[8]; };
struct n64dk_a8005A9B8 { s32 m0; u8 pad4[0x24]; };
extern struct n64dk_a8005A9B8 D_8005A9B8[];
struct n64dk_a800B9998 { s32 m0; s32 m4; u8 pad8[0x10C]; };
extern struct n64dk_a800B9998 D_800B9998[];
extern s32 D_01021970;
extern s32 D_8005A4B8;
extern s32 D_8005A5A8;
extern s32 D_8005A7B0;
extern s32 D_8005A828;
extern s32 D_8005A8C8;
extern s32 D_8005A930;
extern s32 D_8005A998;
extern s32 D_8005ADD0;
extern s32 D_8005B360;
extern s32 D_8005B4C8;
extern s32 D_8005B630;
extern s32 D_8005B710;
extern s32 D_800B40C4;
extern s32 D_800B619C;
extern struct n64dk_e8 *D_800B81E8;
extern s32 D_800B966A;
extern s32 D_800BA2BC;
extern s32 D_800BCA28;
s32 func_800278A8();

void func_800278F0(s32 arg0, s32 arg1) {
    s32 pad0[2];
    s32 sp18;
    s32 sp1C;
    s32 sp20;

    sp20 = (s32)D_800B81E8++;
    (*(s32 *)sp20) = 0xE7000000;
    ((struct gd_4_s32 *)sp20)->v = 0;
    sp20 = (s32)D_800B81E8++;
    (*(s32 *)sp20) = 0x6000000;
    ((struct gd_4_s32 *)sp20)->v = (s32)&D_01021970;
    sp20 = (s32)D_800B81E8++;
    (*(s32 *)sp20) = 0xBA001402;
    ((struct gd_4_s32 *)sp20)->v = 0x200000;
    sp18 = 2;
    for (;;) {
        if (sp18 < 0) {
            break;
        }
        sp1C = 0;
        for (;;) {
            if (sp1C >= 2) {
                break;
            }
            func_800278A8(((((s32)&D_8005A4B8) + (sp18 * 80)) + (sp1C * 40)), 1);
            sp1C++;
        }
        sp18--;
    }
    sp18 = 0;
    for (;;) {
        if (sp18 >= 3) {
            break;
        }
        sp1C = 0;
        for (;;) {
            if (sp1C >= 7) {
                break;
            }
            func_800278A8(((((s32)&D_8005ADD0) + (sp18 * 280)) + (sp1C * 40)), 1);
            sp1C++;
        }
        sp18++;
    }
    if ((D_800B619C == 2) && ((D_800B40C4 != 0) || (D_800BCA28 == 22))) {
        switch (D_800BA2BC) {
        case 3:
        case 18:
            sp1C = 0;
            for (;;) {
                if (sp1C >= 3) {
                    break;
                }
                func_800278A8(((sp1C * 40) + ((s32)&D_8005B630)), 1);
                sp1C++;
            }
            sp1C = 0;
            for (;;) {
                if (sp1C >= 9) {
                    break;
                }
                func_800278A8(((sp1C * 40) + ((s32)&D_8005B4C8)), 1);
                func_800278A8(((sp1C * 40) + ((s32)&D_8005B360)), 1);
                sp1C++;
            }
        }
    }
    sp18 = 0;
    for (;;) {
        if (sp18 >= 26) {
            break;
        }
        if ((*(u8 *)(sp18 + ((s32)&D_800B966A))) == 32) {
            D_8005A9B8[sp18].m0 = *(s32 *)((sp18 * 4) + ((s32)&D_8005A8C8));
        } else {
            D_8005A9B8[sp18].m0 = *(s32 *)((sp18 * 4) + ((s32)&D_8005A930));
        }
        func_800278A8(((sp18 * 40) + ((s32)&D_8005A998)), 1);
        sp18++;
    }
    sp18 = 0;
    for (;;) {
        if (sp18 >= 4) {
            break;
        }
        func_800278A8(((sp18 * 40) + ((s32)&D_8005A828)), 1);
        sp18++;
    }
    sp18 = 0;
    for (;;) {
        if (sp18 >= 3) {
            break;
        }
        if (D_800B9998[sp18].m0 != 0) {
            func_800278A8(((sp18 * 40) + ((s32)&D_8005A7B0)), 1);
        }
        if (D_800B9998[sp18].m4 != 0) {
            func_800278A8(((sp18 * 40) + ((s32)&D_8005A5A8)), 1);
        }
        sp18++;
    }
    sp18 = 0;
    for (;;) {
        if (sp18 >= 22) {
            return;
        }
        func_800278A8(((sp18 * 40) + ((s32)&D_8005B710)), 1);
        sp18++;
    }
}
