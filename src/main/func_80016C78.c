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

struct gd_4_f32 { u8 pad[0x4]; f32 v; };
struct gd_4_s32 { u8 pad[0x4]; s32 v; };
struct gd_8_f32 { u8 pad[0x8]; f32 v; };
struct gd_C_f32 { u8 pad[0xC]; f32 v; };
struct gd_10_f32 { u8 pad[0x10]; f32 v; };
struct gd_10_s16 { u8 pad[0x10]; s16 v; };
struct gd_12_s16 { u8 pad[0x12]; s16 v; };
struct gd_14_f32 { u8 pad[0x14]; f32 v; };
struct gd_14_s16 { u8 pad[0x14]; s16 v; };
struct gd_18_f32 { u8 pad[0x18]; f32 v; };
struct gd_18_s32 { u8 pad[0x18]; s32 v; };
struct gd_28_s32 { u8 pad[0x28]; s32 v; };
struct gd_2C_s32 { u8 pad[0x2C]; s32 v; };
struct gd_30_s32 { u8 pad[0x30]; s32 v; };
struct n64dk_e8 { u8 b[8]; };
struct n64dk_a8005EB48 { f32 m0; f32 m4; f32 m8; f32 mC; f32 m10; f32 m14; f32 m18; f32 m1C; f32 m20; };
extern struct n64dk_a8005EB48 D_8005EB48[];
extern f32 D_80000E8C;
extern f32 D_80000E90;
extern f32 D_80000E94;
extern s32 D_8004B7B8;
extern s32 D_8004B7C0;
extern s32 D_8004B7D0;
extern s32 D_8004B7E0;
extern s32 D_8004B7F0;
extern s32 D_8004B800;
extern s32 D_8004B810;
extern s32 D_800B3994;
extern s32 D_800B6198;
extern f32 D_800B6BE8;
extern f32 D_800B6BEC;
extern f32 D_800B6BF0;
extern struct n64dk_e8 *D_800B81E8;
extern s32 D_800BA5D8;
extern s32 D_800BCD54;
s32 func_8003BEA8();
s32 func_8003C048();
s32 func_8003C2A8();
s32 func_8003E248(s32, s32, s32, s32, f32, f32, f32);
s32 func_80041018();
s32 func_8004A460(s32, f32, f32, f32, f32, f32, f32, f32, f32, f32);

