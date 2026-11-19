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
struct gd_C_s32 { u8 pad[0xC]; s32 v; };
extern s32 D_8004B7A8;
extern s32 D_8004B7AC;
extern s32 D_800BA598;
extern s32 D_800BA5CC;
extern s32 D_800BA5D0;
s32 func_8003A538();
s32 func_8003A568();
s32 func_8003E318();

void func_80003FDC(void) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;

    for (sp10 = 0;;) {
        if ((u32)sp10 >= (u32)D_8004B7AC) {
            break;
        }
        if (func_8003E318(((s32)&D_800BA598), ((s32)&sp14), 0) == -1) {
        }
        sp10++;
    }
    sp18 = D_800BA5CC;
    for (;;) {
        if (sp18 == 0) {
            break;
        }
        sp1C = *(s32 *)sp18;
        if ((u32)(((struct gd_C_s32 *)sp18)->v + 1) < (u32)D_8004B7A8) {
            if (D_800BA5CC == sp18) {
                D_800BA5CC = *(s32 *)sp18;
            }
            func_8003A538(sp18);
            if (D_800BA5D0 != 0) {
                func_8003A568(sp18, D_800BA5D0);
            } else {
                D_800BA5D0 = sp18;
                (*(s32 *)sp18) = 0;
                ((struct gd_4_s32 *)sp18)->v = 0;
            }
        }
        sp18 = sp1C;
    }
    D_8004B7AC = 0;
    D_8004B7A8++;
}
