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

struct n64dk_m140_40 { u8 pad[0x140]; struct { u8 b[0x40]; } m[1]; };
struct n64dk_m1A40_40 { u8 pad[0x1A40]; struct { u8 b[0x40]; } m[1]; };
struct n64dk_m3340_40 { u8 pad[0x3340]; struct { u8 b[0x40]; } m[1]; };
struct gd_4_s32 { u8 pad[0x4]; s32 v; };
struct gd_10_s16 { u8 pad[0x10]; s16 v; };
struct gd_12_s16 { u8 pad[0x12]; s16 v; };
struct gd_14_s16 { u8 pad[0x14]; s16 v; };
struct gd_18_s32 { u8 pad[0x18]; s32 v; };
struct gd_28_s32 { u8 pad[0x28]; s32 v; };
struct gd_2C_s32 { u8 pad[0x2C]; s32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct gd_48_s32 { u8 pad[0x48]; s32 v; };
struct n64dk_e8 { u8 b[8]; };
struct n64dk_v4 { u8 pad[0x4]; void *v; };
extern s32 D_010219C8;
extern s32 D_80057F34;
extern s32 D_800B81E0;
extern struct n64dk_e8 *D_800B81E8;
s32 func_80005300();
s32 func_8003BFF4();
s32 func_8003C09C();
s32 func_8003C2F0(s32, f32, f32, f32);

void func_80014A5C(s32 arg0, s32 arg1) {
    s32 sp10;

    func_8003C2F0(((s32)&((struct n64dk_m1A40_40 *)arg1)->m[*(s32 *)arg0]), ((f32)((struct gd_10_s16 *)arg0)->v), ((f32)((struct gd_12_s16 *)arg0)->v), ((f32)((struct gd_14_s16 *)arg0)->v));
    func_8003C09C(((s32)&((struct n64dk_m140_40 *)arg1)->m[*(s32 *)arg0]), ((struct gd_18_s32 *)arg0)->v, ((struct gd_18_s32 *)arg0)->v, ((struct gd_18_s32 *)arg0)->v);
    func_8003BFF4(((s32)&((struct n64dk_m3340_40 *)arg1)->m[*(s32 *)arg0]), ((struct gd_28_s32 *)arg0)->v, ((struct gd_2C_s32 *)arg0)->v, ((struct gd_30_s32 *)arg0)->v);
    sp10 = (s32)D_800B81E8++;
    (*(s32 *)sp10) = 0x1020040;
    ((struct n64dk_v4 *)sp10)->v = (void *)&((struct n64dk_m1A40_40 *)arg1)->m[*(s32 *)arg0];
    sp10 = (s32)D_800B81E8++;
    (*(s32 *)sp10) = 0x1000040;
    ((struct n64dk_v4 *)sp10)->v = (void *)&((struct n64dk_m140_40 *)arg1)->m[*(s32 *)arg0];
    sp10 = (s32)D_800B81E8++;
    (*(s32 *)sp10) = 0x1000040;
    ((struct n64dk_v4 *)sp10)->v = (void *)&((struct n64dk_m3340_40 *)arg1)->m[*(s32 *)arg0];
    sp10 = (s32)D_800B81E8++;
    (*(s32 *)sp10) = 0x6000000;
    ((struct gd_4_s32 *)sp10)->v = (s32)&D_010219C8;
    func_80005300(1);
    sp10 = (s32)D_800B81E8++;
    (*(s32 *)sp10) = 0xBC00200A;
    ((struct gd_4_s32 *)sp10)->v = 0x55555555;
    sp10 = (s32)D_800B81E8++;
    (*(s32 *)sp10) = 0xBC00240A;
    ((struct gd_4_s32 *)sp10)->v = 0x55555555;
    sp10 = (s32)D_800B81E8++;
    (*(s32 *)sp10) = 0xBC00400A;
    ((struct gd_4_s32 *)sp10)->v = 0x55555555;
    sp10 = (s32)D_800B81E8++;
    (*(s32 *)sp10) = 0xBC00440A;
    ((struct gd_4_s32 *)sp10)->v = 0x55555555;
    sp10 = (s32)D_800B81E8++;
    (*(s32 *)sp10) = 0xBC00600A;
    ((struct gd_4_s32 *)sp10)->v = 0x55555555;
    sp10 = (s32)D_800B81E8++;
    (*(s32 *)sp10) = 0xBC00640A;
    ((struct gd_4_s32 *)sp10)->v = 0x55555555;
    sp10 = (s32)D_800B81E8++;
    (*(s32 *)sp10) = 0xBC00800A;
    ((struct gd_4_s32 *)sp10)->v = 0x55555555;
    sp10 = (s32)D_800B81E8++;
    (*(s32 *)sp10) = 0xBC00840A;
    ((struct gd_4_s32 *)sp10)->v = 0x55555555;
    sp10 = (s32)D_800B81E8++;
    (*(s32 *)sp10) = 0x6000000;
    ((struct gd_4_s32 *)sp10)->v = ((struct gd_48_s32 *)arg0)->v;
    func_80005300(2);
    func_80005300(3);
    func_80005300(4);
    func_80005300(5);
    if ((*(s32 *)((D_800B81E0 * 4) + ((s32)&D_80057F34))) != 0) {
        sp10 = (s32)D_800B81E8++;
        (*(s32 *)sp10) = 0x6000000;
        ((struct gd_4_s32 *)sp10)->v = *(s32 *)((D_800B81E0 * 4) + ((s32)&D_80057F34));
    }
    func_80005300(1);
}
