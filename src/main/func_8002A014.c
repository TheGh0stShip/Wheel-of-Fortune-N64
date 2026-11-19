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

struct n64dk_a8005B360 { s32 m0; u8 pad4[0x4]; s32 m8; u8 padC[0x14]; s32 m20; u8 pad24[0x4]; };
extern struct n64dk_a8005B360 D_8005B360[];
struct n64dk_a8005B4C8 { s32 m0; s32 m4; s32 m8; s32 mC; u8 pad10[0x10]; s32 m20; u8 pad24[0x4]; };
extern struct n64dk_a8005B4C8 D_8005B4C8[];
extern s32 func_80029C98;
extern s32 D_8005B088;
extern s32 D_8005B118;
extern s32 D_8005B148;
extern s32 D_8005B170;
extern s32 D_8005B174;
extern s32 D_8005B178;
extern s32 D_800B619C;
extern s32 D_800B9540;
extern s32 D_800B9CEC;
s32 func_80009A74();
s32 func_80009AE0();
s32 func_8000A4A4();
s32 func_8000A56C();
s32 func_8000A990();

void func_8002A014(void) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp28[6];
    s32 sp40;

    switch (D_800B619C) {
    case 2:
        if (D_800B9CEC == D_800B9540) {
            return;
        }
        sp14 = 0;
        for (;;) {
            if (sp14 >= 9) {
                break;
            }
            D_8005B360[sp14].m0 = D_8005B4C8[sp14].m0;
            D_8005B360[sp14].m8 = D_8005B4C8[sp14].m8;
            D_8005B360[sp14].m20 = D_8005B4C8[sp14].m20;
            sp14++;
        }
        sp14 = 0;
        for (;;) {
            if (sp14 >= 9) {
                break;
            }
            D_8005B4C8[sp14].m20 = 0;
            sp14++;
        }
        sp1C = D_800B9540;
        func_80009AE0(((s32)&sp28), sp1C);
        sp18 = func_80009A74(((s32)&sp28));
        if (sp18 >= 7) {
            sp18 = 6;
        }
        sp1C = 0;
        sp14 = 0;
        for (;;) {
            if (sp14 >= sp18) {
                break;
            }
            sp1C = sp1C + (*(s32 *)(((*(u8 *)(((s32)&sp28) + sp14)) * 4) + ((s32)&D_8005B088)));
            sp14++;
        }
        sp1C = sp1C + D_8005B170;
        sp1C = sp1C + D_8005B174;
        sp1C = sp1C / 2;
        sp1C = 58 - sp1C;
        sp20 = 0;
        sp14 = 0;
        for (;;) {
            if (sp14 >= (sp18 + 2)) {
                break;
            }
            if (sp14 == 0) {
                sp10 = 10;
            } else {
                if (sp14 == (sp18 - 2)) {
                    sp10 = 11;
                } else {
                    sp10 = (*(u8 *)(((s32)&sp28) + (sp20++))) - 48;
                }
            }
            D_8005B4C8[sp14].m0 = sp1C;
            D_8005B4C8[sp14].m8 = *(s32 *)((sp10 * 4) + ((s32)&D_8005B178));
            D_8005B4C8[sp14].m20 = *(s32 *)((sp10 * 4) + ((s32)&D_8005B118));
            sp1C = sp1C + (*(s32 *)((sp10 * 4) + ((s32)&D_8005B148)));
            sp14++;
        }
        if (D_800B9CEC != 0) {
            sp40 = func_8000A990(0x6030000, -1);
            if (sp40 != 0) {
                func_8000A4A4(sp40, 0);
            }
            func_8000A56C(((s32)&func_80029C98), 0x6030000);
        } else {
            sp14 = 0;
            for (;;) {
                if (sp14 >= 9) {
                    break;
                }
                D_8005B360[sp14].m20 = 0;
                D_8005B4C8[sp14].m4 = 45;
                D_8005B4C8[sp14].mC = 15;
                sp14++;
            }
        }
        D_800B9CEC = D_800B9540;
    }
}
