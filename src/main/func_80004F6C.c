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
extern s32 D_800AB448;
extern s32 D_800B3970;
extern s32 D_800BCD70;
extern s32 D_800BEDE8;
s32 func_8000BB10();
s32 func_8000BB68();
s32 func_80039F18();
s32 func_8003A080();
s32 func_8003A368();
s32 func_8003E318();

void func_80004F6C(s32 arg0) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s16 sp1C;

    sp10 = 0;
    for (;;) {
        goto L3;
        return;
L3: ;
        func_8003E318(((s32)&D_800BCD70), ((s32)&sp10), 1);
        func_8000BB10();
        sp18 = ((struct gd_4_s32 *)sp10)->v;
        sp1C = *(u16 *)sp10;
        switch (sp1C) {
        case 1:
            sp14 = func_8003A080(((sp18 * 104) + ((s32)&D_800AB448)));
            if (sp14 == 0) {
                (*(s32 *)((sp18 * 4) + ((s32)&D_800BEDE8))) = 1;
            }
            break;
        case 0:
            sp14 = func_80039F18(((sp18 * 104) + ((s32)&D_800AB448)));
            if (sp14 == 0) {
                (*(s32 *)((sp18 * 4) + ((s32)&D_800BEDE8))) = 0;
            }
            break;
        case 2:
            sp14 = func_8003A368(((s32)&D_800B3970), ((sp18 * 104) + ((s32)&D_800AB448)), sp18);
            sp14 = func_80039F18(((sp18 * 104) + ((s32)&D_800AB448)));
            if (sp14 == 0) {
                (*(s32 *)((sp18 * 4) + ((s32)&D_800BEDE8))) = 0;
            }
            break;
        }
        func_8000BB68();
    }
}
