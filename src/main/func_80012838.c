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
struct n64dk_e8 { u8 b[8]; };
extern s32 D_010A2B88;
extern struct n64dk_e8 *D_800B81E8;
extern s32 D_800BCD54;
s32 func_80005300();
s32 func_8001277C();

void func_80012838(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp10;
    s32 sp14;

    if (D_800BCD54 != 6) {
        sp10 = 0;
        for (;;) {
            if (sp10 >= arg1) {
                break;
            }
            if (arg2 != 0) {
                if (((struct gd_4_s32 *)((sp10 * 28) + arg0))->v == ((s32)&D_010A2B88)) {
                    func_80005300(2);
                    sp14 = (s32)D_800B81E8++;
                    (*(s32 *)sp14) = 0xE7000000;
                    ((struct gd_4_s32 *)sp14)->v = 0;
                    sp14 = (s32)D_800B81E8++;
                    (*(s32 *)sp14) = 0x6000000;
                    ((struct gd_4_s32 *)sp14)->v = *(s32 *)((sp10 * 28) + arg0);
                }
            } else {
                if (((struct gd_4_s32 *)((sp10 * 28) + arg0))->v != ((s32)&D_010A2B88)) {
                    sp14 = (s32)D_800B81E8++;
                    (*(s32 *)sp14) = 0xBC00200A;
                    ((struct gd_4_s32 *)sp14)->v = func_8001277C(((sp10 * 28) + arg0));
                    sp14 = (s32)D_800B81E8++;
                    (*(s32 *)sp14) = 0xBC00240A;
                    ((struct gd_4_s32 *)sp14)->v = func_8001277C(((sp10 * 28) + arg0));
                    sp14 = (s32)D_800B81E8++;
                    (*(s32 *)sp14) = 0xE7000000;
                    ((struct gd_4_s32 *)sp14)->v = 0;
                    sp14 = (s32)D_800B81E8++;
                    (*(s32 *)sp14) = 0xFD900000;
                    ((struct gd_4_s32 *)sp14)->v = ((struct gd_4_s32 *)((sp10 * 28) + arg0))->v;
                    sp14 = (s32)D_800B81E8++;
                    (*(s32 *)sp14) = 0xF5900000;
                    ((struct gd_4_s32 *)sp14)->v = 0x7094250;
                    sp14 = (s32)D_800B81E8++;
                    (*(s32 *)sp14) = 0xE6000000;
                    ((struct gd_4_s32 *)sp14)->v = 0;
                    sp14 = (s32)D_800B81E8++;
                    (*(s32 *)sp14) = 0xF3000000;
                    ((struct gd_4_s32 *)sp14)->v = 0x71FF200;
                    sp14 = (s32)D_800B81E8++;
                    (*(s32 *)sp14) = 0xE7000000;
                    ((struct gd_4_s32 *)sp14)->v = 0;
                    sp14 = (s32)D_800B81E8++;
                    (*(s32 *)sp14) = 0xF5880800;
                    ((struct gd_4_s32 *)sp14)->v = 0x94250;
                    sp14 = (s32)D_800B81E8++;
                    (*(s32 *)sp14) = 0xF2000000;
                    ((struct gd_4_s32 *)sp14)->v = 0x7C07C;
                    sp14 = (s32)D_800B81E8++;
                    (*(s32 *)sp14) = 0xE7000000;
                    ((struct gd_4_s32 *)sp14)->v = 0;
                    sp14 = (s32)D_800B81E8++;
                    (*(s32 *)sp14) = 0x6000000;
                    ((struct gd_4_s32 *)sp14)->v = *(s32 *)((sp10 * 28) + arg0);
                }
            }
            sp10++;
        }
        return;
    }
    sp10 = 0;
    for (;;) {
        if (sp10 >= arg1) {
            return;
        }
        func_80005300(2);
        sp14 = (s32)D_800B81E8++;
        (*(s32 *)sp14) = 0xE7000000;
        ((struct gd_4_s32 *)sp14)->v = 0;
        sp14 = (s32)D_800B81E8++;
        (*(s32 *)sp14) = 0x6000000;
        ((struct gd_4_s32 *)sp14)->v = *(s32 *)((sp10 * 28) + arg0);
        sp10++;
    }
}
