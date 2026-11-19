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

extern s32 D_80000E10;
extern s32 func_80012D40;
extern s32 D_800579F0;
extern s32 D_80057A20;
extern s32 D_80057A58;
extern s32 D_80057A90;
extern s32 D_800B9544;
extern s32 D_800B9601;
extern s32 D_800B9616;
extern s32 D_800B962B;
extern s32 D_800B9640;
extern s32 D_800B9D08;
extern s32 D_800B9E58;
extern s32 D_800B9FE0;
extern s32 D_800BA168;
s32 func_80002CE0();
s32 func_80009F98();
s32 func_8000B5DC();
s32 func_80015848();
s32 func_80015940();

void func_80015D4C(void) {
    s32 sp10;

    func_80009F98(((s32)&D_800B9544));
    func_80009F98(((s32)&D_80000E10));
    func_80009F98(((s32)&D_800B9601));
    func_80009F98(((s32)&D_80000E10));
    func_80009F98(((s32)&D_800B9616));
    func_80009F98(((s32)&D_80000E10));
    func_80009F98(((s32)&D_800B962B));
    func_80009F98(((s32)&D_80000E10));
    func_80009F98(((s32)&D_800B9640));
    func_80009F98(((s32)&D_80000E10));
    sp10 = func_8000B5DC(0x1010000, -1);
    if (sp10 == 0) {
        func_80015848(0, 0, ((s32)&func_80012D40), 0x1010000);
    }
    func_80015940(((s32)&D_800579F0), ((s32)&D_800B9D08), 0, 12);
    func_80015940(((s32)&D_80057A20), ((s32)&D_800B9E58), 1, 14);
    func_80015940(((s32)&D_80057A58), ((s32)&D_800B9FE0), 2, 14);
    func_80015940(((s32)&D_80057A90), ((s32)&D_800BA168), 3, 12);
    func_80002CE0(20);
}
