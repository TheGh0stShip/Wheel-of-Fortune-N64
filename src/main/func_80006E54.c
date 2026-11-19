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
struct n64dk_a8004BB98 { s32 m0; s32 m4; s32 m8; };
extern struct n64dk_a8004BB98 D_8004BB98[];
struct n64dk_a800B9567 { s8 m0; u8 pad1[0x14]; };
extern struct n64dk_a800B9567 D_800B9567[];
struct n64dk_a800B960F { s8 m0; u8 pad1[0x14]; };
extern struct n64dk_a800B960F D_800B960F[];
struct n64dk_a800B9990 { s32 m0; u8 pad4[0x8]; s32 mC; u8 pad10[0xE8]; s32 mF8; u8 padFC[0x18]; };
extern struct n64dk_a800B9990 D_800B9990[];
extern s32 D_8004B9E0;
extern s32 D_800B61D8;
extern s8 D_800B9544;
extern s8 D_800B9559[][21];
extern u8 D_800B9601[][21];
extern s8 D_800B9655;
extern s8 D_800B966A;
extern s32 D_800BCD54;
s32 func_80006828();
s32 func_80009748();
s32 func_80009900();
s32 func_800099B0();

void func_80006E54(s32 arg0, s32 arg1) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30[26];

    sp14 = 0;
    while (!(sp14 >= 3)) {
        D_800B9990[sp14].m0 = 0;
        D_800B9990[sp14].mF8 = 0;
        D_800B9990[sp14].mC = 0;
        sp14++;
    }
    D_800B9544 = 0;
    D_800B9655 = 0;
    D_800B966A = 0;
    sp10 = 0;
    while (!(sp10 >= 4)) {
        sp14 = 0;
        while (!(sp14 >= 14)) {
            D_800B9601[sp10][sp14] = 32;
            D_800B9559[sp10][sp14] = 32;
            sp14++;
        }
        D_800B960F[sp10].m0 = 0;
        D_800B9567[sp10].m0 = 0;
        sp10++;
    }
    if (arg1 == 0) {
        func_80009900(((s32)&D_800B9544), D_8004BB98[arg0].m4);
        func_80006828(D_8004BB98[arg0].m0, ((s32)&sp30), 101);
        sp28 = (s32)&sp30;
        if (D_800BCD54 != 3) {
            D_8004BB98[arg0].m8++;
        }
        D_800B61D8 = arg0;
    } else {
        sp28 = arg1;
    }
    sp1C = 0;
    sp20 = 0;
    sp2C = sp28;
    sp10 = 0;
    while (!(sp10 >= 4)) {
        sp14 = func_800099B0(sp2C, 9) - sp2C;
        if (sp14 != 0) {
            sp20++;
            if (sp14 > sp1C) {
                sp1C = sp14;
            }
        }
        sp2C = (sp2C + 1) + sp14;
        sp10++;
    }
    sp10 = 1;
    if (sp20 >= 3) {
        sp10 = 0;
    }
    sp24 = 1;
    if (sp1C >= 14) {
        sp24 = 0;
    } else {
        sp24 = 7 - (sp1C / 2);
    }
    while (!((sp20--) <= 0)) {
        while (!((sp14 = func_800099B0(sp28, 9) - sp28) != 0)) {
            sp28++;
        }
        sp14 = func_800099B0(sp28, 9) - sp28;
        if (sp10 == 0) {
            if (sp14 >= 13) {
                if (sp20 < 3) {
                    sp10 = 1;
                }
            }
        }
        if ((sp10 == 0) || (sp10 == 3)) {
            sp18 = sp24 - 1;
        } else {
            sp18 = sp24;
        }
        if (sp18 < 0) {
            sp18 = 0;
        }
        func_80009748(((((s32)&D_800B9601) + (sp10 * 21)) + sp18), sp28, sp14);
        sp28 = (sp28 + 1) + sp14;
        sp10++;
    }
    sp14 = func_800099B0(sp28, 10) - sp28;
    func_80009748(((s32)&D_800B9655), sp28, sp14);
    (*(s8 *)(sp14 + ((s32)&D_800B9655))) = 0;
    func_80009900(((s32)&D_800B966A), ((s32)&D_8004B9E0));
    sp10 = 0;
    while (!(sp10 >= 4)) {
        sp14 = 0;
        while (!(sp14 >= 14)) {
            switch (D_800B9601[sp10][sp14]) {
            case 32:
                D_800B9559[sp10][sp14] = 32;
                break;
            case 39:
                D_800B9559[sp10][sp14] = 39;
                break;
            case 38:
                D_800B9559[sp10][sp14] = 38;
                break;
            case 46:
                D_800B9559[sp10][sp14] = 46;
                break;
            case 45:
                D_800B9559[sp10][sp14] = 45;
                break;
            case 47:
                D_800B9559[sp10][sp14] = 47;
                break;
            case 63:
                D_800B9559[sp10][sp14] = 63;
                break;
            default:
                D_800B9559[sp10][sp14] = 43;
            }
            sp14++;
        }
        sp10++;
    }
}
