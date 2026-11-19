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

struct gd_48_s32 { u8 pad[0x48]; s32 v; };
extern s32 D_01092090;
extern s32 func_80012D40;
extern s32 D_800579F0;
extern s32 D_80057A20;
extern s32 D_80057A58;
extern s32 D_80057A90;
extern s32 D_800B9D08;
extern s32 D_800B9E58;
extern s32 D_800B9FE0;
extern s32 D_800BA168;
s32 func_8000A4A4();
s32 func_8000A990();
s32 func_8000B5DC();
s32 func_80015848();
s32 func_80015EDC();

void func_800161A8(void) {
    s32 sp10;
    s32 sp14;

    sp14 = func_8000B5DC(0x1010000, -1);
    if (sp14 == 0) {
        sp14 = func_80015848(0, 0, ((s32)&func_80012D40), 0x1010000);
    } else {
        sp10 = func_8000A990(0x1010100, -1);
        if (sp10 != 0) {
            func_8000A4A4(sp10, 0);
        }
        sp10 = func_8000A990(0x1010200, -1);
        if (sp10 != 0) {
            func_8000A4A4(sp10, 0);
        }
    }
    ((struct gd_48_s32 *)sp14)->v = (s32)&D_01092090;
    func_80015EDC(((s32)&D_800579F0), ((s32)&D_800B9D08), 0, 12);
    func_80015EDC(((s32)&D_80057A20), ((s32)&D_800B9E58), 1, 14);
    func_80015EDC(((s32)&D_80057A58), ((s32)&D_800B9FE0), 2, 14);
    func_80015EDC(((s32)&D_80057A90), ((s32)&D_800BA168), 3, 12);
}
