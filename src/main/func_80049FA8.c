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

/* Provisional declarations recovered from machine code by n64dk. Evidence, not truth. */
struct Struct_func_800396B8_arg0;
struct Struct_func_80039898_arg1;
struct Struct_func_800396B8_arg0 {   /* provisional: 23 field(s) from 28 function(s) */
    /* 0x00 */ u8 unk_0;   /* also accessed as 32-bit */
    /* 0x01 */ u8 unk_1;
    /* 0x02 */ char unk_2[0x2];
    /* 0x04 */ u16 unk_4;   /* also accessed as 32-bit */
    /* 0x06 */ char unk_6[0x2];
    /* 0x08 */ s32 unk_8;
    /* 0x0C */ char unk_C[0x4];
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ struct Struct_func_80039898_arg1 *unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ s32 unk_40;
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ s32 unk_48;
    /* 0x4C */ s32 unk_4C;
    /* 0x50 */ s32 unk_50;
    /* 0x54 */ s32 unk_54;
    /* 0x58 */ s32 unk_58;
};
struct Struct_func_80039898_arg1 {   /* provisional: 2 field(s) from 2 function(s) */
    /* 0x00 */ s32 unk_0;
    /* 0x04 */ s32 unk_4;
};
void func_80049FA8(struct Struct_func_800396B8_arg0 *, s16);

void func_80049FA8(struct Struct_func_800396B8_arg0 *arg0, s16 arg1) {
    arg0->unk_3C = (s32) arg1;
}
