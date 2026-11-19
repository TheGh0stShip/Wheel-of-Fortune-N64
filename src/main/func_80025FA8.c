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

struct n64dk_a800584A0 { s32 m0; s32 m4; };
extern struct n64dk_a800584A0 D_800584A0[];
struct n64dk_a800584E0 { s32 m0; u8 pad4[0x1C]; };
extern struct n64dk_a800584E0 D_800584E0[];
struct n64dk_a80058548 { s32 m0; s32 m4; u8 pad8[0x18]; s32 m20; s32 m24; };
extern struct n64dk_a80058548 D_80058548[];
extern s32 D_01157868;
extern s32 D_01158068;
extern s32 D_01158868;
extern s32 D_01159068;
extern s32 D_01159868;
extern s32 D_0115B068;
extern s32 D_0115B868;
extern s32 D_0115C068;
extern s32 D_0115C868;
extern s32 D_0115D068;
extern s32 func_80021E88;
extern s32 func_800232AC;
extern s32 D_80058638;
extern s32 D_8005863C;
extern u8 D_800B96C4;
s32 func_8000A56C();
s32 func_800258BC();
s32 func_80027218();

void func_80025FA8(void) {
    s32 sp10;
    s32 sp14;
    s32 pad0;
    s32 sp1C;

    sp1C = func_8000A56C(((s32)&func_800232AC), 0x5000000);
    func_80027218(sp1C, 0, ((s32)&func_80021E88), 0x5000000);
    func_800258BC();
    sp14 = 0;
    sp10 = 2;
    for (;;) {
        if (sp10 >= 6) {
            break;
        }
        if (((D_800B96C4 >> (sp10 - 2)) % 2) != 0) {
            D_80058548[sp10].m0 = D_800584A0[sp14].m0;
            D_80058548[sp10].m4 = D_800584A0[sp14].m4;
            sp14++;
        }
        sp10++;
    }
    D_80058638 = D_800584A0[sp14].m0;
    D_8005863C = D_800584A0[sp14].m4;
    sp10 = 0;
    for (;;) {
        if (sp10 >= 3) {
            return;
        }
        switch (D_800584E0[sp10].m0) {
        case 0:
            D_80058548[(sp10 * 4) + 10].m20 = (s32)&D_01158068;
            D_80058548[(sp10 * 4) + 10].m24 = (s32)&D_0115B868;
            break;
        case 1:
            D_80058548[(sp10 * 4) + 10].m20 = (s32)&D_01158868;
            D_80058548[(sp10 * 4) + 10].m24 = (s32)&D_0115C068;
            break;
        case 2:
            D_80058548[(sp10 * 4) + 10].m20 = (s32)&D_01159068;
            D_80058548[(sp10 * 4) + 10].m24 = (s32)&D_0115C868;
            break;
        case 3:
            D_80058548[(sp10 * 4) + 10].m20 = (s32)&D_01159868;
            D_80058548[(sp10 * 4) + 10].m24 = (s32)&D_0115D068;
            break;
        case 4:
            D_80058548[(sp10 * 4) + 10].m20 = (s32)&D_01157868;
            D_80058548[(sp10 * 4) + 10].m24 = (s32)&D_0115B068;
            break;
        }
        sp10++;
    }
}
