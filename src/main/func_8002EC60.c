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

struct n64dk_a8005A4C8 { s32 m0; u8 pad4[0x24]; s32 m28; u8 pad2C[0x24]; };
extern struct n64dk_a8005A4C8 D_8005A4C8[];
struct n64dk_a8005ADE0 { s32 m0; u8 pad4[0x24]; };
extern struct n64dk_a8005ADE0 D_8005ADE0[][7];
extern s32 func_800278F0;
extern s32 func_8002CBF4;
extern s32 D_800B9974;
extern s32 D_800BCA14;
s32 func_8000A56C();
s32 func_80027218();
s32 func_8002EDC0();

void func_8002EC60(void) {
    s32 sp10;
    s32 sp14;
    s32 sp18;

    for (sp14 = 0;;) {
        if (sp14 >= 3) {
            break;
        }
        D_8005A4C8[sp14].m0 = 0;
        D_8005A4C8[sp14].m28 = 0;
        sp18 = 0;
        for (;;) {
            if (sp18 >= 7) {
                break;
            }
            D_8005ADE0[sp14][sp18].m0 = 0;
            sp18++;
        }
        sp14++;
    }
    func_8002EDC0();
    sp10 = func_8000A56C(((s32)&func_8002CBF4), 0x5000000);
    func_80027218(sp10, 0, ((s32)&func_800278F0), 0x5000000);
    D_800BCA14 = 0;
    D_800B9974 = 0;
}
