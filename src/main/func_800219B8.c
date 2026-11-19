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

struct gd_20_s32 { u8 pad[0x20]; s32 v; };
struct gd_24_s32 { u8 pad[0x24]; s32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct n64dk_a8005822C { s32 m0; u8 pad4[0x4]; s32 m8; u8 padC[0x4]; };
extern struct n64dk_a8005822C D_8005822C[];
extern s32 func_80021548;
extern s32 D_80058488;
extern s32 D_80086D58;
extern s32 D_800B40C4;
extern s32 D_800B96A4;
extern s32 D_800BCA0C;
extern s32 D_800BCA28;
s32 func_8000A56C();
s32 func_8000B978();
s32 func_8000B9FC();
s32 func_800211E4(s32, s32, f32, f32, s32);
s32 func_80021908();
s32 func_8009CEC0();
s32 func_800A4E58();

void func_800219B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp18;
    s32 sp1C;

    if (D_80086D58 != 0) {
        func_8000B9FC(1);
        func_800A4E58(0);
    }
    D_800BCA28 = arg0;
    D_800B96A4 = 0;
    sp18 = func_8000A56C(((s32)&func_80021548), 0x5010000);
    (*(s32 *)((struct gd_30_s32 *)sp18)->v) = func_800211E4(sp18, ((s32)&D_80058488), ((f32)arg2), ((f32)arg3), arg0);
    ((struct gd_24_s32 *)((struct gd_30_s32 *)sp18)->v)->v = D_8005822C[arg0].m0;
    ((struct gd_20_s32 *)((struct gd_30_s32 *)sp18)->v)->v = arg1;
    D_800BCA0C = func_8000B978();
    D_800B40C4 = 0;
    sp1C = func_80021908(arg0);
    func_8009CEC0(sp1C, D_8005822C[arg0].m8);
}
