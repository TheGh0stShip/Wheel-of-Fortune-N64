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

struct gd_8_s32 { u8 pad[0x8]; s32 v; };
struct gd_C_s32 { u8 pad[0xC]; s32 v; };
struct gd_10_s32 { u8 pad[0x10]; s32 v; };
struct gd_14_s32 { u8 pad[0x14]; s32 v; };
struct gd_40_s32 { u8 pad[0x40]; s32 v; };
extern s32 D_80000894;
extern s32 D_800B82A0;
extern s32 D_800BCD54;
s32 func_80009F38();
s32 func_8000A4A4();

void func_8000A664(void) {
    s32 sp10;
    s32 sp14;
    s32 pad0[2];
    s32 sp20;

    sp20 = (s32)&D_800B82A0;
    for (;;) {
        if (((struct gd_40_s32 *)sp20)->v == 0) {
            return;
        }
        sp20 = ((struct gd_40_s32 *)sp20)->v;
        if ((*(s32 *)sp20) == 0) {
            func_80009F38(((s32)&D_80000894));
            return;
        }
        if (((struct gd_14_s32 *)sp20)->v == 0) {
            if (((struct gd_C_s32 *)sp20)->v > 0) {
                if (D_800BCD54 != 6) {
                    ((struct gd_C_s32 *)sp20)->v--;
                }
            } else {
                if (D_800BCD54 == 6) {
                    if (((struct gd_8_s32 *)sp20)->v == 0xB000000) {
                        ((s32 (*)())(*(s32 *)sp20))(((s32)&sp10), sp20);
                    }
                } else {
                    ((s32 (*)())(*(s32 *)sp20))(((s32)&sp10), sp20);
                }
                switch (sp14) {
                case 0:
                    func_8000A4A4(sp20, sp10);
                    break;
                case 1:
                    ((struct gd_C_s32 *)sp20)->v = sp10;
                    break;
                case 2:
                    ((struct gd_10_s32 *)sp20)->v = sp10;
                    ((struct gd_14_s32 *)sp20)->v = 1;
                    break;
                case 3:
                    ((struct gd_10_s32 *)sp20)->v = sp10;
                    break;
                }
            }
        }
    }
}
