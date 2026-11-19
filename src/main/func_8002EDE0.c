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

struct n64dk_a800B9994 { s32 m0; u8 pad4[0xC]; s32 m10; u8 pad14[0x100]; };
extern struct n64dk_a800B9994 D_800B9994[];
extern s32 func_80028194;
extern s32 func_8002B094;
extern s32 func_8002C094;
extern s32 D_800B619C;
extern s32 D_800BCA00;
extern s32 D_800BCD54;
extern s32 D_800FB808;
s32 func_80005258();
s32 func_80006BFC();
s32 func_8000A56C();
s32 func_8000ABB8();
s32 func_80015D4C();
s32 func_80017C00();
s32 func_8001A5D0();
s32 func_80027218();
s32 func_8002EDC0();

void func_8002EDE0(void) {
    s32 sp10;
    s32 sp14;

    D_800B619C = 6;
    D_800BCD54 = 4;
    D_800BCA00 = 0;
    D_800FB808 = 0;
    sp14 = 0;
    for (;;) {
        if (sp14 >= 3) {
            break;
        }
        if (D_800B9994[sp14].m0 > D_800B9994[D_800FB808].m0) {
            D_800FB808 = sp14;
        }
        sp14++;
    }
    if (D_800B9994[D_800FB808].m10 == 4) {
        func_8000ABB8(42, 0, 0, 1);
        func_8000A56C(((s32)&func_8002B094), 0x6000000);
        return;
    }
    func_80005258();
    func_80017C00(3, 0);
    func_80006BFC();
    func_8000ABB8(42, 0, 0, 1);
    sp10 = func_8000A56C(((s32)&func_8002C094), 0x5050000);
    func_80027218(sp10, 0, ((s32)&func_80028194), 0x5050000);
    func_80015D4C();
    func_8001A5D0();
    func_8002EDC0();
}
