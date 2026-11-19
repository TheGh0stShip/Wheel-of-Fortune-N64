typedef unsigned char u8;
typedef signed int s32;
typedef signed long long s64;
typedef unsigned long long u64;
struct gd_4_s32 { u8 pad[0x4]; s32 v; };
extern u64 D_80084218;
u64 func_80044988();

s32 func_800A4F74(s32 arg0, ...) {
    s32 sp10;

    sp10 = (s32)func_80044988();
    (*(s32 *)arg0) = (s32)(sp10 / D_80084218);
    sp10 = (s32)(sp10 % D_80084218);
    ((struct gd_4_s32 *)arg0)->v = (s32)(((s64)sp10 * 0xF4240) / D_80084218);
    return 0;
}
