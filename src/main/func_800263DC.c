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

struct n64dk_a800584E0 { s32 m0; u8 pad4[0x1C]; };
extern struct n64dk_a800584E0 D_800584E0[];
struct n64dk_a800588A8 { s32 m0; s32 m4; s32 m8; s32 mC; s32 m10; s32 m14; };
extern struct n64dk_a800588A8 D_800588A8[];
struct n64dk_a8005A39C { s32 m0; s32 m4; s32 m8; };
extern struct n64dk_a8005A39C D_8005A39C[];
struct n64dk_a800B99A4 { s32 m0; s32 m4; u8 pad8[0x10C]; };
extern struct n64dk_a800B99A4 D_800B99A4[];
extern s32 D_01157868;
extern s32 D_01158068;
extern s32 D_01158868;
extern s32 D_01159068;
extern s32 D_01159868;
extern s32 D_0115B068;
extern s32 D_0115B868;
extern s32 D_0115C068;
extern s32 D_0115C868;
extern s32 func_8002208C;
extern s32 func_80023CA4;
extern s32 D_80058880;
extern s32 D_80058910;
extern s32 D_80058914;
extern s32 D_80058A28;
extern s32 D_80058A2C;
extern s32 D_80058A50;
extern s32 D_80058A54;
extern s32 D_80058A78;
extern s32 D_80058A7C;
extern u64 D_8005A390;
extern s32 D_8005A398;
extern s32 D_800FB808;
s32 func_8000A56C();
s32 func_800258BC();
s32 func_80026800();
s32 func_80027218();
s32 func_800323C4();

void func_800263DC(void) {
    s32 sp18;
    s32 sp1C;

    sp18 = D_800FB808;
    for (;;) {
        if (D_800B99A4[sp18].m0 < 4) {
            break;
        }
        sp18++;
        if (sp18 >= 3) {
            D_800FB808 = 0;
            func_80026800();
            return;
        }
    }
    D_800FB808 = sp18;
    sp1C = func_8000A56C(((s32)&func_80023CA4), 0x5000000);
    func_80027218(sp1C, 0, ((s32)&func_8002208C), 0x5000000);
    func_800258BC();
    D_80058910 = D_800588A8[sp18].m0;
    D_80058914 = D_800588A8[sp18].m4;
    D_80058A28 = D_800588A8[sp18].m8;
    D_80058A2C = D_800588A8[sp18].mC;
    D_80058A50 = D_800588A8[sp18].m10;
    D_80058A54 = D_800588A8[sp18].m14;
    switch (D_800584E0[sp18].m0) {
    case 0:
        D_80058A78 = (s32)&D_01158068;
        D_80058A7C = (s32)&D_0115B868;
        break;
    case 1:
        D_80058A78 = (s32)&D_01158868;
        D_80058A7C = (s32)&D_0115C068;
        break;
    case 2:
        D_80058A78 = (s32)&D_01159068;
        D_80058A7C = (s32)&D_0115C868;
        break;
    case 3:
        D_80058A78 = (s32)&D_01159868;
        D_80058A7C = (s32)&D_01159868;
        break;
    case 4:
        D_80058A78 = (s32)&D_01157868;
        D_80058A7C = (s32)&D_0115B068;
        break;
    }
    D_80058880 = D_800B99A4[D_800FB808].m4;
    sp18 = 0;
    for (;;) {
        if (sp18 >= 6) {
            return;
        }
        if (sp18 == D_80058880) {
            func_800323C4(sp18, sp18, D_8005A390, D_8005A398);
        } else {
            func_800323C4(sp18, sp18, D_8005A39C[sp18].m0, D_8005A39C[sp18].m4, D_8005A39C[sp18].m8);
        }
        sp18++;
    }
}
