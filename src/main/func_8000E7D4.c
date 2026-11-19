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
struct gd_C_f32 { u8 pad[0xC]; f32 v; };
struct gd_10_f32 { u8 pad[0x10]; f32 v; };
struct gd_10_s16 { u8 pad[0x10]; s16 v; };
struct gd_12_s16 { u8 pad[0x12]; s16 v; };
struct gd_14_f32 { u8 pad[0x14]; f32 v; };
struct gd_14_s16 { u8 pad[0x14]; s16 v; };
struct gd_28_f32 { u8 pad[0x28]; f32 v; };
struct gd_2C_f32 { u8 pad[0x2C]; f32 v; };
struct gd_30_f32 { u8 pad[0x30]; f32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct gd_3C_s32 { u8 pad[0x3C]; s32 v; };
struct n64dk_a80057808 { s32 m0; s32 m4; u8 pad8[0x4]; };
extern struct n64dk_a80057808 D_80057808[];
extern s32 D_011356C0;
extern s32 D_01197D78;
extern f32 D_80000AE4;
extern f32 D_80000AE8;
extern f32 D_80000AEC;
extern f32 D_80000AF0;
extern f32 D_80000AF4;
extern f32 D_80000AF8;
extern s32 func_8000BEA8;
extern s32 func_8000C310;
extern s32 func_8000C50C;
extern s32 func_8000C6C4;
extern s32 func_8000CB58;
extern s32 func_8000D400;
extern s32 func_8000D6D8;
extern s32 func_8000D8B8;
extern s32 func_8000DCA0;
extern s32 func_800287A4;
extern s32 D_800578B0;
extern s32 D_80057910;
extern s32 D_800B3994;
extern s32 D_800B6198;
extern s32 D_800B61AC;
extern s32 D_800BCD54;
extern s32 D_800BEE24;
extern s32 D_800FB808;
s32 func_80002CE0();
s32 func_8000A56C();
s32 func_80015848();
s32 func_80016B9C();
s32 func_800174DC();

void func_8000E7D4(void) {
    s32 sp10;
    s32 sp14;
    s32 pad0;
    s32 sp1C;

    D_800FB808 = 0;
    D_800BCD54 = 1;
    func_800174DC();
    func_80016B9C(6);
    D_800B3994 = 0;
    func_80015848(0, 0, ((s32)&func_8000CB58), 0x8000000);
    func_80015848(0, 0, ((s32)&func_8000DCA0), 0x8000000);
    sp1C = 0;
    for (;;) {
        if (sp1C >= 14) {
            break;
        }
        sp10 = func_8000A56C(((s32)&func_8000C6C4), 0x8010000);
        ((struct gd_8_s32 *)((struct gd_30_s32 *)sp10)->v)->v = sp1C;
        sp14 = func_80015848(sp10, D_80057808[sp1C].m0, ((s32)&func_8000D6D8), 0x8010000);
        ((struct gd_3C_s32 *)sp14)->v = D_80057808[sp1C].m4;
        sp1C++;
    }
    sp10 = func_8000A56C(((s32)&func_8000C310), 0x8010000);
    sp14 = func_80015848(sp10, ((s32)&D_011356C0), ((s32)&func_8000D8B8), 0x8010000);
    ((struct gd_12_s16 *)sp14)->v = -20;
    sp10 = func_8000A56C(((s32)&func_8000BEA8), 0x8000000);
    sp14 = func_80015848(sp10, ((s32)&D_01197D78), ((s32)&func_8000D400), 0x8010000);
    ((struct gd_C_f32 *)((struct gd_30_s32 *)sp10)->v)->v = D_80000AE4;
    ((struct gd_10_f32 *)((struct gd_30_s32 *)sp10)->v)->v = D_80000AE8;
    ((struct gd_14_f32 *)((struct gd_30_s32 *)sp10)->v)->v = D_80000AEC;
    ((struct gd_10_s16 *)sp14)->v = -272;
    ((struct gd_12_s16 *)sp14)->v = 306;
    ((struct gd_14_s16 *)sp14)->v = -411;
    ((struct gd_28_f32 *)sp14)->v = D_80000AF0;
    ((struct gd_2C_f32 *)sp14)->v = D_80000AF4;
    ((struct gd_30_f32 *)sp14)->v = D_80000AF8;
    D_800B61AC = 0;
    ((struct gd_4_s32 *)((struct gd_30_s32 *)sp10)->v)->v = func_80002CE0(15);
    sp1C = 0;
    for (;;) {
        if (sp1C >= 24) {
            break;
        }
        sp10 = func_8000A56C(((s32)&func_8000C50C), 0x8010000);
        ((struct gd_8_s32 *)((struct gd_30_s32 *)sp10)->v)->v = sp1C;
        sp14 = func_80015848(sp10, (*(s32 *)((sp1C * 4) + ((s32)&D_800578B0))), ((s32)&func_8000D6D8), 0x8010000);
        ((struct gd_3C_s32 *)sp14)->v = *(s32 *)((sp1C * 4) + ((s32)&D_80057910));
        sp1C++;
    }
    func_80015848(0, 0, ((s32)&func_800287A4), 0x5000000);
    D_800B6198 = 721;
    D_800BEE24 = 0;
}
