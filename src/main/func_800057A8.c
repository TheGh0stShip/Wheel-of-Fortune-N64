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
struct gd_C_s32 { u8 pad[0xC]; s32 v; };
struct gd_10_s16 { u8 pad[0x10]; s16 v; };
struct gd_10_s32 { u8 pad[0x10]; s32 v; };
struct gd_12_s16 { u8 pad[0x12]; s16 v; };
struct gd_14_s16 { u8 pad[0x14]; s16 v; };
struct gd_14_s32 { u8 pad[0x14]; s32 v; };
struct gd_18_s32 { u8 pad[0x18]; s32 v; };
struct gd_1C_s32 { u8 pad[0x1C]; s32 v; };
struct gd_20_s32 { u8 pad[0x20]; s32 v; };
struct gd_28_f32 { u8 pad[0x28]; f32 v; };
struct gd_28_s32 { u8 pad[0x28]; s32 v; };
struct gd_2C_f32 { u8 pad[0x2C]; f32 v; };
struct gd_2C_s32 { u8 pad[0x2C]; s32 v; };
struct gd_30_f32 { u8 pad[0x30]; f32 v; };
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
struct gd_1E478_s32 { u8 pad[0x1E478]; s32 v; };
struct n64dk_e8 { u8 b[8]; };
extern s32 D_010217E0;
extern s32 D_010218C8;
extern s32 D_01021948;
extern s32 D_80000520;
extern s32 D_800349B8;
extern s32 D_80034A88;
extern s32 D_8004B830;
extern s32 D_80082BC8;
extern s32 D_800AB5E8;
extern s32 D_800B3CC0;
extern s32 D_800B61E0;
extern struct n64dk_e8 *D_800B81E8;
extern s32 D_800B9688;
extern s32 D_800BCA08;
extern s32 D_800BCD54;
extern f32 D_800BEE2C;
extern f32 D_800BEE30;
extern f32 D_800BEE34;
extern f32 D_800BEE3C;
extern f32 D_800BEE40;
extern f32 D_800BEE44;
extern s32 D_800BEEA0;
extern s32 D_8038F800;
s32 func_80005FD0();
s32 func_80009F38();
s32 func_8000B468();
s32 func_8000B528();
s32 func_8000B5DC();
s32 func_8003E4B8();
s32 func_8003FF78();
s32 func_800453B8();

