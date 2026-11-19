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
struct gd_8_s32 { u8 pad[0x8]; s32 v; };
struct gd_18_s32 { u8 pad[0x18]; s32 v; };
struct gd_1C_s32 { u8 pad[0x1C]; s32 v; };
struct gd_20_s32 { u8 pad[0x20]; s32 v; };
struct gd_44_s32 { u8 pad[0x44]; s32 v; };
struct gd_4C_s32 { u8 pad[0x4C]; s32 v; };
struct n64dk_e72 { u8 b[72]; };
struct n64dk_a8005C3A0 { s32 m0; s32 m4; };
extern struct n64dk_a8005C3A0 D_8005C3A0[];
struct n64dk_a8005C7F0 { s32 m0; s32 m4; s32 m8; u8 padC[0xC]; s32 m18; s32 m1C; s32 m20; };
extern struct n64dk_a8005C7F0 D_8005C7F0[];
struct n64dk_a800B99A8 { s32 m0; u8 pad4[0x110]; };
extern struct n64dk_a800B99A8 D_800B99A8[];
extern s32 D_80001A0C;
extern s32 func_8002FEB0;
extern s32 D_8005C3B8;
extern s32 D_800B61A8;
extern s32 D_800B96AC;
extern s32 D_800B9988;
extern s32 D_800BCA60;
extern s32 D_800BCD54;
s32 func_80009F38();
s32 func_8000B924();
s32 func_8000B978();
s32 func_80015848();
s32 func_80021B4C();
s32 func_80032AD4();
s32 func_80032B10();

void func_80032BF0(void) {
    s32 sp10;
    s32 pad0;
    void *sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;

    sp28 = 0x2000000;
    if (D_800BCD54 == 3) {
        sp1C = 0;
        for (;;) {
            if (sp1C >= 3) {
                break;
            }
            D_800B99A8[sp1C].m0 = sp1C;
            sp1C++;
        }
    }
    D_800BCA60 = func_8000B978();
    sp1C = 0;
    for (;;) {
        if (sp1C >= 3) {
            break;
        }
        if (D_800B99A8[sp1C].m0 >= 6) {
            func_80009F38(((s32)&D_80001A0C));
        }
        sp18 = (void *)&((struct n64dk_e72 *)&D_8005C3B8)[D_800B99A8[sp1C].m0];
        sp20 = 0;
        for (;;) {
            if (sp20 >= 2) {
                break;
            }
            if (((struct gd_8_s32 *)((sp20 * 36) + ((s32)sp18)))->v > 0) {
                sp24 = ((*(s32 *)((sp20 * 36) + ((s32)sp18))) * ((struct gd_4_s32 *)((sp20 * 36) + ((s32)sp18)))->v) * 2;
                ((struct gd_18_s32 *)((sp20 * 36) + ((s32)sp18)))->v = func_8000B924((sp24 * ((struct gd_8_s32 *)((sp20 * 36) + ((s32)sp18)))->v));
                func_80021B4C(((struct gd_1C_s32 *)((sp20 * 36) + ((s32)sp18)))->v, ((struct gd_8_s32 *)((sp20 * 36) + ((s32)sp18)))->v, ((struct gd_18_s32 *)((sp20 * 36) + ((s32)sp18)))->v, ((struct gd_20_s32 *)((sp20 * 36) + ((s32)sp18)))->v);
            } else {
                ((struct gd_18_s32 *)((sp20 * 36) + ((s32)sp18)))->v = 0;
            }
            sp20++;
        }
        sp1C++;
    }
    sp1C = 0;
    for (;;) {
        if (sp1C >= 6) {
            break;
        }
        sp24 = (D_8005C7F0[sp1C].m0 * D_8005C7F0[sp1C].m4) * 2;
        D_8005C7F0[sp1C].m18 = func_8000B924((sp24 * D_8005C7F0[sp1C].m8));
        func_80021B4C(D_8005C7F0[sp1C].m1C, D_8005C7F0[sp1C].m8, D_8005C7F0[sp1C].m18, D_8005C7F0[sp1C].m20);
        sp1C++;
    }
    D_800B61A8 = 1;
    D_800B9988 = 0;
    sp1C = 0;
    for (;;) {
        if (sp1C >= 3) {
            break;
        }
        sp10 = func_80015848(0, D_8005C3A0[sp1C].m0, ((s32)&func_8002FEB0), (sp1C | 0xA020000));
        ((struct gd_4C_s32 *)sp10)->v = D_8005C3A0[sp1C].m4;
        ((struct gd_44_s32 *)sp10)->v = 0;
        sp1C++;
    }
    func_80032B10();
    func_80032AD4(4);
    D_800B96AC = 0;
}
