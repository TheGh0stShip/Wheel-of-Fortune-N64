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
extern s32 D_8004B7A8;
extern s32 D_800B96C8;
extern s32 D_800BCA70;
extern s32 D_800BCC30;
extern s32 D_800BCC68;
extern s32 D_800BCCA0;
s32 func_80003944();
s32 func_80003C68();
s32 func_8003A58C();
s32 func_8003E318();
s32 func_80049238();

void func_800037A0(s32 arg0) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20[2];

    sp14 = 0;
    sp1C = 0;
    func_80049238(((s32)&D_800B96C8), ((s32)&sp20), ((s32)&D_800BCC30));
    for (;;) {
        if (sp14 != 0) {
            break;
        }
        func_8003E318(((s32)&D_800BCC30), ((s32)&sp18), 1);
        switch (*(s16 *)sp18) {
        case 1:
            sp10 = func_80003944((*(s32 *)((((u32)D_8004B7A8 % 3) * 4) + ((s32)&D_800BCA70))), sp1C);
            if (sp10 != 0) {
                func_8003E318(((s32)&D_800BCC68), ((s32)&sp18), 1);
                func_80003C68(((struct gd_4_s32 *)sp18)->v);
                sp1C = ((struct gd_4_s32 *)sp18)->v;
            }
            break;
        case 4:
            break;
        case 10:
            sp14 = 1;
            break;
        default:
            break;
        }
    }
    func_8003A58C(((s32)&D_800BCCA0));
}
