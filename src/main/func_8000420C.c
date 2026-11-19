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

struct n64dk_a800A70A0 { u16 m0; u8 m2; u8 pad3[0x1]; };
extern struct n64dk_a800A70A0 D_800A70A0[];
struct n64dk_a800BEE60 { s32 m0; u8 pad4[0xC]; };
extern struct n64dk_a800BEE60 D_800BEE60[];
extern s32 D_800004C0;
extern s32 func_80004160;
extern s32 func_80004F6C;
extern s16 D_800A70C8;
extern s32 D_800A70E8;
extern s32 D_800A9298;
extern s32 D_800AB448;
extern s32 D_800B3970;
extern s32 D_800B6AE8[][16];
extern s32 D_800B6BF4;
extern u8 D_800B96C4;
extern s32 D_800B9D04;
extern s32 D_800BCD68;
extern s32 D_800BCD70;
extern s32 D_800BEE58;
s32 func_80004EB0();
s32 func_80009F98();
s32 func_8003A368();
s32 func_8003E608();
s32 func_8003E6C8();
s32 func_800447D8();
s32 func_80045498();
s32 func_80046808();
s32 func_80048458();

void func_8000420C(void) {
    s32 sp18;
    s32 sp1C;
    s32 sp20;

    D_800B96C4 = 0;
    func_80045498(((s32)&D_800BCD70), ((s32)&D_800B6BF4), 1);
    func_8003E6C8(((s32)&D_800A70E8), 8, ((s32)&func_80004F6C), 0, ((s32)&D_800A9298), 10);
    func_800447D8(((s32)&D_800A70E8));
    sp18 = 0;
    for (;;) {
        if (sp18 >= 4) {
            break;
        }
        D_800BEE60[sp18].m0 = 0;
        sp18++;
    }
    func_80045498(((s32)&D_800B3970), ((s32)&D_800BCD68), 1);
    func_8003E6C8(((s32)&D_800A9298), 9, ((s32)&func_80004160), 0, ((s32)&D_800AB448), 9);
    D_800A70C8 = 5;
    func_8003E608(5, ((s32)&D_800B3970), ((s32)&D_800A70C8));
    if ((sp18 = (s32)func_80048458(((s32)&D_800B3970), ((s32)&D_800B96C4), ((s32)&D_800A70A0))) != 0) {
        func_80009F98(((s32)&D_800004C0));
    }
    sp18 = 0;
    for (;;) {
        if (sp18 >= 4) {
            break;
        }
        if (((D_800B96C4 >> sp18) % 2) != 0) {
            if ((D_800A70A0[sp18].m0 & 4) != 0) {
                if ((D_800A70A0[sp18].m2 & 1) != 0) {
                    sp20 = func_80046808(((s32)&D_800B3970), ((sp18 * 104) + ((s32)&D_800AB448)), sp18);
                    if ((sp20 == 10) || (sp20 == 11)) {
                        sp20 = func_8003A368(((s32)&D_800B3970), ((sp18 * 104) + ((s32)&D_800AB448)), sp18);
                        if (sp20 == 0) {
                            D_800BEE60[sp18].m0 = 1;
                            func_80004EB0(sp18);
                        } else {
                        }
                    } else {
                        if (sp20 == 0) {
                        }
                    }
                }
            }
        }
        (*(s16 *)((sp18 * 2) + ((s32)&D_800BEE58))) = 0;
        sp1C = 0;
        for (;;) {
            if (sp1C >= 16) {
                break;
            }
            D_800B6AE8[sp18][sp1C] = 0;
            sp1C++;
        }
        sp18++;
    }
    D_800B9D04 = 0;
    func_800447D8(((s32)&D_800A9298));
}
