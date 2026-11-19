typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed int s32;

struct n64dk_r12 { s32 w[3]; };

typedef struct {
    /* 0x00 */ u8 pad0[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 cursor;
    /* 0x0C */ s32 delay;
} MenuData;

typedef struct {
    /* 0x00 */ u8 pad0[0x30];
    /* 0x30 */ MenuData *data;
} Task;

typedef struct {
    u8 b[32];
} Item;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 pad8[0x20];
} Slot;

extern Slot D_80058568[];
extern s32 D_01157868;
extern s32 D_01158068;
extern s32 D_01158868;
extern s32 D_01159068;
extern s32 D_01159868;
extern s32 D_0115B068;
extern s32 D_0115B868;
extern s32 D_0115C068;
extern s32 D_0115C868;
extern s32 D_0115D068;
extern s32 D_80001594;
extern Item D_800584C8[];
extern s32 D_800584E0;
extern s32 D_800584E8;
extern s32 D_80058508;
extern s32 D_80058528;
extern s32 D_80058548;
extern u16 D_800B96B0;
extern s32 D_800B96B4;
extern s8 D_800B9956;
extern s8 D_800B9957;
s32 func_80002CE0(s32 arg0);
void func_80009F38(void *arg0);
s32 func_8000ACE8(s32 arg0);
void func_80022784(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_800229D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80022BC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80022DC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80022FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80023200(void);
void func_800263DC(void);
void func_80026800(void);

struct n64dk_r12 func_800232AC(s32 arg1) {
    s32 event;
    s32 cursor;
    struct n64dk_r12 result;
    s8 pad0;

    result.w[1] = 1;
    result.w[0] = 0;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            ((Task *)arg1)->data->cursor = 0;
            ((Task *)arg1)->data->unk_04 = D_800584E0;
            func_80022784(arg1, (s32)&D_80058548, (s32)&D_800584E8, 0);
            func_80022784(arg1, (s32)&D_80058548, (s32)&D_80058508, 0);
            func_80022784(arg1, (s32)&D_80058548, (s32)&D_80058528, 0);
            func_80022784(arg1, (s32)&D_80058548, (s32)D_800584C8, 1);
            return result;
        }
    }
    if ((D_800B96B0 & 0xA000 & 0xFFFF) != 0) {
        ((Task *)arg1)->data->delay = 0;
        func_80002CE0(42);
        switch (((Task *)arg1)->data->cursor) {
        case 0:
            func_80022BC8(arg1, (s32)&D_80058548, (s32)D_800584C8, 4);
            break;
        case 1:
            func_80022BC8(arg1, (s32)&D_80058548, (s32)D_800584C8, 4);
            break;
        case 2:
            func_80022BC8(arg1, (s32)&D_80058548, (s32)D_800584C8, 4);
            break;
        case 3:
            func_80023200();
            func_800263DC();
            result.w[1] = 0;
            result.w[0] = 1;
            return result;
        default:
            func_80009F38(&D_80001594);
        }
    }
    if ((D_800B96B0 & 0x5000 & 0xFFFF) != 0) {
        func_80002CE0(42);
        func_80023200();
        func_80026800();
        result.w[1] = 0;
        result.w[0] = 1;
        return result;
    } else if ((D_800B96B0 & 2048 & 0xFFFF) != 0) {
        func_800229D0(arg1, (s32)&D_80058548, (s32)D_800584C8, 4);
    } else if ((D_800B96B0 & 1024 & 0xFFFF) != 0) {
        func_80022BC8(arg1, (s32)&D_80058548, (s32)D_800584C8, 4);
    } else if ((D_800B96B0 & 512 & 0xFFFF) != 0) {
        func_80022DC0(arg1, (s32)&D_80058548, (s32)&D_800584C8[((Task *)arg1)->data->cursor], 1);
    } else if ((D_800B96B0 & 256 & 0xFFFF) != 0) {
        func_80022FE0(arg1, (s32)&D_80058548, (s32)&D_800584C8[((Task *)arg1)->data->cursor], 1);
    } else if ((D_800B96B0 & 0x8000 & 0xFFFF) != 0) {
        return result;
    }
    if (((Task *)arg1)->data->delay <= 0) {
        if (D_800B9956 >= 41) {
            func_80022FE0(arg1, (s32)&D_80058548, (s32)&D_800584C8[((Task *)arg1)->data->cursor], 1);
        } else if (D_800B9956 < -40) {
            func_80022DC0(arg1, (s32)&D_80058548, (s32)&D_800584C8[((Task *)arg1)->data->cursor], 1);
        }
        if (D_800B9957 >= 41) {
            func_800229D0(arg1, (s32)&D_80058548, (s32)D_800584C8, 4);
        } else if (D_800B9957 < -40) {
            func_80022BC8(arg1, (s32)&D_80058548, (s32)D_800584C8, 4);
        }
    } else {
        ((Task *)arg1)->data->delay -= D_800B96B4;
    }
    cursor = ((Task *)arg1)->data->cursor;
    if (cursor < 3) {
        switch (((Task *)arg1)->data->unk_04) {
        case 0:
            D_80058568[(cursor * 4) + 10].unk_00 = (s32)&D_01158068;
            D_80058568[(cursor * 4) + 10].unk_04 = (s32)&D_0115B868;
            break;
        case 1:
            D_80058568[(cursor * 4) + 10].unk_00 = (s32)&D_01158868;
            D_80058568[(cursor * 4) + 10].unk_04 = (s32)&D_0115C068;
            break;
        case 2:
            D_80058568[(cursor * 4) + 10].unk_00 = (s32)&D_01159068;
            D_80058568[(cursor * 4) + 10].unk_04 = (s32)&D_0115C868;
            break;
        case 3:
            D_80058568[(cursor * 4) + 10].unk_00 = (s32)&D_01159868;
            D_80058568[(cursor * 4) + 10].unk_04 = (s32)&D_0115D068;
            break;
        case 4:
            D_80058568[(cursor * 4) + 10].unk_00 = (s32)&D_01157868;
            D_80058568[(cursor * 4) + 10].unk_04 = (s32)&D_0115B068;
            break;
        }
    }
    return result;
}
