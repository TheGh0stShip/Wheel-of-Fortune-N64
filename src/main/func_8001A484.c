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

struct n64dk_a800B39A0 { s32 m0; s32 m4; };
extern struct n64dk_a800B39A0 D_800B39A0[];
struct n64dk_a800B99A4 { s32 m0; u8 pad4[0x110]; };
extern struct n64dk_a800B99A4 D_800B99A4[];
extern s32 D_800BCD54;
s32 func_80017C00();
s32 func_8001A424();
s32 func_8001A5D0();
s32 func_8001D320();
s32 func_8001D3CC();

void func_8001A484(void) {
    s32 pad0[2];
    s32 sp18;

    func_8001A5D0();
    sp18 = 0;
    for (;;) {
        if (sp18 >= 3) {
            break;
        }
        if (D_800BCD54 == 3) {
            func_8001D320(sp18);
        } else {
            if (D_800B99A4[sp18].m0 < 4) {
                func_8001A424(sp18);
            } else {
                func_8001D3CC(sp18);
            }
        }
        D_800B39A0[sp18].m0 = 0;
        D_800B39A0[sp18].m4 = 0;
        sp18++;
    }
    if (D_800BCD54 == 3) {
        func_80017C00(17, 0);
        return;
    }
    func_80017C00(3, 0);
}
