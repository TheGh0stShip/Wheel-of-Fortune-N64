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
struct gd_7_u8 { u8 pad[0x7]; u8 v; };
struct gd_C_s32 { u8 pad[0xC]; s32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct n64dk_a8005A9AC { s32 m0; u8 pad4[0x4]; s32 m8; u8 padC[0x1C]; };
extern struct n64dk_a8005A9AC D_8005A9AC[];
extern s8 D_800B61B5;
extern s32 D_800B966A;
extern s32 D_800BED88;
s32 func_80002CE0();

void func_8002ACE8(s32 arg0) {
    s32 sp10;

    D_800BED88++;
    if (((struct gd_4_s32 *)((struct gd_30_s32 *)arg0)->v)->v < 13) {
        return;
    }
    sp10 = 0;
    for (;;) {
        if (sp10 >= 13) {
            break;
        }
        if ((*(u8 *)(sp10 + ((s32)&D_800B966A))) != 32) {
            break;
        }
        sp10++;
    }
    if (sp10 == 13) {
        return;
    }
    func_80002CE0(43);
    ((struct gd_4_s32 *)((struct gd_30_s32 *)arg0)->v)->v = ((struct gd_4_s32 *)((struct gd_30_s32 *)arg0)->v)->v - 13;
    D_8005A9AC[((struct gd_4_s32 *)((struct gd_30_s32 *)arg0)->v)->v].m8 = D_8005A9AC[((struct gd_4_s32 *)((struct gd_30_s32 *)arg0)->v)->v].m0;
    D_800B61B5 = ((struct gd_7_u8 *)((struct gd_30_s32 *)arg0)->v)->v + 65;
    ((struct gd_C_s32 *)((struct gd_30_s32 *)arg0)->v)->v = 15;
}
