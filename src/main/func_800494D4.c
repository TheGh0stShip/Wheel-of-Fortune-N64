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

s32 __osSpDeviceBusy();                             /* extern */
s32 __osSpRawStartDma(); /* extern */
s32 __osSpSetPc();                           /* extern */
void *func_800493B8();                        /* extern */
M2C_UNK func_80049E08();                     /* extern */
M2C_UNK osWritebackDCache();         /* extern */
struct Fields_var_sp1C
{
  char pad_0[0x4];
  s32 unk_4;
  void *unk_8;
  s32 unk_C;
  s32 unk_10;
  char pad_14[0x4];
  s32 unk_18;
  s32 unk_1C;
  char pad_20[0x18];
  s32 unk_38;
  s32 unk_3C;
};
struct Fields_var_arg0
{
  char pad_0[0x4];
  s32 unk_4;
  char pad_8[0x30];
  s32 unk_38;
};

void func_800494D4(struct Fields_var_arg0 *arg0)
{
  struct Fields_var_sp1C *sp1C;
  sp1C = func_800493B8(arg0);
  if (sp1C->unk_4 & 1)
  {
    sp1C->unk_18 = (s32) sp1C->unk_38;
    sp1C->unk_1C = (s32) sp1C->unk_3C;
    arg0->unk_4 = (s32) (arg0->unk_4 & (~1));
    if (sp1C->unk_4 & 4)
    {
      sp1C->unk_10 = (s32) (*((s32 *) ((arg0->unk_38 + 0xBFC) | 0xA0000000)));
    }
  }
  osWritebackDCache(sp1C, 0x40);
  func_80049E08(0x2B00);
  if (__osSpSetPc(0x04001000) == (-1))
  {
    do
    {
    }
    while (__osSpSetPc(0x04001000) == (-1));
  }
  if (__osSpRawStartDma(1, 0x04000FC0, sp1C, 0x40) == (-1))
  {
    do
    {
    }
    while (__osSpRawStartDma(1, 0x04000FC0, sp1C, 0x40) == (-1));
  }
  if (__osSpDeviceBusy() != 0)
  {
    do
    {
    }
    while (__osSpDeviceBusy() != 0);
  }
  if (__osSpRawStartDma(1, 0x04001000, sp1C->unk_8, sp1C->unk_C) == (-1))
  {
    do
    {
    }
    while (__osSpRawStartDma(1, 0x04001000, sp1C->unk_8, sp1C->unk_C) == (-1));
  }
}


