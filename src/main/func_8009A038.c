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

struct n64dk_a80103480 { s32 m0; s32 m4; };
extern struct n64dk_a80103480 D_80103480[];
extern s32 D_801034C0;
extern s32 D_801034C4;
extern s32 D_801034F8;
extern s32 D_801034FC;

void func_8009A038(void) {
    s32 sp0;
    s32 sp4;
    s32 sp8;

    for (sp0 = 0;;) {
        if (sp0 >= 8) {
            break;
        }
        D_80103480[sp0].m0 = -1;
        D_80103480[sp0].m4 = 0;
        sp0++;
    }
    D_801034C0 = 35;
    D_801034C4 = 11;
    sp0 = 9;
    for (;;) {
        if (sp0 >= 15) {
            break;
        }
        D_80103480[sp0].m0 = -1;
        D_80103480[sp0].m4 = 0;
        sp0++;
    }
    D_801034F8 = 34;
    D_801034FC = 11;
    sp0 = 16;
    for (;;) {
        if (sp0 >= 24) {
            break;
        }
        D_80103480[sp0].m0 = -1;
        D_80103480[sp0].m4 = 0;
        sp0++;
    }
    sp8 = 33;
    sp0 = 24;
    for (;;) {
        if (sp0 >= 36) {
            break;
        }
        sp4 = 0;
        for (;;) {
            if (sp4 > 0) {
                break;
            }
            D_80103480[sp0 + sp4].m0 = sp8;
            D_80103480[sp0 + sp4].m4 = 11;
            sp4++;
        }
        sp8--;
        sp0 = sp0 + 1;
    }
    sp0 = 36;
    for (;;) {
        if (sp0 >= 48) {
            break;
        }
        sp4 = 0;
        for (;;) {
            if (sp4 >= 2) {
                break;
            }
            D_80103480[sp0 + sp4].m0 = sp8;
            D_80103480[sp0 + sp4].m4 = 10;
            sp4++;
        }
        sp8--;
        sp0 = sp0 + 2;
    }
    sp0 = 48;
    for (;;) {
        if (sp0 >= 96) {
            break;
        }
        sp4 = 0;
        for (;;) {
            if (sp4 >= 8) {
                break;
            }
            D_80103480[sp0 + sp4].m0 = sp8;
            D_80103480[sp0 + sp4].m4 = 8;
            sp4++;
        }
        sp8--;
        sp0 = sp0 + 8;
    }
    sp0 = 96;
    for (;;) {
        if (sp0 >= 128) {
            break;
        }
        sp4 = 0;
        for (;;) {
            if (sp4 >= 16) {
                break;
            }
            D_80103480[sp0 + sp4].m0 = sp8;
            D_80103480[sp0 + sp4].m4 = 7;
            sp4++;
        }
        sp8--;
        sp0 = sp0 + 16;
    }
    sp0 = 128;
    for (;;) {
        if (sp0 >= 256) {
            break;
        }
        sp4 = 0;
        for (;;) {
            if (sp4 >= 64) {
                break;
            }
            D_80103480[sp0 + sp4].m0 = sp8;
            D_80103480[sp0 + sp4].m4 = 5;
            sp4++;
        }
        sp8--;
        sp0 = sp0 + 64;
    }
    sp0 = 256;
    for (;;) {
        if (sp0 >= 512) {
            break;
        }
        sp4 = 0;
        for (;;) {
            if (sp4 >= 128) {
                break;
            }
            D_80103480[sp0 + sp4].m0 = sp8;
            D_80103480[sp0 + sp4].m4 = 4;
            sp4++;
        }
        sp8--;
        sp0 = sp0 + 128;
    }
    sp0 = 512;
    for (;;) {
        if (sp0 >= 1024) {
            break;
        }
        sp4 = 0;
        for (;;) {
            if (sp4 >= 256) {
                break;
            }
            D_80103480[sp0 + sp4].m0 = sp8;
            D_80103480[sp0 + sp4].m4 = 3;
            sp4++;
        }
        sp8--;
        sp0 = sp0 + 256;
    }
    sp0 = 1024;
    for (;;) {
        if (sp0 >= 2048) {
            return;
        }
        sp4 = 0;
        for (;;) {
            if (sp4 >= 1024) {
                break;
            }
            D_80103480[sp0 + sp4].m0 = sp8;
            D_80103480[sp0 + sp4].m4 = 1;
            sp4++;
        }
        sp8--;
        sp0 = sp0 + 1024;
    }
}
