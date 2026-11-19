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

struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct gd_44_s32 { u8 pad[0x44]; s32 v; };
struct n64dk_o800BEF5C { u8 pad[0x4]; struct { u8 b[0x1E47C]; } a; };
extern struct n64dk_o800BEF5C D_800BEF5C[];
extern s32 D_800B40C4;
extern s32 D_800B61A0;
extern s32 D_800BEF60;
s32 func_8003FF78();
s32 func_8009D244();

void func_800212C0(s32 arg0) {
    s32 sp10;
    s32 pad0;
    s32 pad1[6];
    s32 pad2;
    s32 sp34;

    sp34 = 0x2000000;
    sp10 = func_8003FF78(((s32)&D_800BEF5C[D_800B61A0].a + 0x19C00));
    sp10 = sp10 - func_8003FF78(((D_800B61A0 * 0x1E480) + ((s32)&D_800BEF60)));
    ((struct gd_44_s32 *)(*(s32 *)((struct gd_30_s32 *)arg0)->v))->v = sp34 + sp10;
    if (D_800B40C4 == 0) {
        D_800B40C4 = func_8009D244();
    }
}
