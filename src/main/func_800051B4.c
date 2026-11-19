typedef signed int s32;
typedef float f32;
struct n64dk_a800BEE60 { s32 m0; s32 m4; f32 m8; s32 mC; };
extern struct n64dk_a800BEE60 D_800BEE60[];

void func_800051B4(s32 arg0, s32 arg1, f32 arg2) {
    if (D_800BEE60[arg0].m0 == 0) {
        return;
    }
    D_800BEE60[arg0].mC = arg1;
    D_800BEE60[arg0].m8 = arg2;
    D_800BEE60[arg0].m4 = 0;
}
