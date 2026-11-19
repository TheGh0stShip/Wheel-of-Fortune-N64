typedef signed int s32;
typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} Pair;

extern Pair D_800FF2F8[];

void func_8009BAE0(void) {
    s32 i;
    s32 j;
    s32 value;

    value = 16;
    for (i = 0; i < 24; i++) {
        D_800FF2F8[i].unk_00 = -1;
        D_800FF2F8[i].unk_04 = 0;
    }
    i = 24;
    while (i < 36) {
        for (j = 0; j <= 0; j++) {
            D_800FF2F8[i + j].unk_00 = value;
            D_800FF2F8[i + j].unk_04 = 11;
        }
        for (j = 1; j < 2; j++) {
            D_800FF2F8[i + j].unk_00 = -value;
            D_800FF2F8[i + j].unk_04 = 11;
        }
        value--;
        i += 2;
    }
    i = 36;
    while (i < 48) {
        for (j = 0; j < 2; j++) {
            D_800FF2F8[i + j].unk_00 = value;
            D_800FF2F8[i + j].unk_04 = 10;
        }
        for (j = 2; j < 4; j++) {
            D_800FF2F8[i + j].unk_00 = -value;
            D_800FF2F8[i + j].unk_04 = 10;
        }
        value--;
        i += 4;
    }
    i = 48;
    while (i < 96) {
        for (j = 0; j < 8; j++) {
            D_800FF2F8[i + j].unk_00 = value;
            D_800FF2F8[i + j].unk_04 = 8;
        }
        for (j = 8; j < 16; j++) {
            D_800FF2F8[i + j].unk_00 = -value;
            D_800FF2F8[i + j].unk_04 = 8;
        }
        value--;
        i += 16;
    }
    i = 96;
    while (i < 128) {
        for (j = 0; j < 16; j++) {
            D_800FF2F8[i + j].unk_00 = value;
            D_800FF2F8[i + j].unk_04 = 7;
        }
        for (j = 16; j < 32; j++) {
            D_800FF2F8[i + j].unk_00 = -value;
            D_800FF2F8[i + j].unk_04 = 7;
        }
        value--;
        i += 32;
    }
    i = 128;
    while (i < 256) {
        for (j = 0; j < 64; j++) {
            D_800FF2F8[i + j].unk_00 = value;
            D_800FF2F8[i + j].unk_04 = 5;
        }
        for (j = 64; j < 128; j++) {
            D_800FF2F8[i + j].unk_00 = -value;
            D_800FF2F8[i + j].unk_04 = 5;
        }
        value--;
        i += 128;
    }
    i = 256;
    while (i < 512) {
        for (j = 0; j < 128; j++) {
            D_800FF2F8[i + j].unk_00 = value;
            D_800FF2F8[i + j].unk_04 = 4;
        }
        for (j = 128; j < 256; j++) {
            D_800FF2F8[i + j].unk_00 = -value;
            D_800FF2F8[i + j].unk_04 = 4;
        }
        value--;
        i += 256;
    }
    i = 512;
    while (i < 1024) {
        for (j = 0; j < 256; j++) {
            D_800FF2F8[i + j].unk_00 = value;
            D_800FF2F8[i + j].unk_04 = 3;
        }
        for (j = 256; j < 512; j++) {
            D_800FF2F8[i + j].unk_00 = -value;
            D_800FF2F8[i + j].unk_04 = 3;
        }
        value--;
        i += 512;
    }
    i = 1024;
    while (i < 2048) {
        for (j = 0; j < 512; j++) {
            D_800FF2F8[i + j].unk_00 = value;
            D_800FF2F8[i + j].unk_04 = 1;
        }
        for (j = 512; j < 1024; j++) {
            D_800FF2F8[i + j].unk_00 = -value;
            D_800FF2F8[i + j].unk_04 = 1;
        }
        value--;
        i += 1024;
    }
}
