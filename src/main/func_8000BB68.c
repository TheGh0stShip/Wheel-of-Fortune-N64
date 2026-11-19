typedef signed int s32;
typedef s32 M2C_UNK;
M2C_UNK osSendMesg();    /* extern */
extern M2C_UNK D_800BA5B0;

void func_8000BB68(void) {
    osSendMesg(&D_800BA5B0, 0, 0);
}
