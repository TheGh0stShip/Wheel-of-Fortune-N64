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

struct n64dk_m1A40_40 { u8 pad[0x1A40]; struct { u8 b[0x40]; } m[1]; };
struct gd_4_s32 { u8 pad[0x4]; s32 v; };
struct gd_8_s32 { u8 pad[0x8]; s32 v; };
struct gd_10_s16 { u8 pad[0x10]; s16 v; };
struct gd_10_s32 { u8 pad[0x10]; s32 v; };
struct gd_12_s16 { u8 pad[0x12]; s16 v; };
struct gd_14_s16 { u8 pad[0x14]; s16 v; };
struct gd_20_s32 { u8 pad[0x20]; s32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct gd_44_s32 { u8 pad[0x44]; s32 v; };
struct n64dk_e8 { u8 b[8]; };
struct n64dk_v4 { u8 pad[0x4]; void *v; };
extern s32 D_0113AD08;
extern s32 D_0113AD28;
extern s32 D_0113AD48;
extern s32 D_0113AE28;
extern s32 D_800B61A8;
extern struct n64dk_e8 *D_800B81E8;
extern s32 D_800BCD54;
s32 func_8000A990();
s32 func_8003143C();
s32 func_8003C2F0(s32, f32, f32, f32);

void func_80030B5C(s32 arg0, s32 arg1) {
    s32 sp10;
    s32 sp14;
    s32 sp18;

    if (((struct gd_44_s32 *)arg0)->v == 0) {
        return;
    }
    if (D_800BCD54 == 6) {
        sp10 = func_8000A990(0xA000400, -1);
        if (sp10 != 0) {
            sp14 = ((struct gd_8_s32 *)((struct gd_30_s32 *)sp10)->v)->v + (((struct gd_10_s32 *)((struct gd_30_s32 *)sp10)->v)->v * 0x3000);
            func_8003143C(sp14, (((struct gd_20_s32 *)((struct gd_30_s32 *)sp10)->v)->v * D_800B61A8));
        }
    }
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0x1020040;
    ((struct gd_4_s32 *)sp18)->v = (s32)&D_0113AE28;
    func_8003C2F0(((s32)&((struct n64dk_m1A40_40 *)arg1)->m[*(s32 *)arg0]), ((f32)((struct gd_10_s16 *)arg0)->v), ((f32)((struct gd_12_s16 *)arg0)->v), ((f32)((struct gd_14_s16 *)arg0)->v));
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0x1000040;
    ((struct n64dk_v4 *)sp18)->v = (void *)&((struct n64dk_m1A40_40 *)arg1)->m[*(s32 *)arg0];
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0xBB000001;
    ((struct gd_4_s32 *)sp18)->v = -1;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0xE7000000;
    ((struct gd_4_s32 *)sp18)->v = 0;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0xB900031D;
    ((struct gd_4_s32 *)sp18)->v = 0x553078;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0xFC127E24;
    ((struct gd_4_s32 *)sp18)->v = -3079;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0xFD100000;
    ((struct gd_4_s32 *)sp18)->v = ((struct gd_44_s32 *)arg0)->v;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0xF5100000;
    ((struct gd_4_s32 *)sp18)->v = 0x7094260;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0xE6000000;
    ((struct gd_4_s32 *)sp18)->v = 0;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0xF3000000;
    ((struct gd_4_s32 *)sp18)->v = 0x77FF080;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0xE7000000;
    ((struct gd_4_s32 *)sp18)->v = 0;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0xF5102000;
    ((struct gd_4_s32 *)sp18)->v = 0x94260;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0xF2000000;
    ((struct gd_4_s32 *)sp18)->v = 0xFC07C;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0xE7000000;
    ((struct gd_4_s32 *)sp18)->v = 0;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0x6000000;
    ((struct gd_4_s32 *)sp18)->v = (s32)&D_0113AD08;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0xFD100000;
    ((struct gd_4_s32 *)sp18)->v = ((struct gd_44_s32 *)arg0)->v + 0x1000;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0xF5100000;
    ((struct gd_4_s32 *)sp18)->v = 0x7094260;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0xE6000000;
    ((struct gd_4_s32 *)sp18)->v = 0;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0xF3000000;
    ((struct gd_4_s32 *)sp18)->v = 0x77FF080;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0xE7000000;
    ((struct gd_4_s32 *)sp18)->v = 0;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0xF5102000;
    ((struct gd_4_s32 *)sp18)->v = 0x94260;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0xF2000000;
    ((struct gd_4_s32 *)sp18)->v = 0xFC07C;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0x6000000;
    ((struct gd_4_s32 *)sp18)->v = (s32)&D_0113AD28;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0xFD100000;
    ((struct gd_4_s32 *)sp18)->v = ((struct gd_44_s32 *)arg0)->v + 0x2000;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0xF5100000;
    ((struct gd_4_s32 *)sp18)->v = 0x7094260;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0xE6000000;
    ((struct gd_4_s32 *)sp18)->v = 0;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0xF3000000;
    ((struct gd_4_s32 *)sp18)->v = 0x77FF080;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0xE7000000;
    ((struct gd_4_s32 *)sp18)->v = 0;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0xF5102000;
    ((struct gd_4_s32 *)sp18)->v = 0x94260;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0xF2000000;
    ((struct gd_4_s32 *)sp18)->v = 0xFC07C;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0x6000000;
    ((struct gd_4_s32 *)sp18)->v = (s32)&D_0113AD48;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0xE7000000;
    ((struct gd_4_s32 *)sp18)->v = 0;
    sp18 = (s32)D_800B81E8++;
    (*(s32 *)sp18) = 0xB900031D;
    ((struct gd_4_s32 *)sp18)->v = 0x552078;
}
