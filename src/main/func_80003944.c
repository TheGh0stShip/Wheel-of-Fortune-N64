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

struct gd_4_s16 { u8 pad[0x4]; s16 v; };
struct gd_8_s32 { u8 pad[0x8]; s32 v; };
struct gd_10_s32 { u8 pad[0x10]; s32 v; };
struct gd_14_s32 { u8 pad[0x14]; s32 v; };
struct gd_18_s32 { u8 pad[0x18]; s32 v; };
struct gd_1C_s32 { u8 pad[0x1C]; s32 v; };
struct gd_20_s32 { u8 pad[0x20]; s32 v; };
struct gd_28_s32 { u8 pad[0x28]; s32 v; };
struct gd_2C_s32 { u8 pad[0x2C]; s32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct gd_34_s32 { u8 pad[0x34]; s32 v; };
struct gd_38_s32 { u8 pad[0x38]; s32 v; };
struct gd_3C_s32 { u8 pad[0x3C]; s32 v; };
struct gd_40_s32 { u8 pad[0x40]; s32 v; };
struct gd_44_s32 { u8 pad[0x44]; s32 v; };
struct gd_48_s32 { u8 pad[0x48]; s32 v; };
struct gd_4C_s32 { u8 pad[0x4C]; s32 v; };
struct gd_50_s32 { u8 pad[0x50]; s32 v; };
struct gd_54_s32 { u8 pad[0x54]; s32 v; };
struct n64dk_e8 { u8 b[8]; };
extern s32 D_800349B8;
extern s32 D_80034A88;
extern s32 D_80037298;
extern s32 D_8004B7B0;
extern s32 D_80083BC8;
extern s32 D_800B96B8;
extern s32 D_800B96BC;
extern u16 D_800B96BE;
extern s32 D_800BA5CC;
extern s32 D_800BCA68;
extern s32 D_800BCC68;
extern u16 D_800BCD66;
extern s32 D_800BEEA0;
s32 func_80003FDC();
s32 func_80038748();
s32 func_800388B8();
s32 func_80039980();
s32 func_8003E4B8();
s32 func_8003FF78();

s32 func_80003944(s32 arg0, s32 arg1) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;

    sp1C = 0;
    sp24 = 0;
    sp28 = D_800BA5CC;
    for (;;) {
        if (sp28 == 0) {
            break;
        }
        sp24++;
        sp28 = *(s32 *)sp28;
    }
    if (sp24 > D_800B96B8) {
        D_800B96B8 = sp24;
    }
    func_80003FDC();
    sp10 = func_8003FF78((*(s32 *)arg0));
    if (arg1 != 0) {
        func_800388B8((*(s32 *)arg1), (((struct gd_4_s16 *)arg1)->v << 2));
    }
    sp1C = (u32)func_80038748() >> 2;
    ((struct gd_4_s16 *)arg0)->v = ((D_800BCD66 - ((u16)sp1C)) + 96) & 0xFFF0u;
    if ((u32)((struct gd_4_s16 *)arg0)->v < (u32)D_800B96BC) {
        ((struct gd_4_s16 *)arg0)->v = D_800B96BE;
    }
    sp14 = func_80039980((*(s32 *)((D_8004B7B0 * 4) + ((s32)&D_800BCA68))), ((s32)&sp18), sp10, ((struct gd_4_s16 *)arg0)->v);
    if (sp18 == 0) {
        return 0;
    }
    sp20 = arg0 + 8;
    (*(s32 *)sp20) = 0;
    ((struct gd_50_s32 *)sp20)->v = (s32)&D_800BCC68;
    ((struct gd_54_s32 *)sp20)->v = arg0 + 96;
    ((struct gd_8_s32 *)sp20)->v = 2;
    ((struct gd_40_s32 *)sp20)->v = *(s32 *)((D_8004B7B0 * 4) + ((s32)&D_800BCA68));
    ((struct gd_44_s32 *)sp20)->v = (s32)((u32)((struct n64dk_e8 *)sp14 - (struct n64dk_e8 *)(*(s32 *)((D_8004B7B0 * 4) + ((s32)&D_800BCA68)))) * 8);
    ((struct gd_10_s32 *)sp20)->v = 2;
    ((struct gd_18_s32 *)sp20)->v = (s32)&D_800349B8;
    ((struct gd_1C_s32 *)sp20)->v = ((s32)&D_80034A88) - ((s32)&D_800349B8);
    ((struct gd_14_s32 *)sp20)->v = 2;
    ((struct gd_20_s32 *)sp20)->v = (s32)&D_80037298;
    ((struct gd_28_s32 *)sp20)->v = (s32)&D_80083BC8;
    ((struct gd_2C_s32 *)sp20)->v = 2048;
    ((struct gd_30_s32 *)sp20)->v = 0;
    ((struct gd_34_s32 *)sp20)->v = 0;
    ((struct gd_38_s32 *)sp20)->v = 0;
    ((struct gd_3C_s32 *)sp20)->v = 0;
    ((struct gd_48_s32 *)sp20)->v = 0;
    ((struct gd_4C_s32 *)sp20)->v = 0;
    func_8003E4B8(D_800BEEA0, sp20, 1);
    D_8004B7B0 = D_8004B7B0 ^ 1;
    return 1;
}
