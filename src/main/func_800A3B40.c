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

struct gd_204_s32 { u8 pad[0x204]; s32 v; };
struct gd_208_s32 { u8 pad[0x208]; s32 v; };
struct gd_218_s32 { u8 pad[0x218]; s32 v; };
struct gd_21C_s32 { u8 pad[0x21C]; s32 v; };
struct gd_220_s32 { u8 pad[0x220]; s32 v; };
s32 func_800A4A18();
s32 func_800A4C04();
s32 func_800A4C28();

s32 func_800A3B40(s32 arg0) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    u16 sp1C;
    u8 sp1E;

    sp10 = 0;
    sp14 = func_800A4A18(((s32)&sp1C), 1, 2, ((struct gd_208_s32 *)arg0)->v);
    if (sp14 != 2) {
        ((struct gd_204_s32 *)arg0)->v = 1;
        return 1;
    }
    sp10 = func_800A4C28((sp1C + 1));
    if (sp10 == 0) {
        return 1;
    }
    (*(s8 *)(sp1C + sp10)) = 0;
    sp14 = func_800A4A18(sp10, 1, sp1C, ((struct gd_208_s32 *)arg0)->v);
    if (sp14 < sp1C) {
        ((struct gd_204_s32 *)arg0)->v = 1;
        return 1;
    }
    sp18 = 6;
    for (;;) {
        if (((*(u8 *)(sp10 + sp18)) & 128) == 0) {
            break;
        }
        sp1E = *(u8 *)(sp10 + sp18);
        switch (sp1E) {
        case 185:
            break;
        case 184:
            break;
        case 188:
            break;
        case 190:
            break;
        case 189:
            break;
        case 191:
            break;
        default:
            if ((u32)sp1E < 188) {
                return 1;
            }
            switch ((s32)(((u32)sp1E >> 4) & 255)) {
            case 12:
            case 13:
                ((struct gd_218_s32 *)arg0)->v = sp1E;
                break;
            case 14:
                if (((struct gd_21C_s32 *)arg0)->v != 0) {
                    if (((struct gd_21C_s32 *)arg0)->v != sp1E) {
                        break;
                    }
                }
                ((struct gd_21C_s32 *)arg0)->v = sp1E;
                break;
            case 15:
                ((struct gd_220_s32 *)arg0)->v = sp1E;
                break;
            }
            break;
        }
        sp18 = sp18 + 3;
    }
    if (sp10 != 0) {
        func_800A4C04(sp10);
    }
    return 0;
}