void func_800057A8(s32 arg0) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;

    sp18 = func_8000B5DC(0x3000000, 0xFF000000);
    if (sp18 != 0) {
        D_800BEE2C = (f32)((struct gd_10_s16 *)sp18)->v;
        D_800BEE30 = (f32)((struct gd_12_s16 *)sp18)->v;
        D_800BEE34 = (f32)((struct gd_14_s16 *)sp18)->v;
        D_800BEE3C = ((struct gd_28_f32 *)sp18)->v;
        D_800BEE40 = ((struct gd_2C_f32 *)sp18)->v;
        D_800BEE44 = ((struct gd_30_f32 *)sp18)->v;
    }
    sp10 = arg0 + 88;
    D_800B81E8 = (void *)(arg0 + 0x4D18);
    sp1C = (s32)D_800B81E8++;
    (*(s32 *)sp1C) = 0xBC000006;
    ((struct gd_4_s32 *)sp1C)->v = 0;
    sp1C = (s32)D_800B81E8++;
    (*(s32 *)sp1C) = 0xBC000406;
    ((struct gd_4_s32 *)sp1C)->v = func_8003FF78(D_800BCA08);
    sp1C = (s32)D_800B81E8++;
    (*(s32 *)sp1C) = 0xBC000806;
    ((struct gd_4_s32 *)sp1C)->v = func_8003FF78(sp10);
    sp1C = (s32)D_800B81E8++;
    (*(s32 *)sp1C) = 0x6000000;
    ((struct gd_4_s32 *)sp1C)->v = (s32)&D_01021948;
    if (D_8004B830 != 0) {
        sp1C = (s32)D_800B81E8++;
        (*(s32 *)sp1C) = 0x6000000;
        ((struct gd_4_s32 *)sp1C)->v = (s32)&D_010217E0;
        D_8004B830 = 0;
    }
    sp1C = (s32)D_800B81E8++;
    (*(s32 *)sp1C) = 0x6000000;
    ((struct gd_4_s32 *)sp1C)->v = (s32)&D_010218C8;
    sp1C = (s32)D_800B81E8++;
    (*(s32 *)sp1C) = 0xFE000000;
    ((struct gd_4_s32 *)sp1C)->v = func_8003FF78(((s32)&D_8038F800));
    sp1C = (s32)D_800B81E8++;
    (*(s32 *)sp1C) = 0xE7000000;
    ((struct gd_4_s32 *)sp1C)->v = 0;
    sp1C = (s32)D_800B81E8++;
    (*(s32 *)sp1C) = 0xBA001402;
    ((struct gd_4_s32 *)sp1C)->v = 0x300000;
    sp1C = (s32)D_800B81E8++;
    (*(s32 *)sp1C) = 0xFF10013F;
    ((struct gd_4_s32 *)sp1C)->v = func_8003FF78(((s32)&D_8038F800));
    sp1C = (s32)D_800B81E8++;
    (*(s32 *)sp1C) = 0xF7000000;
    ((struct gd_4_s32 *)sp1C)->v = 0xFFFCFFFC;
    sp1C = (s32)D_800B81E8++;
    (*(s32 *)sp1C) = 0xF64FC3BC;
    ((struct gd_4_s32 *)sp1C)->v = 0;
    sp1C = (s32)D_800B81E8++;
    (*(s32 *)sp1C) = 0xE7000000;
    ((struct gd_4_s32 *)sp1C)->v = 0;
    sp1C = (s32)D_800B81E8++;
    (*(s32 *)sp1C) = 0xFF10013F;
    ((struct gd_4_s32 *)sp1C)->v = func_8003FF78(((struct gd_1E478_s32 *)arg0)->v);
    sp1C = (s32)D_800B81E8++;
    (*(s32 *)sp1C) = 0xF7000000;
    ((struct gd_4_s32 *)sp1C)->v = 0x10001;
    sp1C = (s32)D_800B81E8++;
    (*(s32 *)sp1C) = 0xF64FC3BC;
    ((struct gd_4_s32 *)sp1C)->v = 0;
    sp1C = (s32)D_800B81E8++;
    (*(s32 *)sp1C) = 0xE7000000;
    ((struct gd_4_s32 *)sp1C)->v = 0;
    sp1C = (s32)D_800B81E8++;
    (*(s32 *)sp1C) = 0xBA001402;
    ((struct gd_4_s32 *)sp1C)->v = 0;
    switch (D_800BCD54) {
    case 1:
    case 5:
    case 7:
    case 8:
        sp1C = (s32)D_800B81E8++;
        (*(s32 *)sp1C) = 0xED000000;
        ((struct gd_4_s32 *)sp1C)->v = 0x5003C0;
        break;
    case 4:
        sp1C = (s32)D_800B81E8++;
        (*(s32 *)sp1C) = 0xED000000;
        ((struct gd_4_s32 *)sp1C)->v = 0x5002BC;
        break;
    default:
        sp1C = (s32)D_800B81E8++;
        (*(s32 *)sp1C) = 0xED000000;
        ((struct gd_4_s32 *)sp1C)->v = 0x5002AC;
    }
    sp1C = (s32)D_800B81E8++;
    (*(s32 *)sp1C) = 0xB900031D;
    ((struct gd_4_s32 *)sp1C)->v = 0x552078;
    func_8000B468(sp10);
    func_80005FD0(sp10);
    func_8000B528(sp10);
    sp1C = (s32)D_800B81E8++;
    (*(s32 *)sp1C) = 0xE9000000;
    ((struct gd_4_s32 *)sp1C)->v = 0;
    sp1C = (s32)D_800B81E8++;
    (*(s32 *)sp1C) = 0xB8000000;
    ((struct gd_4_s32 *)sp1C)->v = 0;
    func_800453B8((arg0 + 88), (((s32)D_800B81E8) - (arg0 + 88)));
    if (((struct n64dk_e8 *)((s32)D_800B81E8) - (struct n64dk_e8 *)(sp10 + 0x4CC0)) >= 3048) {
        func_80009F38(((s32)&D_80000520));
    }
    sp14 = arg0;
    ((struct gd_40_s32 *)sp14)->v = sp10 + 0x4CC0;
    ((struct gd_44_s32 *)sp14)->v = (s32)((u32)((struct n64dk_e8 *)((s32)D_800B81E8) - (struct n64dk_e8 *)(sp10 + 0x4CC0)) * 8);
    ((struct gd_10_s32 *)sp14)->v = 1;
    ((struct gd_14_s32 *)sp14)->v = 0;
    ((struct gd_18_s32 *)sp14)->v = (s32)&D_800349B8;
    ((struct gd_1C_s32 *)sp14)->v = ((s32)&D_80034A88) - ((s32)&D_800349B8);
    ((struct gd_20_s32 *)sp14)->v = (s32)&D_80034A88;
    ((struct gd_28_s32 *)sp14)->v = (s32)&D_80082BC8;
    ((struct gd_2C_s32 *)sp14)->v = 2048;
    ((struct gd_30_s32 *)sp14)->v = (s32)&D_800B3CC0;
    ((struct gd_34_s32 *)sp14)->v = 1024;
    ((struct gd_38_s32 *)sp14)->v = 0;
    ((struct gd_3C_s32 *)sp14)->v = 0;
    ((struct gd_48_s32 *)sp14)->v = (s32)&D_800B61E0;
    ((struct gd_4C_s32 *)sp14)->v = 2304;
    (*(s32 *)sp14) = 0;
    ((struct gd_8_s32 *)sp14)->v = 99;
    ((struct gd_50_s32 *)sp14)->v = (s32)&D_800B9688;
    ((struct gd_54_s32 *)sp14)->v = arg0 + 0x1E458;
    ((struct gd_C_s32 *)sp14)->v = ((struct gd_1E478_s32 *)arg0)->v;
    func_8003E4B8(D_800BEEA0, sp14, 1);
    D_800AB5E8++;
}
