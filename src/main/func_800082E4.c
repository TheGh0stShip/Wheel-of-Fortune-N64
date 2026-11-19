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

struct n64dk_e21 { u8 b[21]; };
extern s32 D_800B9559;
extern u8 D_800B9601[][21];
s32 func_800099B0();

s32 func_800082E4(void) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    void *sp1C;
    u8 sp20;

    sp18 = 0;
    sp14 = 0;
    sp10 = 0;
    for (;;) {
        if (sp10 >= 4) {
            break;
        }
        sp1C = (void *)&((struct n64dk_e21 *)&D_800B9559)[sp10];
        for (;;) {
            if (((s32)sp1C) == 0) {
                break;
            }
            sp1C = (void *)func_800099B0(((s32)sp1C), 43);
            if (((s32)sp1C) != 0) {
                sp20 = D_800B9601[sp10][(((s32)sp1C) - ((s32)&D_800B9559)) - (sp10 * 21)];
                switch (sp20) {
                case 65:
                case 69:
                case 73:
                case 79:
                case 85:
                    sp18++;
                    break;
                default:
                    sp14++;
                }
                sp1C++;
            }
        }
        sp10++;
    }
    if ((sp14 > 0) && (sp18 > 0)) {
        return 4;
    }
    if ((sp14 == 0) && (sp18 > 0)) {
        return 2;
    }
    if ((sp14 > 0) && (sp18 == 0)) {
        return 3;
    }
    return 1;
}
