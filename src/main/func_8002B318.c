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

struct n64dk_r12 { s32 w[3]; };
struct gd_8_s32 { u8 pad[0x8]; s32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct n64dk_a8005B730 { s32 m0; s32 m4; u8 pad8[0x20]; };
extern struct n64dk_a8005B730 D_8005B730[];
extern s32 func_80028064;
extern s32 D_8005C1E8;
extern s32 D_8005C33C;
extern s32 D_800B9544;
extern s32 D_800B96B4;
extern s32 D_800BCD54;
s32 func_80002CE0();
s32 func_8000315C();
s32 func_80005258();
s32 func_80006E54();
s32 func_80009900();
s32 func_8000AAB0();
s32 func_8000ACE8();
s32 func_8000ADEC();
s32 func_8000AE70();
s32 func_8000AF00();
s32 func_8000B6FC();
s32 func_8000E794();
s32 func_80011B24();
s32 func_800161A8();
s32 func_80021E28();
s32 func_80027218();
s32 func_80029440();

struct n64dk_r12 func_8002B318(s32 arg1) {
    s32 sp10;
    s32 sp14;
    struct n64dk_r12 sp18;
    s8 pad0;

    sp18.w[1] = 1;
    sp18.w[0] = 0;
    for (;;) {
        sp10 = func_8000ACE8(arg1);
        if (sp10 == 0) {
            break;
        }
        switch (sp10) {
        case 8:
            sp14 = 0;
            for (;;) {
                if (sp14 >= 22) {
                    break;
                }
                D_8005B730[sp14].m0 = 0;
                D_8005B730[sp14].m4 = 0;
                sp14++;
            }
            func_80005258();
            func_80027218(0, 0, ((s32)&func_80028064), 0x5050000);
            ((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 0;
            D_800BCD54 = 8;
            func_8000B6FC(0x5050100, -1);
            func_8000AE70(0xA000400, -1, 1);
            func_8000B6FC(0xA030000, -1);
            func_80002CE0(21);
            break;
        case 46:
            func_8000315C();
            sp18.w[1] = 1;
            sp18.w[0] = 2;
            func_8000B6FC(0x1000000, 0xFF000000);
            func_8000B6FC(0xA000000, 0xFF000000);
            func_8000B6FC(0x4000000, 0xFF000000);
            func_8000AAB0(arg1, 35, 0);
            return sp18;
        case 35:
            func_8000ADEC(arg1);
            func_8000AF00();
            func_80021E28();
            func_8000E794();
            sp18.w[1] = 0;
            sp18.w[0] = 0;
            return sp18;
        }
    }
    if (((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v >= 22) {
        func_8000AAB0(arg1, 46, 0);
        return sp18;
    }
    func_800161A8();
    func_80006E54(0, (*(s32 *)((((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v * 4) + ((s32)&D_8005C1E8))));
    if ((*(s32 *)((((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v * 4) + ((s32)&D_8005C33C))) != 0) {
        func_80009900(((s32)&D_800B9544), (*(s32 *)((((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v * 4) + ((s32)&D_8005C33C))));
        func_80029440();
    }
    func_80011B24();
    ((struct gd_8_s32 *)((struct gd_30_s32 *)arg1)->v)->v++;
    sp18.w[0] = 65 / D_800B96B4;
    return sp18;
}