void func_80016C78(s32 arg0, s32 arg1) {
    s32 sp28;
    u16 sp2C;
    s32 sp30[12];
    f32 sp60;
    f32 sp64;
    f32 sp68;
    s32 sp70[16];
    s32 spB0[16];
    s32 spF0[12];
    f32 sp120;
    f32 sp124;
    f32 sp128;
    s32 pad0;
    s32 sp130;

    func_8003E248(arg1, ((s32)&sp2C), 0x42040000, 0x3FAAAAAB, D_80000E8C, D_80000E90, ((struct gd_18_f32 *)arg0)->v);
    sp130 = (s32)D_800B81E8++;
    (*(s32 *)sp130) = 0xBC00000E;
    ((struct gd_4_s32 *)sp130)->v = sp2C;
    if (D_800BCD54 == 1) {
        sp28 = D_800B3994;
        if (sp28 < 0) {
            sp28 = 0;
        }
        if ((D_800B6198 - 1) < sp28) {
            sp28 = D_800B6198 - 1;
        }
        func_8004A460((arg1 + 64), D_8005EB48[sp28].m0, D_8005EB48[sp28].m4, D_8005EB48[sp28].m8, D_8005EB48[sp28].mC, D_8005EB48[sp28].m10, D_8005EB48[sp28].m14, D_8005EB48[sp28].m18, D_8005EB48[sp28].m1C, D_8005EB48[sp28].m20);
    } else {
        if (D_800BA5D8 != 0) {
            if (((D_800B6BE8 + D_800B6BEC) + D_800B6BF0) == 0.0f) {
                func_8004A460((arg1 + 64), (*(f32 *)D_800BA5D8), ((struct gd_4_f32 *)D_800BA5D8)->v, ((struct gd_8_f32 *)D_800BA5D8)->v, ((struct gd_C_f32 *)D_800BA5D8)->v, ((struct gd_10_f32 *)D_800BA5D8)->v, ((struct gd_14_f32 *)D_800BA5D8)->v, 0.0f, D_80000E94, 0.0f);
            } else {
                func_8004A460((arg1 + 64), (*(f32 *)D_800BA5D8), ((struct gd_4_f32 *)D_800BA5D8)->v, ((struct gd_8_f32 *)D_800BA5D8)->v, ((struct gd_C_f32 *)D_800BA5D8)->v, ((struct gd_10_f32 *)D_800BA5D8)->v, ((struct gd_14_f32 *)D_800BA5D8)->v, D_800B6BE8, D_800B6BEC, D_800B6BF0);
            }
        } else {
            func_8003C2A8(((s32)&sp30), 0, 0, 0xC47A0000);
            func_8003C048(((s32)&sp70), ((struct gd_18_s32 *)arg0)->v, ((struct gd_18_s32 *)arg0)->v, ((struct gd_18_s32 *)arg0)->v);
            func_8003BEA8(((s32)&spB0), ((struct gd_28_s32 *)arg0)->v, ((struct gd_2C_s32 *)arg0)->v, ((struct gd_30_s32 *)arg0)->v);
            func_80041018(((s32)&sp30), ((s32)&sp70), ((s32)&sp30));
            func_80041018(((s32)&sp30), ((s32)&spB0), ((s32)&sp30));
            func_8003C2A8(((s32)&spF0), 0, 0x3F800000, 0);
            func_8003C048(((s32)&sp70), ((struct gd_18_s32 *)arg0)->v, ((struct gd_18_s32 *)arg0)->v, ((struct gd_18_s32 *)arg0)->v);
            func_8003BEA8(((s32)&spB0), ((struct gd_28_s32 *)arg0)->v, ((struct gd_2C_s32 *)arg0)->v, ((struct gd_30_s32 *)arg0)->v);
            func_80041018(((s32)&spF0), ((s32)&sp70), ((s32)&spF0));
            func_80041018(((s32)&spF0), ((s32)&spB0), ((s32)&spF0));
            func_8004A460((arg1 + 64), ((f32)((struct gd_10_s16 *)arg0)->v), ((f32)((struct gd_12_s16 *)arg0)->v), ((f32)((struct gd_14_s16 *)arg0)->v), (sp60 + ((f32)((struct gd_10_s16 *)arg0)->v)), (sp64 + ((f32)((struct gd_12_s16 *)arg0)->v)), (sp68 + ((f32)((struct gd_14_s16 *)arg0)->v)), sp120, sp124, sp128);
        }
    }
    sp130 = (s32)D_800B81E8++;
    (*(s32 *)sp130) = 0x1030040;
    ((struct gd_4_s32 *)sp130)->v = arg1;
    sp130 = (s32)D_800B81E8++;
    (*(s32 *)sp130) = 0x1010040;
    ((struct gd_4_s32 *)sp130)->v = arg1 + 64;
    sp130 = (s32)D_800B81E8++;
    (*(s32 *)sp130) = 0xBC000002;
    ((struct gd_4_s32 *)sp130)->v = 0x800000E0;
    sp130 = (s32)D_800B81E8++;
    (*(s32 *)sp130) = 0x3860010;
    ((struct gd_4_s32 *)sp130)->v = (s32)&D_8004B7C0;
    sp130 = (s32)D_800B81E8++;
    (*(s32 *)sp130) = 0x3880010;
    ((struct gd_4_s32 *)sp130)->v = (s32)&D_8004B7D0;
    sp130 = (s32)D_800B81E8++;
    (*(s32 *)sp130) = 0x38A0010;
    ((struct gd_4_s32 *)sp130)->v = (s32)&D_8004B7E0;
    sp130 = (s32)D_800B81E8++;
    (*(s32 *)sp130) = 0x38C0010;
    ((struct gd_4_s32 *)sp130)->v = (s32)&D_8004B7F0;
    sp130 = (s32)D_800B81E8++;
    (*(s32 *)sp130) = 0x38E0010;
    ((struct gd_4_s32 *)sp130)->v = (s32)&D_8004B800;
    sp130 = (s32)D_800B81E8++;
    (*(s32 *)sp130) = 0x3900010;
    ((struct gd_4_s32 *)sp130)->v = (s32)&D_8004B810;
    sp130 = (s32)D_800B81E8++;
    (*(s32 *)sp130) = 0x3920010;
    ((struct gd_4_s32 *)sp130)->v = (s32)&D_8004B7B8;
}
