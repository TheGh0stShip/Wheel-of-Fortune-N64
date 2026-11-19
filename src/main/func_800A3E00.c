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

struct gd_1FC_s32 { u8 pad[0x1FC]; s32 v; };
struct gd_200_s32 { u8 pad[0x200]; s32 v; };
struct gd_204_s32 { u8 pad[0x204]; s32 v; };
struct gd_208_s32 { u8 pad[0x208]; s32 v; };
struct gd_218_s32 { u8 pad[0x218]; s32 v; };
struct gd_21C_s32 { u8 pad[0x21C]; s32 v; };
struct n64dk_e4 { u8 b[4]; };
s32 func_800A4A18();
s32 func_800A4B14();
s32 func_800A4BB4();
s32 func_800A4C04();
s32 func_800A4C28();

s32 func_800A3E00(register s32 arg0, s32 arg1) {
    u8 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    u8 sp28;
    u16 sp2A;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 sp3C;
    u8 sp40;
    s8 pad0;
    s16 pad1;
    s32 pad2;
    s32 pad3[2];
    struct n64dk_e4 *sp50;
    s32 sp54;

    sp10 = arg0;
    sp14 = arg1 + 492;
    sp18 = arg1 + 496;
    sp1C = arg1 + 488;
    sp20 = arg1 + 484;
    sp2C = 0;
    sp34 = 0;
    if (sp10 == 255) {
        if (((struct gd_1FC_s32 *)arg1)->v != 0) {
            (*(s32 *)((*(s32 *)sp20) + ((*(s32 *)sp1C) * 4))) = ((struct gd_200_s32 *)arg1)->v;
            (*(s32 *)(((*(s32 *)sp20) + ((*(s32 *)sp1C) * 4)) + 4)) = 441;
            (*(s32 *)sp1C) = (*(s32 *)sp1C) + 2;
        } else {
            (*(s32 *)((*(s32 *)sp20) + ((*(s32 *)sp1C) * 4))) = 441;
            (*(s32 *)sp1C) = (*(s32 *)sp1C) + 1;
        }
        return 1;
    } else {
        if (sp10 == 254) {
            ((struct gd_1FC_s32 *)arg1)->v = 0;
            ((struct gd_200_s32 *)arg1)->v = 0;
            return 0;
        }
    }
    sp24 = func_800A4A18(((s32)&sp2A), 1, 2, ((struct gd_208_s32 *)arg1)->v);
    if (sp24 < 2) {
        return 1;
    }
    if (sp10 == ((struct gd_218_s32 *)arg1)->v) {
        goto L125;
    }
    if (sp10 == ((struct gd_21C_s32 *)arg1)->v) {
        goto L125;
    }
    switch (sp10) {
    case 190:
        break;
    case 188:
        break;
    case 189:
        break;
    case 191:
        break;
    }
    if (sp10 != ((struct gd_21C_s32 *)arg1)->v) {
        func_800A4BB4(((struct gd_208_s32 *)arg1)->v, sp2A, 1);
        return 0;
L125: ;
    }
    func_800A4A18(((s32)&sp28), 1, 1, ((struct gd_208_s32 *)arg1)->v);
    sp30 = 0;
    for (;;) {
        if (((sp28 & 128) & 255) == 0) {
            break;
        }
        sp34++;
        sp30++;
        func_800A4A18(((s32)&sp28), 1, 1, ((struct gd_208_s32 *)arg1)->v);
    }
    if ((((u32)sp28 >> 6) & 255) == 1) {
        sp30 = sp30 + 2;
        func_800A4A18(((s32)&sp28), 1, 1, ((struct gd_208_s32 *)arg1)->v);
        func_800A4A18(((s32)&sp28), 1, 1, ((struct gd_208_s32 *)arg1)->v);
    }
    if ((((u32)sp28 >> 4) & 255) == 2) {
        sp40 = sp28;
        func_800A4A18((((s32)&sp40) + 1), 1, 4, ((struct gd_208_s32 *)arg1)->v);
        func_800A4A18(((s32)&sp28), 1, 1, ((struct gd_208_s32 *)arg1)->v);
        sp30 = sp30 + 5;
    } else {
        if ((((u32)sp28 >> 4) & 255) == 3) {
            sp40 = sp28;
            func_800A4A18((((s32)&sp40) + 1), 1, 9, ((struct gd_208_s32 *)arg1)->v);
            func_800A4A18(((s32)&sp28), 1, 1, ((struct gd_208_s32 *)arg1)->v);
            sp30 = sp30 + 10;
        } else {
            func_800A4A18(((s32)&sp28), 1, 1, ((struct gd_208_s32 *)arg1)->v);
            sp30 = sp30 + 1;
        }
    }
    if ((u32)((*(s32 *)sp14) + ((*(s32 *)sp18) * 4)) < (u32)(((*(s32 *)sp20) + ((sp2A / 4) * 4)) + ((*(s32 *)sp1C) * 4))) {
        if (((*(s32 *)sp18) - (*(s32 *)sp1C)) < (sp2A / 4)) {
            sp50 = (void *)(*(s32 *)sp14);
            (*(s32 *)sp18) = (*(s32 *)sp1C) + (sp2A / 2);
            (*(s32 *)sp14) = func_800A4C28(((*(s32 *)sp18) * 4));
            if ((*(s32 *)sp14) == 0) {
                return 1;
            }
            func_800A4B14((*(s32 *)sp14), (*(s32 *)sp20), ((*(s32 *)sp1C) * 4));
            func_800A4C04(((s32)sp50));
            (*(s32 *)sp20) = *(s32 *)sp14;
        } else {
            func_800A4B14((*(s32 *)sp14), (*(s32 *)sp20), ((*(s32 *)sp1C) * 4));
            (*(s32 *)sp20) = *(s32 *)sp14;
        }
    }
    sp3C = (*(s32 *)sp1C) * 4;
    if (((struct gd_1FC_s32 *)arg1)->v != 0) {
        sp3C = sp3C + ((struct gd_1FC_s32 *)arg1)->v;
        (*(s32 *)((*(s32 *)sp20) + ((*(s32 *)sp1C) * 4))) = ((struct gd_200_s32 *)arg1)->v;
    }
    sp2C = (*(s32 *)sp20) + sp3C;
    sp38 = sp2A - sp30;
    (*(s8 *)(sp2C++)) = sp28;
    if (sp10 == ((struct gd_21C_s32 *)arg1)->v) {
        sp24 = func_800A4A18(sp2C, 1, (sp38 - 1), ((struct gd_208_s32 *)arg1)->v);
        if (sp24 != (sp38 - 1)) {
            ((struct gd_204_s32 *)arg1)->v = 1;
            return 1;
        }
        if (0) {
            sp50 = (void *)((*(s32 *)sp20) + ((*(s32 *)sp1C) * 4));
            sp54 = 0;
            for (;;) {
                if ((u32)sp54 >= (u32)((sp38 + ((struct gd_1FC_s32 *)arg1)->v) & -4)) {
                    break;
                }
                (*(s32 *)((s32)sp50)) = *(s32 *)((s32)sp50);
                sp50++;
                sp54 = sp54 + 4;
            }
        }
        sp3C = sp3C + sp38;
        ((struct gd_1FC_s32 *)arg1)->v = sp3C % 4;
        (*(s32 *)sp1C) = sp3C / 4;
        ((struct gd_200_s32 *)arg1)->v = *(s32 *)((*(s32 *)sp20) + ((*(s32 *)sp1C) * 4));
        return 2;
    } else {
        if (sp10 == ((struct gd_218_s32 *)arg1)->v) {
            sp2C = ((*(s32 *)sp20) + ((*(s32 *)sp1C) * 4)) + 4;
            func_800A4A18(sp2C, 1, (sp38 - 1), ((struct gd_208_s32 *)arg1)->v);
        } else {
            sp2C = ((*(s32 *)sp20) + ((*(s32 *)sp1C) * 4)) + 4;
            func_800A4A18(sp2C, 1, (sp38 - 1), ((struct gd_208_s32 *)arg1)->v);
        }
    }
    return 0;
}
