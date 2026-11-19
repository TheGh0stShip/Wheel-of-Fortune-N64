typedef signed char s8;
typedef signed int s32;

struct n64dk_r12 { s32 w[3]; };

extern s32 func_8002B094;
extern s32 D_800B96B4;
s32 func_8000A56C(s32 arg0, s32 arg1);
s32 func_8000ACE8(s32 arg0);
void func_80016B9C(s32 arg0);

struct n64dk_r12 func_8002B904(s32 arg1) {
    s32 event;
    struct n64dk_r12 ret;
    s8 pad0;

    ret.w[1] = 1;
    ret.w[0] = 0;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            ret.w[0] = 30 / D_800B96B4;
            return ret;
        }
    }
    func_80016B9C(20);
    func_8000A56C((s32)&func_8002B094, 0x6000000);
    ret.w[1] = 0;
    ret.w[0] = 0;
    return ret;
}
