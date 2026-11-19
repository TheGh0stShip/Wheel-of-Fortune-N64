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

struct gd_4_s32 { u8 pad[0x4]; s32 v; };
struct gd_8_s32 { u8 pad[0x8]; s32 v; };
struct gd_10_s16 { u8 pad[0x10]; s16 v; };
struct gd_12_s16 { u8 pad[0x12]; s16 v; };
struct gd_14_s16 { u8 pad[0x14]; s16 v; };
struct gd_18_s32 { u8 pad[0x18]; s32 v; };
struct gd_1C_s32 { u8 pad[0x1C]; s32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct gd_4C_s32 { u8 pad[0x4C]; s32 v; };
struct n64dk_a8005C720 { s32 m0; u8 pad4[0x4]; s32 m8; u8 padC[0x4]; s32 m10; u8 pad14[0x10]; };
extern struct n64dk_a8005C720 D_8005C720[];
extern s32 D_0113A9B0;
extern s32 D_0113A9D0;
extern s32 D_80001974;
extern s32 func_80030490;
extern s32 func_800315FC;
s32 func_80009F38();
s32 func_8000A4A4();
s32 func_8000A56C();
s32 func_8000A990();
s32 func_80015848();

void func_800323C4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp10;
    s32 sp14;

    if (arg0 < 0) {
        return;
    }
    if (arg0 >= 6) {
        func_80009F38(((s32)&D_80001974));
    }
    if (D_8005C720[arg0].m10 == 0) {
        return;
    }
    sp10 = func_8000A990((arg1 | 0xA000300), -1);
    if (sp10 != 0) {
        func_8000A4A4(sp10, 0);
    }
    sp10 = func_8000A56C(((s32)&func_800315FC), (arg1 | 0xA000300));
    sp14 = func_80015848(sp10, ((s32)&D_0113A9B0), ((s32)&func_80030490), (arg1 | 0xA020000));
    ((struct gd_4C_s32 *)sp14)->v = (s32)&D_0113A9D0;
    ((struct gd_10_s16 *)sp14)->v = arg2;
    ((struct gd_12_s16 *)sp14)->v = arg3;
    ((struct gd_14_s16 *)sp14)->v = arg4;
    ((struct gd_4_s32 *)((struct gd_30_s32 *)sp10)->v)->v = arg1;
    ((struct gd_8_s32 *)((struct gd_30_s32 *)sp10)->v)->v = D_8005C720[arg0].m10;
    ((struct gd_18_s32 *)((struct gd_30_s32 *)sp10)->v)->v = D_8005C720[arg0].m0;
    ((struct gd_1C_s32 *)((struct gd_30_s32 *)sp10)->v)->v = D_8005C720[arg0].m8;
    (*(s32 *)((struct gd_30_s32 *)sp10)->v) = sp14;
}
