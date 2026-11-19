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

extern s32 D_80086D3C;
extern s32 D_80086D40;
extern f64 D_80086D48;
extern s32 D_80086D60;
extern s32 D_80087160;
extern s32 D_80087560;
extern f64 D_800883E4;
extern f64 D_800883EC;
extern f64 D_800883F4;
extern f64 D_800883FC;
extern s32 D_800FF2C8;
extern s32 D_800FF2CC;
extern s32 D_800FF2D0;
extern s32 D_800FF2D4;
extern s32 D_800FF2D8;
extern s32 D_800FF2DC;
extern s32 D_800FF2E0;
extern s32 D_800FF2E4;
extern s32 D_800FF2E8;
extern s32 D_800FF2EC;
extern s32 D_800FF2F0;
extern s32 D_80107480;
extern s32 D_80107484;
extern s32 D_80107488;
s32 func_800A19D8();
s32 func_800A1B60();
s32 func_800A4C28();

void func_800A1BE4(s32 arg0) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 pad0;
    s32 sp20;
    s32 sp24;
    s32 sp28;

    sp10 = D_80107480;
    sp14 = D_80107484;
    sp18 = D_80107488;
    D_800FF2C8 = func_800A4C28(1024);
    D_800FF2CC = func_800A4C28(1024);
    D_800FF2D0 = func_800A4C28(1024);
    D_800FF2D4 = func_800A4C28(1024);
    D_800FF2D8 = func_800A4C28(1024);
    D_800FF2E8 = func_800A4C28(3072);
    D_800FF2EC = func_800A4C28(3072);
    D_800FF2F0 = func_800A4C28(3072);
    sp28 = 0;
    for (;;) {
        if (sp28 >= 256) {
            break;
        }
        switch (D_80086D3C) {
        case 1:
            (*(s32 *)((sp28 * 4) + D_800FF2C8)) = *(s32 *)((sp28 * 4) + ((s32)&D_80086D60));
            break;
        case 2:
            (*(s32 *)((sp28 * 4) + D_800FF2C8)) = *(s32 *)((sp28 * 4) + ((s32)&D_80087560));
            break;
        case 3:
            (*(s32 *)((sp28 * 4) + D_800FF2C8)) = *(s32 *)((sp28 * 4) + ((s32)&D_80087160));
            break;
        default:
            (*(s32 *)((sp28 * 4) + D_800FF2C8)) = sp28;
        }
        sp24 = sp20 = sp28;
        if (D_80086D40 != 0) {
            sp24 = sp24 - 128;
            sp24 = (sp24 >= 0) ? ((((s32)(((f64)sp24) * D_80086D48)) >= 128) ? 127 : ((s32)(((f64)sp24) * D_80086D48))) : ((((s32)(((f64)sp24) * D_80086D48)) < -128) ? -128 : ((s32)(((f64)sp24) * D_80086D48)));
            sp20 = sp20 - 128;
            sp20 = (sp20 >= 0) ? ((((s32)(((f64)sp20) * D_80086D48)) >= 128) ? 127 : ((s32)(((f64)sp20) * D_80086D48))) : ((((s32)(((f64)sp20) * D_80086D48)) < -128) ? -128 : ((s32)(((f64)sp20) * D_80086D48)));
        } else {
            sp24 = sp24 - 128;
            sp20 = sp20 - 128;
        }
        (*(s32 *)((sp28 * 4) + D_800FF2CC)) = (s32)(((f64)sp20) * D_800883E4);
        (*(s32 *)((sp28 * 4) + D_800FF2D0)) = (s32)(((f64)sp20) * D_800883EC);
        (*(s32 *)((sp28 * 4) + D_800FF2D4)) = (s32)(((f64)sp24) * D_800883F4);
        (*(s32 *)((sp28 * 4) + D_800FF2D8)) = (s32)(((f64)sp24) * D_800883FC);
        sp28++;
    }
    sp28 = 0;
    for (;;) {
        if (sp28 >= 256) {
            break;
        }
        (*(s32 *)(((sp28 * 4) + D_800FF2E8) + 1024)) = sp28 >> (8 - func_800A19D8(sp10));
        (*(s32 *)(((sp28 * 4) + D_800FF2E8) + 1024)) = (*(s32 *)(((sp28 * 4) + D_800FF2E8) + 1024)) << func_800A1B60(sp10);
        (*(s32 *)(((sp28 * 4) + D_800FF2EC) + 1024)) = sp28 >> (8 - func_800A19D8(sp14));
        (*(s32 *)(((sp28 * 4) + D_800FF2EC) + 1024)) = (*(s32 *)(((sp28 * 4) + D_800FF2EC) + 1024)) << func_800A1B60(sp14);
        (*(s32 *)(((sp28 * 4) + D_800FF2F0) + 1024)) = sp28 >> (8 - func_800A19D8(sp18));
        (*(s32 *)(((sp28 * 4) + D_800FF2F0) + 1024)) = (*(s32 *)(((sp28 * 4) + D_800FF2F0) + 1024)) << func_800A1B60(sp18);
        if (arg0 == 0) {
            (*(s32 *)(((sp28 * 4) + D_800FF2E8) + 1024)) = (*(s32 *)(((sp28 * 4) + D_800FF2E8) + 1024)) | ((*(s32 *)(((sp28 * 4) + D_800FF2E8) + 1024)) << 16);
            (*(s32 *)(((sp28 * 4) + D_800FF2EC) + 1024)) = (*(s32 *)(((sp28 * 4) + D_800FF2EC) + 1024)) | ((*(s32 *)(((sp28 * 4) + D_800FF2EC) + 1024)) << 16);
            (*(s32 *)(((sp28 * 4) + D_800FF2F0) + 1024)) = (*(s32 *)(((sp28 * 4) + D_800FF2F0) + 1024)) | ((*(s32 *)(((sp28 * 4) + D_800FF2F0) + 1024)) << 16);
        }
        sp28++;
    }
    sp28 = 0;
    for (;;) {
        if (sp28 >= 256) {
            break;
        }
        (*(s32 *)((sp28 * 4) + D_800FF2E8)) = *(s32 *)(D_800FF2E8 + 1024);
        (*(s32 *)(((sp28 * 4) + D_800FF2E8) + 2048)) = *(s32 *)(D_800FF2E8 + 2044);
        (*(s32 *)((sp28 * 4) + D_800FF2EC)) = *(s32 *)(D_800FF2EC + 1024);
        (*(s32 *)(((sp28 * 4) + D_800FF2EC) + 2048)) = *(s32 *)(D_800FF2EC + 2044);
        (*(s32 *)((sp28 * 4) + D_800FF2F0)) = *(s32 *)(D_800FF2F0 + 1024);
        (*(s32 *)(((sp28 * 4) + D_800FF2F0) + 2048)) = *(s32 *)(D_800FF2F0 + 2044);
        sp28++;
    }
    D_800FF2DC = D_800FF2E8 + 1024;
    D_800FF2E0 = D_800FF2EC + 1024;
    D_800FF2E4 = D_800FF2F0 + 1024;
}
