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
struct n64dk_e8 { u8 b[8]; };
extern struct n64dk_e8 *D_800B81E8;

void func_80005300(s32 arg0) {
    s32 sp0;

    switch (arg0) {
    case 1:
        sp0 = (s32)D_800B81E8++;
        (*(s32 *)sp0) = 0xBC00000A;
        ((struct gd_4_s32 *)sp0)->v = 0x505050FF;
        sp0 = (s32)D_800B81E8++;
        (*(s32 *)sp0) = 0xBC00040A;
        ((struct gd_4_s32 *)sp0)->v = 0x505050FF;
        return;
    case 2:
        sp0 = (s32)D_800B81E8++;
        (*(s32 *)sp0) = 0xBC00200A;
        ((struct gd_4_s32 *)sp0)->v = 0x8C8C8CFF;
        sp0 = (s32)D_800B81E8++;
        (*(s32 *)sp0) = 0xBC00240A;
        ((struct gd_4_s32 *)sp0)->v = 0x8C8C8CFF;
        return;
    case 3:
        sp0 = (s32)D_800B81E8++;
        (*(s32 *)sp0) = 0xBC00400A;
        ((struct gd_4_s32 *)sp0)->v = 0x8C8C8CFF;
        sp0 = (s32)D_800B81E8++;
        (*(s32 *)sp0) = 0xBC00440A;
        ((struct gd_4_s32 *)sp0)->v = 0x8C8C8CFF;
        return;
    case 4:
        sp0 = (s32)D_800B81E8++;
        (*(s32 *)sp0) = 0xBC00600A;
        ((struct gd_4_s32 *)sp0)->v = 0x8C8C8CFF;
        sp0 = (s32)D_800B81E8++;
        (*(s32 *)sp0) = 0xBC00640A;
        ((struct gd_4_s32 *)sp0)->v = 0x8C8C8CFF;
        return;
    case 5:
        sp0 = (s32)D_800B81E8++;
        (*(s32 *)sp0) = 0xBC00800A;
        ((struct gd_4_s32 *)sp0)->v = 0x8C8C8CFF;
        sp0 = (s32)D_800B81E8++;
        (*(s32 *)sp0) = 0xBC00840A;
        ((struct gd_4_s32 *)sp0)->v = 0x8C8C8CFF;
        return;
    case 6:
        sp0 = (s32)D_800B81E8++;
        (*(s32 *)sp0) = 0xBC00A00A;
        ((struct gd_4_s32 *)sp0)->v = 0x141414FF;
        sp0 = (s32)D_800B81E8++;
        (*(s32 *)sp0) = 0xBC00A40A;
        ((struct gd_4_s32 *)sp0)->v = 0x141414FF;
        return;
    }
}
