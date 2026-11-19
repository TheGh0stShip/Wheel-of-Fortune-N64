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

struct n64dk_u6 { s16 w[3]; };
struct gd_4_u8 { u8 pad[0x4]; u8 v; };
struct gd_C_s32 { u8 pad[0xC]; s32 v; };
struct n64dk_e6 { u8 b[6]; };
struct n64dk_a800A70B2 { u8 m0; u8 m1; u8 pad2[0x4]; };
extern struct n64dk_a800A70B2 D_800A70B2[];
struct n64dk_a800B99A4 { s32 m0; u8 pad4[0x110]; };
extern struct n64dk_a800B99A4 D_800B99A4[];
struct n64dk_a800BEE60 { s32 m0; f32 m4; f32 m8; s32 mC; };
extern struct n64dk_a800BEE60 D_800BEE60[];
extern f64 D_800004E0;
extern f64 D_800004E8;
extern s32 D_800A70B0;
extern s32 D_800B6AE8[][16];
extern u16 D_800B96B0;
extern u8 D_800B96C4;
extern s32 D_800B9954;
extern s8 D_800B9956;
extern s8 D_800B9957;
extern s32 D_800B9D04;
extern s32 D_800BCD54;
extern s32 D_800BEDE8;
extern s32 D_800BEE58;
extern s32 D_800FB808;
s32 func_80004E50();
s32 func_80004EB0();
s32 func_800482BC();

void func_800045D4(void) {
    void *sp10;
    u16 sp14;
    s32 sp18;
    u16 sp1C;
    u16 sp1E;

    sp1E = 1;
    func_800482BC(((s32)&D_800A70B0));
    sp14 = 0;
    for (;;) {
        if ((u32)sp14 >= 4) {
            break;
        }
        if (((D_800B96C4 >> sp14) % 2) != 0) {
            sp10 = (void *)&((struct n64dk_e6 *)&D_800A70B0)[sp14];
            switch (((struct gd_4_u8 *)((s32)sp10))->v) {
            case 0:
                if (D_800BEE60[sp14].m0 != 0) {
                    if (D_800BEE60[sp14].mC > 0) {
                        D_800BEE60[sp14].mC--;
                        D_800BEE60[sp14].m4 = D_800BEE60[sp14].m4 + D_800BEE60[sp14].m8;
                        if (((f64)D_800BEE60[sp14].m4) < D_800004E0) {
                            func_80004EB0(sp14);
                        } else {
                            D_800BEE60[sp14].m4 = (f32)(((f64)D_800BEE60[sp14].m4) - D_800004E8);
                            func_80004E50(sp14);
                        }
                    } else {
                        if ((*(s32 *)((sp14 * 4) + ((s32)&D_800BEDE8))) != 0) {
                            func_80004EB0(sp14);
                        }
                    }
                }
                sp1C = *(u16 *)((s32)sp10);
                sp18 = 0;
                for (;;) {
                    if (sp18 >= 16) {
                        break;
                    }
                    if (((sp1C & 1) & 0xFFFF) != 0) {
                        if (D_800B6AE8[sp14][sp18] < 5) {
                            D_800B6AE8[sp14][sp18] = 0;
                        } else {
                            (*(s16 *)((sp14 * 2) + ((s32)&D_800BEE58))) = (*(u16 *)((sp14 * 2) + ((s32)&D_800BEE58))) | (1 << sp18);
                            D_800B6AE8[sp14][sp18] = 0;
                        }
                    } else {
                        if (D_800B6AE8[sp14][sp18] < 6) {
                            D_800B6AE8[sp14][sp18]++;
                        }
                    }
                    sp1C = (u32)sp1C >> 1;
                    sp18++;
                }
            }
        }
        sp14++;
    }
    if (D_800B9D04 != 0) {
        if ((D_800BCD54 == 3) || ((D_800BCD54 == 1) || ((D_800BCD54 == 7) || (D_800BCD54 == 8)))) {
            D_800B9956 = 0;
            D_800B9957 = 0;
            D_800B96B0 = 0;
            sp14 = 0;
            for (;;) {
                if ((u32)sp14 >= 4) {
                    break;
                }
                D_800B96B0 = (*(u16 *)((sp14 * 2) + ((s32)&D_800BEE58))) | D_800B96B0;
                if (((D_800B96C4 >> sp14) % 2) != 0) {
                    if ((((s8)D_800A70B2[sp14].m0) >= 41) || (((s8)D_800A70B2[sp14].m0) < -40)) {
                        D_800B9956 = D_800A70B2[sp14].m0;
                    }
                    if ((((s8)D_800A70B2[sp14].m1) >= 41) || (((s8)D_800A70B2[sp14].m1) < -40)) {
                        D_800B9957 = D_800A70B2[sp14].m1;
                    }
                }
                sp14++;
            }
        } else {
            if ((D_800BCD54 == 6) || (D_800B99A4[D_800FB808].m0 == 4)) {
                D_800B96B0 = 0;
                sp14 = 0;
                for (;;) {
                    if ((u32)sp14 >= 4) {
                        break;
                    }
                    D_800B96B0 = ((*(u16 *)((sp14 * 2) + ((s32)&D_800BEE58))) & 0x1000) | D_800B96B0;
                    sp14++;
                }
            } else {
                D_800B96B0 = *(u16 *)((D_800B99A4[D_800FB808].m0 * 2) + ((s32)&D_800BEE58));
                (*(struct n64dk_u6 *)&D_800B9954) = (*(struct n64dk_u6 *)((D_800B99A4[D_800FB808].m0 * 6) + ((s32)&D_800A70B0)));
            }
        }
        sp14 = 0;
        for (;;) {
            if ((u32)sp14 >= 4) {
                break;
            }
            (*(s16 *)((sp14 * 2) + ((s32)&D_800BEE58))) = 0;
            sp14++;
        }
        D_800B9D04 = 0;
    }
}
