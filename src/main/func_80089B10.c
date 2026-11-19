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
struct gd_1F4_s32 { u8 pad[0x1F4]; s32 v; };
struct gd_1F8_s32 { u8 pad[0x1F8]; s32 v; };
struct gd_1FC_s32 { u8 pad[0x1FC]; s32 v; };
struct gd_200_s32 { u8 pad[0x200]; s32 v; };
struct gd_20C_s32 { u8 pad[0x20C]; s32 v; };
struct gd_214_s32 { u8 pad[0x214]; s32 v; };
struct gd_234_s32 { u8 pad[0x234]; s32 v; };
struct gd_25C_s32 { u8 pad[0x25C]; s32 v; };
struct gd_260_s32 { u8 pad[0x260]; s32 v; };
struct n64dk_e4 { u8 b[4]; };
struct n64dk_p1E4_4 { u8 pad[0x1E4]; struct n64dk_e4 *v; };
extern s32 D_80086D18;
extern s32 D_80086D20;
s32 func_800887D8();
s32 func_800888C0();
s32 func_80088C58();
s32 func_8008A34C();
s32 func_8008B560();
s32 func_8008C0A8();
s32 func_8008CDB8();
s32 func_8008D220();
s32 func_800962DC();
s32 func_8009CAD8();
s32 func_800A2D38();
s32 func_800A2D84();

