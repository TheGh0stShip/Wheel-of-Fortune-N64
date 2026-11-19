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
struct gd_44_s32 { u8 pad[0x44]; s32 v; };
struct gd_48_s32 { u8 pad[0x48]; s32 v; };
struct gd_4C_s32 { u8 pad[0x4C]; s32 v; };
struct n64dk_e8 { u8 b[8]; };
extern struct n64dk_e8 *D_800B81E8;
s32 func_80005300();
s32 func_80016638();

void func_8002FEB0(s32 arg0, s32 arg1) {
    s32 sp10;

    if (((struct gd_44_s32 *)arg0)->v == 0) {
        return;
    }
    switch (func_80016638()) {
    case 0:
        sp10 = (s32)D_800B81E8++;
        (*(s32 *)sp10) = 0xBC00400A;
        ((struct gd_4_s32 *)sp10)->v = 0xCCCCCCCC;
        sp10 = (s32)D_800B81E8++;
        (*(s32 *)sp10) = 0xBC00440A;
        ((struct gd_4_s32 *)sp10)->v = 0xCCCCCCCC;
        sp10 = (s32)D_800B81E8++;
        (*(s32 *)sp10) = 0xBC00600A;
        ((struct gd_4_s32 *)sp10)->v = 0xCCCCCCCC;
        sp10 = (s32)D_800B81E8++;
        (*(s32 *)sp10) = 0xBC00640A;
        ((struct gd_4_s32 *)sp10)->v = 0xCCCCCCCC;
        sp10 = (s32)D_800B81E8++;
        (*(s32 *)sp10) = 0xBB000001;
        ((struct gd_4_s32 *)sp10)->v = -1;
        sp10 = (s32)D_800B81E8++;
        (*(s32 *)sp10) = 0xE7000000;
        ((struct gd_4_s32 *)sp10)->v = 0;
        sp10 = (s32)D_800B81E8++;
        (*(s32 *)sp10) = 0xB900031D;
        ((struct gd_4_s32 *)sp10)->v = 0x553078;
        sp10 = (s32)D_800B81E8++;
        (*(s32 *)sp10) = 0xFC127E24;
        ((struct gd_4_s32 *)sp10)->v = -3079;
        sp10 = (s32)D_800B81E8++;
        (*(s32 *)sp10) = 0xFD100000;
        ((struct gd_4_s32 *)sp10)->v = ((struct gd_44_s32 *)arg0)->v;
        sp10 = (s32)D_800B81E8++;
        (*(s32 *)sp10) = 0xF5100000;
        ((struct gd_4_s32 *)sp10)->v = 0x7098250;
        sp10 = (s32)D_800B81E8++;
        (*(s32 *)sp10) = 0xE6000000;
        ((struct gd_4_s32 *)sp10)->v = 0;
        sp10 = (s32)D_800B81E8++;
        (*(s32 *)sp10) = 0xF3000000;
        ((struct gd_4_s32 *)sp10)->v = 0x77FF100;
        sp10 = (s32)D_800B81E8++;
        (*(s32 *)sp10) = 0xE7000000;
        ((struct gd_4_s32 *)sp10)->v = 0;
        sp10 = (s32)D_800B81E8++;
        (*(s32 *)sp10) = 0xF5101000;
        ((struct gd_4_s32 *)sp10)->v = 0x98250;
        sp10 = (s32)D_800B81E8++;
        (*(s32 *)sp10) = 0xF2000000;
        ((struct gd_4_s32 *)sp10)->v = 0x7C0FC;
        sp10 = (s32)D_800B81E8++;
        (*(s32 *)sp10) = 0xE7000000;
        ((struct gd_4_s32 *)sp10)->v = 0;
        sp10 = (s32)D_800B81E8++;
        (*(s32 *)sp10) = 0x6000000;
        ((struct gd_4_s32 *)sp10)->v = ((struct gd_48_s32 *)arg0)->v;
        sp10 = (s32)D_800B81E8++;
        (*(s32 *)sp10) = 0xFD100000;
        ((struct gd_4_s32 *)sp10)->v = ((struct gd_44_s32 *)arg0)->v + 0x1000;
        sp10 = (s32)D_800B81E8++;
        (*(s32 *)sp10) = 0xF5100000;
        ((struct gd_4_s32 *)sp10)->v = 0x7098250;
        sp10 = (s32)D_800B81E8++;
        (*(s32 *)sp10) = 0xE6000000;
        ((struct gd_4_s32 *)sp10)->v = 0;
        sp10 = (s32)D_800B81E8++;
        (*(s32 *)sp10) = 0xF3000000;
        ((struct gd_4_s32 *)sp10)->v = 0x77FF100;
        sp10 = (s32)D_800B81E8++;
        (*(s32 *)sp10) = 0xE7000000;
        ((struct gd_4_s32 *)sp10)->v = 0;
        sp10 = (s32)D_800B81E8++;
        (*(s32 *)sp10) = 0xF5101000;
        ((struct gd_4_s32 *)sp10)->v = 0x98250;
        sp10 = (s32)D_800B81E8++;
        (*(s32 *)sp10) = 0xF2000000;
        ((struct gd_4_s32 *)sp10)->v = 0x7C0FC;
        sp10 = (s32)D_800B81E8++;
        (*(s32 *)sp10) = 0x6000000;
        ((struct gd_4_s32 *)sp10)->v = ((struct gd_4C_s32 *)arg0)->v;
        sp10 = (s32)D_800B81E8++;
        (*(s32 *)sp10) = 0xE7000000;
        ((struct gd_4_s32 *)sp10)->v = 0;
        func_80005300(3);
        func_80005300(4);
        sp10 = (s32)D_800B81E8++;
        (*(s32 *)sp10) = 0xB900031D;
        ((struct gd_4_s32 *)sp10)->v = 0x552078;
    }
}
