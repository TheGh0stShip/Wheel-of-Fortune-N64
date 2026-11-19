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

struct gd_10_s16 { u8 pad[0x10]; s16 v; };
struct gd_12_s16 { u8 pad[0x12]; s16 v; };
struct gd_14_s16 { u8 pad[0x14]; s16 v; };
struct n64dk_a8005A39E { u16 m0; u8 pad2[0x2]; u16 m4; u8 pad6[0x2]; u16 m8; u8 padA[0x2]; };
extern struct n64dk_a8005A39E D_8005A39E[];
extern s32 D_800015D4;
extern s32 D_80058880;
extern u16 D_8005A392;
extern u16 D_8005A396;
extern u16 D_8005A39A;
s32 func_80009F38();
s32 func_8000B5DC();

void func_80023B44(void) {
    s32 sp10;
    s32 sp14;

    for (sp10 = 0;;) {
        if (sp10 >= 6) {
            return;
        }
        sp14 = func_8000B5DC((sp10 | 0xA020000), -1);
        if (sp14 == 0) {
            func_80009F38(((s32)&D_800015D4));
        }
        if (sp10 == D_80058880) {
            ((struct gd_10_s16 *)sp14)->v = D_8005A392;
            ((struct gd_12_s16 *)sp14)->v = D_8005A396;
            ((struct gd_14_s16 *)sp14)->v = D_8005A39A;
        } else {
            ((struct gd_10_s16 *)sp14)->v = D_8005A39E[sp10].m0;
            ((struct gd_12_s16 *)sp14)->v = D_8005A39E[sp10].m4;
            ((struct gd_14_s16 *)sp14)->v = D_8005A39E[sp10].m8;
        }
        sp10++;
    }
}
