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

s32 func_8003BD34(void *arg0, u32 *arg1)
{
  s32 temp_v0_9;
  s32 var_a2_13;
  u32 temp_a1_92;
  u32 temp_t0_31;
  u32 temp_t0_51;
  u32 temp_t0_72;
  u32 var_v1_7;
  void *temp_a3_24;
  void *temp_a3_44;
  void *temp_a3_65;
  void *temp_a3_86;
  var_v1_7 = -1U;
  temp_v0_9 = *((s32 *) (((s8 *) arg0) + 0x10));
  if ((*((u32 *) (((s8 *) arg0) + 4))) == 0)
  {
    return 0;
  }
  var_a2_13 = 0;
  do
  {
    if ((((u32) (*((u32 *) (((s8 *) arg0) + 4)))) >> var_a2_13) & 1)
    {
      temp_a3_24 = (void *) (((u8 *) arg0) + (var_a2_13 * 4));
      if ((*((s32 *) (((s8 *) arg0) + 0x14))) != 0)
      {
        *((u32 *) (((s8 *) temp_a3_24) + 0xB8)) = (u32) ((*((u32 *) (((s8 *) temp_a3_24) + 0xB8))) - temp_v0_9);
      }
      temp_t0_31 = *((u32 *) (((s8 *) temp_a3_24) + 0xB8));
      if (temp_t0_31 < var_v1_7)
      {
        var_v1_7 = temp_t0_31;
      }
    }
    if (((*((u32 *) (((s8 *) arg0) + 4))) >> (var_a2_13 + 1)) & 1)
    {
      temp_a3_44 = (void *) (((u8 *) arg0) + (var_a2_13 * 4));
      if ((*((s32 *) (((s8 *) arg0) + 0x14))) != 0)
      {
        *((u32 *) (((s8 *) temp_a3_44) + 0xBC)) = (u32) ((*((u32 *) (((s8 *) temp_a3_44) + 0xBC))) - temp_v0_9);
      }
      temp_t0_51 = *((u32 *) (((s8 *) temp_a3_44) + 0xBC));
      if (temp_t0_51 < var_v1_7)
      {
        var_v1_7 = temp_t0_51;
      }
    }
    if (((*((u32 *) (((s8 *) arg0) + 4))) >> (var_a2_13 + 2)) & 1)
    {
      temp_a3_65 = (void *) (((u8 *) arg0) + (var_a2_13 * 4));
      if ((*((s32 *) (((s8 *) arg0) + 0x14))) != 0)
      {
        *((u32 *) (((s8 *) temp_a3_65) + 0xC0)) = (u32) ((*((u32 *) (((s8 *) temp_a3_65) + 0xC0))) - temp_v0_9);
      }
      temp_t0_72 = *((u32 *) (((s8 *) temp_a3_65) + 0xC0));
      if (temp_t0_72 < var_v1_7)
      {
        var_v1_7 = temp_t0_72;
      }
    }
    if (((*((u32 *) (((s8 *) arg0) + 4))) >> (var_a2_13 + 3)) & 1)
    {
      temp_a3_86 = (void *) (((u8 *) arg0) + (var_a2_13 * 4));
      if ((*((s32 *) (((s8 *) arg0) + 0x14))) != 0)
      {
        *((u32 *) (((s8 *) temp_a3_86) + 0xC4)) = (u32) ((*((u32 *) (((s8 *) temp_a3_86) + 0xC4))) - temp_v0_9);
      }
      temp_a1_92 = *((u32 *) (((s8 *) temp_a3_86) + 0xC4));
      if (temp_a1_92 < var_v1_7)
      {
        var_v1_7 = temp_a1_92;
      }
    }
    var_a2_13 += 4;
  }
  while (var_a2_13 != 0x10);
  *((s32 *) (((s8 *) arg0) + 0x14)) = 0;
  *arg1 = var_v1_7;
  return 1;
}

