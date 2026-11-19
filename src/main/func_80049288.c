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

M2C_UNK osCreateMesgQueue();
M2C_UNK osCreateThread();
M2C_UNK osCreateViManager();
M2C_UNK osSetEventMesg();
M2C_UNK osStartThread();
M2C_UNK osViBlack();
M2C_UNK osViSetEvent();
M2C_UNK osViSetMode();
extern M2C_UNK D_800843C8;
extern M2C_UNK func_80048F7C;
void func_80049288(void *arg0, s32 arg1, s32 arg2, u8 arg3, u8 arg4)
{
  void *temp_s1_25;
  void *temp_s1_64;
  *((s32 *) (((s8 *) arg0) + 0x274)) = 0;
  *((s32 *) (((s8 *) arg0) + 0x278)) = 0;
  *((s32 *) (((s8 *) arg0) + 0x260)) = 0;
  *((s32 *) (((s8 *) arg0) + 0x27C)) = 0;
  *((s32 *) (((s8 *) arg0) + 0x264)) = 0;
  *((s32 *) (((s8 *) arg0) + 0x268)) = 0;
  *((s32 *) (((s8 *) arg0) + 0x26C)) = 0;
  *((s32 *) (((s8 *) arg0) + 0x270)) = 0;
  *((s16 *) (((s8 *) arg0) + 0)) = 1;
  *((s16 *) (((s8 *) arg0) + 0x20)) = 4;
  temp_s1_25 = (void *) (((u8 *) arg0) + 0x40);
  osCreateMesgQueue(temp_s1_25, (void *) (((u8 *) arg0) + 0x58), 8);
  osCreateMesgQueue((void *) (((u8 *) arg0) + 0x78), (void *) (((u8 *) arg0) + 0x90), 8);
  osCreateViManager(0xFE);
  osViSetMode((M2C_UNK *) ((arg3 * 0x50) + ((u8 *) (&D_800843C8))));
  osViBlack(1);
  osSetEventMesg(4, temp_s1_25, 0x29B);
  osSetEventMesg(9, temp_s1_25, 0x29C);
  osSetEventMesg(0xE, temp_s1_25, 0x29D);
  osViSetEvent(temp_s1_25, 0x29A, arg4);
  temp_s1_64 = (void *) (((u8 *) arg0) + 0xB0);
  osCreateThread(temp_s1_64, 4, &func_80048F7C, arg0, arg1, arg2);
  osStartThread(temp_s1_64);
}

