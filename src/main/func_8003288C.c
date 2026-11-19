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
struct gd_C_s32 { u8 pad[0xC]; s32 v; };
struct gd_10_s16 { u8 pad[0x10]; s16 v; };
struct gd_14_s32 { u8 pad[0x14]; s32 v; };
struct gd_18_s32 { u8 pad[0x18]; s32 v; };
struct gd_1C_s32 { u8 pad[0x1C]; s32 v; };
struct gd_20_s32 { u8 pad[0x20]; s32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct n64dk_a8005C7F8 { s32 m0; s32 m4; s32 m8; s32 mC; s32 m10; u8 pad14[0x10]; };
extern struct n64dk_a8005C7F8 D_8005C7F8[];
extern s32 D_800019E4;
extern s32 func_80030B5C;
extern s32 func_80031A54;
extern u16 D_800B998A;
s32 func_80009F38();
s32 func_8000A56C();
s32 func_8000AE70();
s32 func_8000B6FC();
s32 func_80015848();

s32 func_8003288C(s32 arg0, s32 arg1) {
    s32 sp10;
    s32 sp14;
    s32 sp18;

    sp18 = arg0;
    if (arg0 < 0) {
        return;
    }
    if (arg0 == 80) {
        arg0 = 2;
    } else {
        if (arg0 >= 6) {
            func_80009F38(((s32)&D_800019E4));
        }
    }
    if (D_8005C7F8[arg0].m10 == 0) {
        return 0;
    }
    if (arg1 != 0) {
        func_8000AE70(0xA000400, -1, 1);
        func_8000B6FC(0xA030000, -1);
    }
    sp10 = func_8000A56C(((s32)&func_80031A54), 0xA000400);
    sp14 = func_80015848(sp10, 0, ((s32)&func_80030B5C), 0xA030000);
    ((struct gd_10_s16 *)sp14)->v = D_800B998A;
    ((struct gd_C_s32 *)((struct gd_30_s32 *)sp10)->v)->v = sp18;
    ((struct gd_8_s32 *)((struct gd_30_s32 *)sp10)->v)->v = D_8005C7F8[arg0].m10;
    ((struct gd_18_s32 *)((struct gd_30_s32 *)sp10)->v)->v = D_8005C7F8[arg0].m0;
    ((struct gd_14_s32 *)((struct gd_30_s32 *)sp10)->v)->v = D_8005C7F8[arg0].m4;
    ((struct gd_1C_s32 *)((struct gd_30_s32 *)sp10)->v)->v = D_8005C7F8[arg0].m8;
    ((struct gd_20_s32 *)((struct gd_30_s32 *)sp10)->v)->v = D_8005C7F8[arg0].mC;
    (*(s32 *)((struct gd_30_s32 *)sp10)->v) = sp14;
    return sp10;
}
