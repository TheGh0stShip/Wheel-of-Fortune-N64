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

struct n64dk_a80058234 { s32 m0; u8 pad4[0xC]; };
extern struct n64dk_a80058234 D_80058234[];
extern s32 D_80086D58;
extern s32 D_800B40C4;
extern s32 D_800B81E4;
extern s32 D_800B96A4;
extern s32 D_800B998C;
extern s32 D_800BCA0C;
extern s32 D_800BCA28;
s32 func_8000B978();
s32 func_8000B9FC();
s32 func_80021908();
s32 func_8009CEC0();
s32 func_8009D244();
s32 func_800A4E58();

void func_80021B4C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp10;
    s32 pad0;
    s32 sp18;

    if (D_80086D58 != 0) {
        func_8000B9FC(1);
        func_800A4E58(0);
    }
    D_800B96A4 = 1;
    D_800B998C = arg2;
    D_800B81E4 = arg3;
    D_800BCA28 = arg0;
    D_800BCA0C = func_8000B978();
    D_800B40C4 = 0;
    sp18 = func_80021908(arg0);
    func_8009CEC0(sp18, D_80058234[arg0].m0);
    sp10 = 1;
    for (;;) {
        if (sp10 >= arg1) {
            break;
        }
        func_8009D244();
        sp10++;
    }
    func_800A4E58(0);
    func_8000B9FC(1);
    D_800B96A4 = 0;
}
