typedef signed int s32;
typedef s32 M2C_UNK;
M2C_UNK func_8000BAA8();                            /* extern */
M2C_UNK osRecvMesg();  /* extern */
extern s32 D_80057800;
extern M2C_UNK D_800BA5B0;

void func_8000BB10(void) {
    M2C_UNK sp10;

    if (D_80057800 == 0) {
        func_8000BAA8();
    }
    osRecvMesg(&D_800BA5B0, &sp10, 1);
}
