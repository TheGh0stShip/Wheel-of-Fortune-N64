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

struct gd_4_f32 { u8 pad[0x4]; f32 v; };
struct gd_8_s32 { u8 pad[0x8]; s32 v; };
struct gd_2C_f32 { u8 pad[0x2C]; f32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct gd_3C_s32 { u8 pad[0x3C]; s32 v; };
extern s32 D_01024340;
extern s32 D_01024368;
extern s32 D_01036FA8;
extern s32 D_01037090;
extern s32 D_01037178;
extern s32 D_01037E70;
extern s32 D_01037EB0;
extern s32 D_01037EF0;
extern s32 D_010A6098;
extern s32 D_010B3728;
extern s32 D_010E4260;
extern s32 D_0112BBA8;
extern s32 D_01135878;
extern s32 D_01135FF8;
extern f32 D_80000E14;
extern f32 D_80000E18;
extern f32 D_80000E1C;
extern f32 D_80000E20;
extern s32 func_8000F274;
extern s32 func_80012500;
extern s32 func_80013748;
extern s32 func_80014208;
extern s32 func_800144F0;
extern s32 func_80014768;
extern s32 func_80014A5C;
extern s32 func_80014F38;
extern s32 func_800153C4;
extern s32 D_80057F24;
extern s32 D_800B81E0;
extern s32 D_800BCCF0;
s32 func_80009C98();
s32 func_8000A56C();
s32 func_800132EC();
s32 func_80015848();
s32 func_800161A8();

void func_80016310(void) {
    s32 sp10;
    s32 sp14;
    s8 pad0;

    sp10 = 0;
    sp14 = func_80015848(sp10, ((s32)&D_01024340), ((s32)&func_80014F38), 0x4010000);
    ((struct gd_2C_f32 *)sp14)->v = D_80000E14;
    func_800161A8();
    D_800BCCF0 = 0;
    func_80015848(0, ((s32)&D_01024368), ((s32)&func_800144F0), 0xA000000);
    func_80015848(0, ((s32)&D_01135878), ((s32)&func_80014768), 0xA010100);
    func_80015848(0, ((s32)&D_01135FF8), ((s32)&func_80014768), 0xA010200);
    D_800B81E0 = func_80009C98(4);
    func_80015848(0, (*(s32 *)((D_800B81E0 * 4) + ((s32)&D_80057F24))), ((s32)&func_80014A5C), 0xA000000);
    func_80015848(0, ((s32)&D_0112BBA8), ((s32)&func_800144F0), 0xA000000);
    func_80015848(0, ((s32)&D_010B3728), ((s32)&func_800144F0), 0xA000000);
    func_80015848(0, ((s32)&D_010A6098), ((s32)&func_80014208), 0xA000000);
    func_80015848(0, ((s32)&D_010E4260), ((s32)&func_800153C4), 0xA000000);
    sp10 = func_8000A56C(((s32)&func_8000F274), 0x4020000);
    ((struct gd_4_f32 *)((struct gd_30_s32 *)sp10)->v)->v = D_80000E18;
    ((struct gd_8_s32 *)((struct gd_30_s32 *)sp10)->v)->v = 0;
    sp14 = func_80015848(sp10, ((s32)&D_01037090), ((s32)&func_80012500), 0x4020000);
    ((struct gd_3C_s32 *)sp14)->v = (s32)&D_01037EF0;
    func_800132EC(0);
    sp14 = func_80015848(0, 0, ((s32)&func_80013748), 0xA000000);
    sp10 = func_8000A56C(((s32)&func_8000F274), 0x4020001);
    ((struct gd_4_f32 *)((struct gd_30_s32 *)sp10)->v)->v = D_80000E1C;
    ((struct gd_8_s32 *)((struct gd_30_s32 *)sp10)->v)->v = 0;
    sp14 = func_80015848(sp10, ((s32)&D_01036FA8), ((s32)&func_80012500), 0x4020001);
    ((struct gd_3C_s32 *)sp14)->v = (s32)&D_01037EB0;
    sp10 = func_8000A56C(((s32)&func_8000F274), 0x4020002);
    ((struct gd_4_f32 *)((struct gd_30_s32 *)sp10)->v)->v = D_80000E20;
    ((struct gd_8_s32 *)((struct gd_30_s32 *)sp10)->v)->v = 0;
    sp14 = func_80015848(sp10, ((s32)&D_01037178), ((s32)&func_80012500), 0x4020002);
    ((struct gd_3C_s32 *)sp14)->v = (s32)&D_01037E70;
}
