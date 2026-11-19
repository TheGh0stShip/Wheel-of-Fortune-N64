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
struct gd_2C_f32 { u8 pad[0x2C]; f32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
extern f32 D_80000ECC;
extern s32 func_800181A4;
extern s32 D_8004B848;
extern s32 D_800581F4;
extern s32 D_800B619C;
extern s32 D_800B9540;
extern s32 D_800B96B4;
extern s32 D_800B96C0;
extern s32 D_800B9CEC;
extern s32 D_800B9CF0;
extern s32 D_800FB808;
s32 func_8000A56C();
s32 func_8000A850();
s32 func_8000ACE8();
s32 func_8000AE70();
s32 func_8000B5DC();
s32 func_800161A8();
s32 func_80016B9C();
s32 func_80017848();
s32 func_80017C00();
s32 func_800219B8();
s32 func_8002A014();
s32 func_80032858();
s32 func_80032AD4();
s32 func_80032B10();
s32 func_80033150();

struct n64dk_r12 func_80017DBC(s32 arg1) {
    struct n64dk_r12 sp10;
    s32 pad0;
    s32 sp24;
    s32 sp28;

    sp10.w[1] = 1;
    sp10.w[0] = 0;
    for (;;) {
        sp28 = func_8000ACE8(arg1);
        if (sp28 == 0) {
            break;
        }
        switch (sp28) {
        case 8:
            func_80017C00(3, 0);
            func_80032AD4(1);
            func_80032B10();
            if (D_800B619C != 2) {
                func_80033150(0, 0, D_800FB808);
            }
            sp10.w[1] = 1;
            sp10.w[0] = 320 / D_800B96B4;
            return sp10;
        case 45:
            func_80017C00(3, 0);
            func_800161A8();
            func_8000A850(47);
            if (D_800B619C == 2) {
                func_800219B8(7, 39, 180, 20);
            } else {
                func_800219B8(6, 39, 180, 20);
            }
            sp10.w[1] = 0;
            sp10.w[0] = 0;
            return sp10;
        }
    }
    func_80032858();
    func_80032B10();
    D_800B619C++;
    if ((D_800B9CF0 == 0) && (D_800B619C < D_800B96C0)) {
        func_80016B9C(13);
        if (D_800B619C == 2) {
            D_800B9CEC = 0;
            D_800B9540 = 0x1388;
            func_8002A014();
        }
        sp24 = func_8000B5DC(0x4010000, -1);
        ((struct gd_2C_f32 *)sp24)->v = (f32)((*(s32 *)((D_800B619C * 4) + ((s32)&D_8004B848))) - D_800581F4);
        ((struct gd_2C_f32 *)sp24)->v = ((struct gd_2C_f32 *)sp24)->v - D_80000ECC;
        sp10.w[1] = 2;
        sp10.w[0] = 45;
        return sp10;
    } else {
        func_8000AE70(0x7010000, -1, 0);
        D_800B9CF0 = 1;
        D_800B619C = 6;
        func_8000A56C(((s32)&func_800181A4), (((struct gd_4_s32 *)((struct gd_30_s32 *)arg1)->v)->v | 0x2000600));
        func_80017848();
        sp10.w[1] = 0;
        sp10.w[0] = 0;
        return sp10;
    }
    return sp10;
}
