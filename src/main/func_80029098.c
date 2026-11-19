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
struct gd_4_s32 { u8 pad[0x4]; s32 v; };
struct gd_10_s16 { u8 pad[0x10]; s16 v; };
struct gd_12_s16 { u8 pad[0x12]; s16 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct gd_44_s32 { u8 pad[0x44]; s32 v; };
struct n64dk_a8005B712 { u16 m0; u8 pad2[0x2]; u16 m4; u8 pad6[0x22]; };
extern struct n64dk_a8005B712 D_8005B712[];
struct n64dk_a8005B730 { s32 m0; s32 m4; u8 pad8[0x20]; };
extern struct n64dk_a8005B730 D_8005B730[];
extern s32 D_8005BA80;
extern s32 D_800B619C;
extern s32 D_800B96A8;
extern s32 D_800B96B4;
extern s32 D_800B96C0;
extern s32 D_800FB808;
s32 func_80002CE0();
s32 func_8000AAB0();
s32 func_8000ACE8();
s32 func_80016B9C();
s32 func_80032AD4();
s32 func_80032B80();

struct n64dk_r12 func_80029098(s32 arg1) {
    s32 sp10;
    s32 sp14;
    struct n64dk_r12 sp18;
    s32 sp28;

    sp18.w[1] = 1;
    sp18.w[0] = 0;
    sp28 = *(s32 *)((struct gd_30_s32 *)arg1)->v;
    for (;;) {
        sp10 = func_8000ACE8(arg1);
        if (sp10 == 0) {
            break;
        }
        switch (sp10) {
        case 8:
            if (D_800B619C < D_800B96C0) {
                func_80032B80();
            }
            func_80032AD4(2);
            ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v = 0;
            break;
        case 6:
            if (D_800B619C == 6) {
                func_80032AD4(80);
            } else {
                func_80016B9C(17);
                D_800B96A8++;
            }
            sp18.w[1] = 0;
            sp18.w[0] = 1;
            return sp18;
        }
    }
    sp14 = ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v;
    if ((D_8005B730[sp14].m4 == 0) || (sp14 >= 22)) {
        if (D_800B619C != 6) {
            func_80002CE0((D_800FB808 + 139));
        }
        func_8000AAB0(arg1, 6, 0);
        sp18.w[1] = 1;
        sp18.w[0] = 20 / D_800B96B4;
        return sp18;
    }
    ((struct gd_10_s16 *)sp28)->v = D_8005B712[sp14].m0;
    ((struct gd_12_s16 *)sp28)->v = D_8005B712[sp14].m4 - 4;
    D_8005B730[sp14].m0 = D_8005B730[sp14].m4;
    if (sp14 >= 16) {
        sp14 = sp14 % 16;
    }
    ((struct gd_44_s32 *)sp28)->v = *(s32 *)((sp14 * 4) + ((s32)&D_8005BA80));
    ((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v++;
    return sp18;
}
