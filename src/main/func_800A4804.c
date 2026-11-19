typedef signed char s8;
typedef unsigned char u8;
typedef signed int s32;
typedef unsigned int u32;

void func_800A4804(void *arg0, s8 *arg1, s32 *arg2) {
    *arg1 = (u32)(((u8 *)arg0)[0] & 0x20 & 0xFF) >> 5;
    *arg2 = (((u8 *)arg0)[0] & 0x1F & 0xFF) << 8;
    *arg2 = *arg2 | ((u8 *)arg0)[1];
}
