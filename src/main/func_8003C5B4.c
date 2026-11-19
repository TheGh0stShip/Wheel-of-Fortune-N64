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

s32 alHeapDBAlloc(); /* extern */
M2C_UNK func_8003FB08(); /* extern */
extern M2C_UNK alEnvmixerParam;
extern M2C_UNK alEnvmixerPull;
struct Fields_var_arg0
{
  char pad_0[0x14];
  s32 unk_14;
  s16 unk_18;
  s16 unk_1A;
  s16 unk_1C;
  s16 unk_1E;
  s16 unk_20;
  s16 unk_22;
  s16 unk_24;
  s16 unk_26;
  s16 unk_28;
  char pad_2A[0x4];
  s16 unk_2E;
  s32 unk_30;
  s32 unk_34;
  s32 unk_38;
  s32 unk_3C;
  s32 unk_40;
  s32 unk_44;
  s32 unk_48;
};

void func_8003C5B4(struct Fields_var_arg0 *arg0, s32 arg1)
{
  func_8003FB08(arg0, &alEnvmixerPull, &alEnvmixerParam, 4);
  arg0->unk_14 = alHeapDBAlloc(0, 0, arg1, 1, 0x50);
  arg0->unk_38 = 1;
  arg0->unk_48 = 0;
  arg0->unk_1A = 1;
  arg0->unk_28 = 1;
  arg0->unk_2E = 1;
  arg0->unk_1C = 1;
  arg0->unk_1E = 1;
  arg0->unk_20 = 0;
  arg0->unk_22 = 0;
  arg0->unk_26 = 1;
  arg0->unk_24 = 0;
  arg0->unk_30 = 0;
  arg0->unk_34 = 0;
  arg0->unk_18 = 0;
  arg0->unk_3C = 0;
  arg0->unk_40 = 0;
  arg0->unk_44 = 0;
}


