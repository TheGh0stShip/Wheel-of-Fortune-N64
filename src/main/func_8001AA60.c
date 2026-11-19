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

struct gd_C_f32 { u8 pad[0xC]; f32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct n64dk_a800B9990 { s32 m0; u8 pad4[0x110]; };
extern struct n64dk_a800B9990 D_800B9990[];
extern f64 D_800011CC;
extern f64 D_800011D4;
extern f32 D_800011DC;
extern f32 D_800011E0;
extern f64 D_800011E4;
extern s8 D_800B61B5;
extern s32 D_800B61C0;
extern s32 D_800B6AE0;
extern s32 D_800B96A0;
extern s32 D_800B9CF8;
extern s32 D_800B9CFC;
extern s32 D_800B9D00;
extern s32 D_800FB808;
s32 func_800084E8();
f32 func_80008628();
s32 func_80009A74();
s32 func_80009C98();
s32 func_8000A990();
s32 func_8000AAB0();

void func_8001AA60(s32 arg0) {
    s32 sp10;
    s32 sp14;
    f32 sp18;
    f32 sp1C;
    f32 sp20;

    sp14 = 0;
    sp20 = func_80008628();
    sp10 = func_8000A990(0x5000000, -1);
    if (D_800B9D00 != 0) {
        if (D_800B96A0 != 0) {
            if (((f64)sp20) > D_800011CC) {
                D_800B61B5 = 50;
                func_8000AAB0(arg0, 14, 0);
                func_8000AAB0(sp10, 27, 0);
                return;
            }
        }
        if ((((f64)sp20) > D_800011D4) || (D_800B9CF8 == 0)) {
            D_800B61B5 = 50;
            func_8000AAB0(arg0, 14, 0);
            func_8000AAB0(sp10, 27, 0);
            return;
        }
    }
    if (D_800B9CF8 != 0) {
        sp1C = (f32)func_80009C98(100);
        sp1C = sp1C / D_800011DC;
        sp18 = (f32)func_80009A74(((s32)&D_800B61C0));
        sp18 = sp18 / D_800011E0;
        sp18 = (f32)(((f64)sp18) * D_800011E4);
        sp18 = sp18 + sp1C;
        switch (func_800084E8()) {
        case 4:
            if ((sp18 < ((struct gd_C_f32 *)((struct gd_30_s32 *)arg0)->v)->v) || (D_800B9990[D_800FB808].m0 < 250)) {
                D_800B61B5 = 48;
                func_8000AAB0(arg0, 12, 0);
            } else {
                D_800B61B5 = 49;
                func_8000AAB0(arg0, 13, 0);
            }
            break;
        case 3:
            D_800B61B5 = 48;
            func_8000AAB0(arg0, 12, 0);
            break;
        case 2:
            D_800B61B5 = 49;
            func_8000AAB0(arg0, 13, 0);
            break;
        }
    } else {
        if (D_800B9CFC != 0) {
            if (func_80009A74(((s32)&D_800B6AE0)) != 0) {
                D_800B61B5 = 49;
                func_8000AAB0(arg0, 13, 0);
            } else {
                D_800B61B5 = 48;
                func_8000AAB0(arg0, 12, 0);
            }
        }
    }
    func_8000AAB0(sp10, 27, 0);
}
