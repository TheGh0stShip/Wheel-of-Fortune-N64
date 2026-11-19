typedef signed char s8;
typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x000 */ u8 unk_000[0x204];
    /* 0x204 */ s32 unk_204;
    /* 0x208 */ s32 unk_208;
} Stream;

void func_800A46FC(void *arg0, s8 *arg1, s32 *arg2);
void func_800A4888(void *arg0, s32 *arg1);
s32 func_800A4920(u8 arg0, s32 arg1, s32 arg2);
s32 func_800A4A18(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_800A3A3C(s32 arg0, s32 arg1, s32 arg2) {
    s32 count;
    s32 buf[2];
    s32 sp20;
    u8 sp24;
    s32 sp28;

    count = func_800A4A18((s32)buf, 1, 8, ((Stream *)arg2)->unk_208);
    if (count < 8) {
        ((Stream *)arg2)->unk_204 = 1;
        return 1;
    }
    func_800A46FC(buf, (s8 *)&sp24, &sp20);
    sp28 = func_800A4920(sp24, sp20, arg0);
    func_800A4888((u8 *)buf + 5, (s32 *)arg1);
    *(s32 *)arg1 = *(s32 *)arg1 * 50;
    return 0;
}
