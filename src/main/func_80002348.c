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
struct gd_C_s32 { u8 pad[0xC]; s32 v; };
extern s32 D_8004B718;
extern s32 D_8004B71C;
extern s32 D_8006DD04;
extern s32 D_8006DD08;
extern s32 D_8006DD0C;
extern s32 D_800A5084;
extern s32 D_800A5088;
extern s32 D_800A508C;
extern s32 D_800A5090;
extern s32 D_800A509C;
extern s32 D_800B3990;
extern s32 D_800B9960;
extern s32 D_800BED90;
s32 func_800032A8();
s32 func_80006828();
s32 func_8000B924();
s32 func_8003A5F8();
s32 func_8003EA1C();
s32 func_800422B8();
s32 func_8004AABC();

void func_80002348(void) {
    s32 sp10;
    s32 pad0;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 pad1;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    u8 sp34;
    s32 sp38;
    s32 pad2;
    s32 sp40;
    s32 sp44;
    u8 sp48;
    u8 sp49;
    s32 sp4C;
    s32 sp50;
    s32 sp54;
    s32 sp58;
    s32 pad3;
    s32 sp60;
    s32 sp64;
    s32 sp68;
    s32 pad4;
    s32 sp70;
    s32 sp74;

    sp70 = func_8000B924(0x30D40);
    func_8003A5F8(((s32)&D_800B9960), sp70, 0x30D40);
    sp18 = 32;
    sp1C = 32;
    sp20 = 48;
    sp28 = 0;
    sp34 = 6;
    sp30 = 0;
    sp2C = (s32)&D_800B9960;
    sp38 = (s32)&D_8004B71C;
    sp60 = 0x5622;
    sp64 = 1;
    sp68 = 0x1000;
    func_800032A8(((s32)&sp18), 12, ((s32)&sp60));
    sp40 = 32;
    sp44 = 48;
    sp48 = 32;
    sp4C = (s32)&D_800B9960;
    sp50 = 0;
    sp54 = 0;
    sp58 = 0;
    sp49 = 7;
    D_800BED90 = func_8000B924(136);
    func_800422B8(D_800BED90, ((s32)&sp40));
    D_800A5084 = 32;
    D_800A5088 = 64;
    D_800A508C = (s32)&D_800B9960;
    func_8004AABC(D_8004B718, ((s32)&D_800A5084));
    sp10 = D_8006DD08 - D_8006DD04;
    D_800B3990 = func_8000B924(sp10);
    func_80006828(D_8006DD04, D_800B3990, sp10);
    func_8003EA1C(D_800B3990, D_8006DD0C);
    D_800A5090 = ((struct gd_C_s32 *)((struct gd_4_s32 *)D_800B3990)->v)->v;
    D_800A509C = func_8000B924(64);
    sp74 = 0;
    for (;;) {
        if (sp74 >= 32) {
            return;
        }
        (*(s16 *)((sp74 * 2) + D_800A509C)) = -1;
        sp74++;
    }
}
