typedef signed int s32;
typedef unsigned char u8;

struct n64dk_r12 { s32 w[3]; };

typedef struct {
    /* 0x00 */ u8 pad0[0x30];
    /* 0x30 */ s32 *unk_30;
} Obj;

void func_8000315C(void);
void func_8000AAB0(s32 arg0, s32 arg1, s32 arg2);
s32 func_8000ACE8(s32 arg0);
void func_8000ADEC(s32 arg0);
void func_8000AF00(void);
void func_8000B9FC(s32 arg0);
void func_8000BBA8(void);
void func_80016B9C(s32 arg0);
void func_800219B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

struct n64dk_r12 func_8000BC64(s32 arg1) {
    struct n64dk_r12 result;
    s32 sp20;
    s32 event;

    sp20 = *((Obj *)arg1)->unk_30;
    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            func_8000315C();
            func_8000AAB0(arg1, 36, 0);
            result.w[1] = 1;
            result.w[0] = 2;
            return result;
        case 36:
            func_8000ADEC(arg1);
            func_8000AF00();
            func_8000B9FC(1);
            func_8000BBA8();
            func_80016B9C(12);
            result.w[1] = 2;
            result.w[0] = 45;
            return result;
        case 45:
            func_80016B9C(3);
            func_800219B8(5, 40, 180, 20);
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        }
    }
    return result;
}