s32 func_80089B10(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp10;
    s32 sp14;
    s32 sp18;

    if (arg1 == 0) {
        return 0;
    }
    if (arg2 != 0) {
        ((struct gd_1F8_s32 *)arg1)->v = -1;
        ((struct gd_1FC_s32 *)arg1)->v = 0;
        ((struct gd_200_s32 *)arg1)->v = 0;
        ((struct gd_20C_s32 *)arg1)->v = 0;
        ((struct gd_214_s32 *)arg1)->v = 0;
        func_80088C58(arg1);
        if (((struct gd_1E8_s32 *)arg1)->v < 2) {
            func_800887D8(arg1);
        }
        if (((struct gd_1E0_s32 *)arg1)->v != 0) {
            sp10 = ((struct gd_234_s32 *)arg1)->v | ((u32)(*(s32 *)(((struct gd_1E4_s32 *)arg1)->v + 4)) >> (u32)(32 - ((struct gd_1E0_s32 *)arg1)->v));
        } else {
            sp10 = ((struct gd_234_s32 *)arg1)->v;
        }
        if (sp10 != 435) {
            return 0;
        }
    } else {
        ((struct gd_234_s32 *)arg1)->v = (*(s32 *)((struct gd_1E4_s32 *)arg1)->v) << ((struct gd_1E0_s32 *)arg1)->v;
    }
    if (((struct gd_1E8_s32 *)arg1)->v < 2) {
        func_800887D8(arg1);
    }
    if (((struct gd_1E0_s32 *)arg1)->v != 0) {
        sp10 = ((struct gd_234_s32 *)arg1)->v | ((u32)(*(s32 *)(((struct gd_1E4_s32 *)arg1)->v + 4)) >> (u32)(32 - ((struct gd_1E0_s32 *)arg1)->v));
    } else {
        sp10 = ((struct gd_234_s32 *)arg1)->v;
    }
    switch ((u32)sp10) {
    case 439:
    case 441:
        if (((struct gd_25C_s32 *)arg1)->v != 0) {
            ((struct gd_260_s32 *)arg1)->v = ((struct gd_25C_s32 *)arg1)->v;
            func_8009CAD8(arg1, arg3);
        }
        if (D_80086D20 == 0) {
        }
        ((struct gd_1F4_s32 *)arg1)->v = 1;
        if (D_80086D18 != 0) {
            func_800A2D38(arg1);
        }
        goto L394;
        break;
    case 435:
        if (func_8008A34C(arg1, arg3) != 1) {
            goto L391;
        }
        if (((struct gd_20C_s32 *)arg1)->v > 0) {
            func_800A2D84(arg1);
        }
        goto L394;
    case 440:
        if (func_8008B560(arg1) != 1) {
            goto L391;
        }
        goto L394;
    case 256:
        sp18 = func_8008C0A8(arg1, arg0);
        if (sp18 == -10) {
            func_80088C58(arg1);
            for (;;) {
                if (func_800888C0(32, 256, arg1) != 0) {
                    break;
                }
                if (func_800888C0(32, 440, arg1) != 0) {
                    break;
                } else {
                    if (func_800888C0(32, 439, arg1) != 0) {
                        break;
                    }
                }
                if (arg1 == 0) {
                }
                if (((struct gd_1E8_s32 *)arg1)->v < 2) {
                    func_800887D8(arg1);
                }
                ((struct gd_1E0_s32 *)arg1)->v = ((struct gd_1E0_s32 *)arg1)->v + 24;
                if ((((struct gd_1E0_s32 *)arg1)->v & 32) != 0) {
                    ((struct gd_1E8_s32 *)arg1)->v--;
                    ((struct gd_1E0_s32 *)arg1)->v = ((struct gd_1E0_s32 *)arg1)->v - 32;
                    ((struct n64dk_p1E4_4 *)arg1)->v++;
                    ((struct gd_234_s32 *)arg1)->v = (*(s32 *)((struct gd_1E4_s32 *)arg1)->v) << ((struct gd_1E0_s32 *)arg1)->v;
                } else {
                    ((struct gd_234_s32 *)arg1)->v = ((struct gd_234_s32 *)arg1)->v << 24;
                }
                func_80088C58(arg1);
            }
            goto L394;
        } else {
            if (sp18 != 1) {
                goto L391;
            }
        }
        if (func_8008CDB8(arg1) != 1) {
            goto L391;
        }
        break;
    case 436:
        if (arg1 == 0) {
        }
        if (((struct gd_1E8_s32 *)arg1)->v < 2) {
            func_800887D8(arg1);
        }
        ((struct n64dk_p1E4_4 *)arg1)->v++;
        ((struct gd_1E8_s32 *)arg1)->v--;
        ((struct gd_234_s32 *)arg1)->v = (*(s32 *)((struct gd_1E4_s32 *)arg1)->v) << ((struct gd_1E0_s32 *)arg1)->v;
        func_80088C58(arg1);
        goto L394;
    default:
        if ((u32)sp10 >= 257) {
            if ((u32)sp10 < 432) {
                if (func_8008CDB8(arg1) != 1) {
                    goto L391;
                }
            }
        }
        break;
    }
    sp14 = 0;
    for (;;) {
        if (sp14 >= 100) {
            break;
        }
        if (func_800888C0(23, 0, arg1) == 0) {
            if (func_8008D220(arg1) != 1) {
                goto L391;
            }
        } else {
            func_80088C58(arg1);
            if (((struct gd_1E8_s32 *)arg1)->v < 2) {
                func_800887D8(arg1);
            }
            if (((struct gd_1E0_s32 *)arg1)->v != 0) {
                sp10 = ((struct gd_234_s32 *)arg1)->v | ((u32)(*(s32 *)(((struct gd_1E4_s32 *)arg1)->v + 4)) >> (u32)(32 - ((struct gd_1E0_s32 *)arg1)->v));
            } else {
                sp10 = ((struct gd_234_s32 *)arg1)->v;
            }
            if (((u32)sp10 < 257) || ((u32)sp10 >= 432)) {
                if (sp10 != 436) {
                    func_800962DC(arg1, arg3);
                }
            }
            goto L394;
        }
        sp14++;
    }
    if (func_800888C0(23, 0, arg1) != 0) {
        func_80088C58(arg1);
        if (((struct gd_1E8_s32 *)arg1)->v < 2) {
            func_800887D8(arg1);
        }
        if (((struct gd_1E0_s32 *)arg1)->v != 0) {
            sp10 = ((struct gd_234_s32 *)arg1)->v | ((u32)(*(s32 *)(((struct gd_1E4_s32 *)arg1)->v + 4)) >> (u32)(32 - ((struct gd_1E0_s32 *)arg1)->v));
        } else {
            sp10 = ((struct gd_234_s32 *)arg1)->v;
        }
        if (((u32)sp10 < 257) || ((u32)sp10 >= 432)) {
            func_800962DC(arg1, arg3);
        }
    }
    goto L394;
L391: ;
    func_80088C58(arg1);
    goto L394;
L394: ;
    return arg1;
}
