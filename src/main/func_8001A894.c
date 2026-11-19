typedef unsigned char u8;
typedef signed int s32;
typedef float f32;
extern f32 D_800011C4;
extern s32 D_800B61C0;
s32 func_80009C98(s32 arg0);
void func_8001A628(s32 arg0);
s32 func_8001A6DC(s32 arg0);
s32 func_8001A7A8(s32 arg0);

s32 func_8001A894(f32 arg0, s32 arg1) {
    f32 roll;
    u8 result;

    func_8001A628((s32)&D_800B61C0);
    roll = func_80009C98(100);
    roll = roll / D_800011C4;
    if (roll < arg0) {
        result = func_8001A7A8((s32)&D_800B61C0);
    } else {
        result = func_8001A6DC((s32)&D_800B61C0);
        if (result == 32) {
            result = func_8001A7A8((s32)&D_800B61C0);
        }
    }
    return result;
}
