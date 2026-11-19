typedef signed int s32;
extern s32 D_80000E10;
extern s32 D_800579F0;
extern s32 D_80057A20;
extern s32 D_80057A58;
extern s32 D_80057A90;
extern s32 D_800B9544;
extern s32 D_800B9601;
extern s32 D_800B9616;
extern s32 D_800B962B;
extern s32 D_800B9640;
extern s32 D_800B9D08;
extern s32 D_800B9E58;
extern s32 D_800B9FE0;
extern s32 D_800BA168;
void func_80012D40();
s32 func_80002CE0(s32 arg0);
void func_80009F98(s32 arg0);
s32 func_8000B5DC(s32 arg0, s32 arg1);
s32 func_80015848(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80015940(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_80015D4C(void) {
    s32 obj;

    func_80009F98((s32)&D_800B9544);
    func_80009F98((s32)&D_80000E10);
    func_80009F98((s32)&D_800B9601);
    func_80009F98((s32)&D_80000E10);
    func_80009F98((s32)&D_800B9616);
    func_80009F98((s32)&D_80000E10);
    func_80009F98((s32)&D_800B962B);
    func_80009F98((s32)&D_80000E10);
    func_80009F98((s32)&D_800B9640);
    func_80009F98((s32)&D_80000E10);
    obj = func_8000B5DC(0x1010000, -1);
    if (obj == 0) {
        func_80015848(0, 0, (s32)func_80012D40, 0x1010000);
    }
    func_80015940((s32)&D_800579F0, (s32)&D_800B9D08, 0, 12);
    func_80015940((s32)&D_80057A20, (s32)&D_800B9E58, 1, 14);
    func_80015940((s32)&D_80057A58, (s32)&D_800B9FE0, 2, 14);
    func_80015940((s32)&D_80057A90, (s32)&D_800BA168, 3, 12);
    func_80002CE0(20);
}
