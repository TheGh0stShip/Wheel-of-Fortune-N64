typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;
struct n64dk_r12 { s32 w[3]; };

typedef struct {
    /* 0x00 */ u8 unk_00[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 index;
    /* 0x0C */ s32 timer;
} Cursor;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ Cursor *cursor;
} Menu;

typedef struct {
    u8 unk_00[0x20];
} Item;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x110];
} Player;

extern Player D_800B99A8[];
extern s32 D_80001594;
extern Item D_80058868[];
extern s32 D_80058880;
extern s32 D_80058888;
extern s32 D_800588F0;
extern u16 D_800B96B0;
extern s32 D_800B96B4;
extern s8 D_800B9956;
extern s8 D_800B9957;
extern s32 D_800FB808;
s32 func_80002CE0(s32 arg0);
void func_80009F38(s32 *arg0);
s32 func_8000ACE8(s32 arg0);
void func_8000AE70(s32 arg0, s32 arg1, s32 arg2);
void func_80022784(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_800229D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80022BC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80022DC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80022FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80023B44(void);
void func_80025FA8(void);
void func_800263DC(void);
void func_80026800(void);

struct n64dk_r12 func_80023CA4(s32 arg1) {
    s32 event;
    struct n64dk_r12 ret;
    s8 pad0;

    ret.w[1] = 1;
    ret.w[0] = 0;
    while ((event = func_8000ACE8(arg1)) != 0) {
        switch (event) {
        case 8:
            ((Menu *)arg1)->cursor->index = 0;
            ((Menu *)arg1)->cursor->unk_04 = D_80058880;
            func_80022784(arg1, (s32)&D_800588F0, (s32)&D_80058888, 0);
            func_80022784(arg1, (s32)&D_800588F0, (s32)D_80058868, 1);
            return ret;
        }
    }
    if ((D_800B96B0 & 0xA000) & 0xFFFF) {
        ((Menu *)arg1)->cursor->timer = 0;
        func_80002CE0(42);
        switch (((Menu *)arg1)->cursor->index) {
        case 0:
            func_80022BC8(arg1, (s32)&D_800588F0, (s32)D_80058868, 2);
            break;
        case 1:
            if (D_800FB808 >= 2) {
                D_800B99A8[D_800FB808].unk_00 = D_80058880;
                D_800FB808 = 0;
                func_8000AE70(0xA000300, -256, 1);
                func_80026800();
                ret.w[1] = 0;
                ret.w[0] = 1;
                return ret;
            } else {
                D_800B99A8[D_800FB808].unk_00 = D_80058880;
                D_800FB808++;
                func_8000AE70(0xA000300, -256, 1);
                func_800263DC();
                ret.w[1] = 0;
                ret.w[0] = 1;
                return ret;
            }
        default:
            func_80009F38(&D_80001594);
        }
    }
    if ((D_800B96B0 & 0x5000) & 0xFFFF) {
        func_80002CE0(42);
        D_800B99A8[D_800FB808].unk_00 = D_80058880;
        D_800FB808 = 0;
        func_8000AE70(0xA000300, -256, 1);
        func_80025FA8();
        ret.w[1] = 0;
        ret.w[0] = 1;
        return ret;
    } else if ((D_800B96B0 & 0x800) & 0xFFFF) {
        func_800229D0(arg1, (s32)&D_800588F0, (s32)D_80058868, 2);
    } else if ((D_800B96B0 & 0x400) & 0xFFFF) {
        func_80022BC8(arg1, (s32)&D_800588F0, (s32)D_80058868, 2);
    } else if ((D_800B96B0 & 0x200) & 0xFFFF) {
        func_80022DC0(arg1, (s32)&D_800588F0, (s32)&D_80058868[((Menu *)arg1)->cursor->index], 0);
        if (((Menu *)arg1)->cursor->index == 0) {
            func_80023B44();
        }
    } else if ((D_800B96B0 & 0x100) & 0xFFFF) {
        func_80022FE0(arg1, (s32)&D_800588F0, (s32)&D_80058868[((Menu *)arg1)->cursor->index], 0);
        if (((Menu *)arg1)->cursor->index == 0) {
            func_80023B44();
        }
    }
    if (((Menu *)arg1)->cursor->timer <= 0) {
        if (D_800B9956 >= 41) {
            func_80022FE0(arg1, (s32)&D_800588F0, (s32)&D_80058868[((Menu *)arg1)->cursor->index], 0);
            if (((Menu *)arg1)->cursor->index == 0) {
                func_80023B44();
            }
        } else if (D_800B9956 < -40) {
            func_80022DC0(arg1, (s32)&D_800588F0, (s32)&D_80058868[((Menu *)arg1)->cursor->index], 0);
            if (((Menu *)arg1)->cursor->index == 0) {
                func_80023B44();
            }
        }
        if (D_800B9957 >= 41) {
            func_800229D0(arg1, (s32)&D_800588F0, (s32)D_80058868, 2);
        } else if (D_800B9957 < -40) {
            func_80022BC8(arg1, (s32)&D_800588F0, (s32)D_80058868, 2);
        }
    } else {
        ((Menu *)arg1)->cursor->timer = ((Menu *)arg1)->cursor->timer - D_800B96B4;
    }
    return ret;
}
