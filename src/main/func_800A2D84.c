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

struct gd_1E0_s32 { u8 pad[0x1E0]; s32 v; };
struct gd_1E4_s32 { u8 pad[0x1E4]; s32 v; };
struct gd_1E8_s32 { u8 pad[0x1E8]; s32 v; };
struct gd_1EC_s32 { u8 pad[0x1EC]; s32 v; };
struct gd_1F8_s32 { u8 pad[0x1F8]; s32 v; };
struct gd_208_s32 { u8 pad[0x208]; s32 v; };
struct gd_20C_s32 { u8 pad[0x20C]; s32 v; };
struct gd_234_s32 { u8 pad[0x234]; s32 v; };
struct gd_248_s32 { u8 pad[0x248]; s32 v; };
struct n64dk_e4 { u8 b[4]; };
struct n64dk_p1E4_4 { u8 pad[0x1E4]; struct n64dk_e4 *v; };
extern s32 D_8008855C;
s32 func_80009F38();
s32 func_800887D8();
s32 func_80088C58();
s32 func_800A2D38();
s32 func_800A3460();
s32 func_800A4AD8();
s32 func_800A4BB4();
s32 func_800A4CBC();

void func_800A2D84(s32 arg0) {
    s32 sp10;
    s32 sp14;

    if (((struct gd_20C_s32 *)arg0)->v < 0) {
        return;
    }
    sp10 = func_800A4BB4(((struct gd_208_s32 *)arg0)->v, ((struct gd_20C_s32 *)arg0)->v, 0);
    if (sp10 != 0) {
        func_80009F38(((s32)&D_8008855C));
    }
    ((struct gd_20C_s32 *)arg0)->v = -((struct gd_20C_s32 *)arg0)->v;
    ((struct gd_248_s32 *)arg0)->v = 0;
    ((struct gd_1E4_s32 *)arg0)->v = ((struct gd_1EC_s32 *)arg0)->v;
    ((struct gd_1E8_s32 *)arg0)->v = 0;
    ((struct gd_1E0_s32 *)arg0)->v = 0;
L31: ;
L32: ;
    switch (func_800A4AD8(((struct gd_208_s32 *)arg0)->v)) {
    case 0:
        goto L43;
    case -1:
        goto L178;
    default:
        goto L32;
    }
L43: ;
    switch (func_800A4AD8(((struct gd_208_s32 *)arg0)->v)) {
    case 0:
        goto L54;
    case -1:
        goto L178;
    default:
        goto L32;
    }
L54: ;
    switch (func_800A4AD8(((struct gd_208_s32 *)arg0)->v)) {
    case 1:
        goto L70;
    case 0:
        goto L54;
    case -1:
        goto L178;
    default:
        goto L32;
    }
L70: ;
    sp14 = func_800A4AD8(((struct gd_208_s32 *)arg0)->v) + 256;
    if (((struct gd_1F8_s32 *)arg0)->v != 0) {
        func_800A2D38(arg0);
        if ((sp14 & -256) == 256) {
            if ((sp14 & 255) >= 188) {
                func_800A3460(arg0, sp14);
                for (;;) {
                    goto L94;
                    break;
L94: ;
                    func_80088C58(arg0);
                    if (((struct gd_1E8_s32 *)arg0)->v < 2) {
                        func_800887D8(arg0);
                    }
                    if (((struct gd_1E0_s32 *)arg0)->v != 0) {
                        sp14 = ((struct gd_234_s32 *)arg0)->v | ((u32)(*(s32 *)(((struct gd_1E4_s32 *)arg0)->v + 4)) >> (u32)(32 - ((struct gd_1E0_s32 *)arg0)->v));
                    } else {
                        sp14 = ((struct gd_234_s32 *)arg0)->v;
                    }
                    if ((sp14 == 435) || (sp14 == 440)) {
                        return;
                    }
                    if (arg0 == 0) {
                    }
                    if (((struct gd_1E8_s32 *)arg0)->v < 2) {
                        func_800887D8(arg0);
                    }
                    ((struct n64dk_p1E4_4 *)arg0)->v++;
                    ((struct gd_1E8_s32 *)arg0)->v--;
                    ((struct gd_234_s32 *)arg0)->v = (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) << ((struct gd_1E0_s32 *)arg0)->v;
                }
            }
        }
    } else {
        if ((sp14 == 435) || (sp14 == 440)) {
            (*(s32 *)((struct gd_1E4_s32 *)arg0)->v) = sp14;
            ((struct gd_1E8_s32 *)arg0)->v = 1;
            return;
        }
    }
    goto L31;
L178: ;
    func_800A4CBC(1);
}
