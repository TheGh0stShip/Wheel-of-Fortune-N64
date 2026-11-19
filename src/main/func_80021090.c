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

struct gd_4_s32 { u8 pad[0x4]; s32 v; };
extern s32 D_80001534;
extern s32 D_80001538;
extern s32 D_8000153C;
extern s32 D_80107884;
s32 func_80009D78();
s32 func_80009F38();
s32 func_80009F98();
s32 func_8001ED48();
s32 func_800202A0();
s32 func_800206C8();
s32 func_80020C98();

void func_80021090(s32 arg0) {
    switch ((u32)(*(s32 *)D_80107884)) {
    case 112:
        func_800202A0(arg0);
        return;
    case 96:
        func_8001ED48(arg0);
        return;
    case 64:
        switch (((struct gd_4_s32 *)D_80107884)->v) {
        case 64:
            func_800206C8(arg0);
            break;
        case 96:
            func_80020C98(arg0);
            break;
        }
        return;
    }
    func_80009D78((*(s32 *)D_80107884));
    func_80009F98(((s32)&D_80001534));
    func_80009D78(((struct gd_4_s32 *)D_80107884)->v);
    func_80009F98(((s32)&D_80001538));
    func_80009F38(((s32)&D_8000153C));
}
