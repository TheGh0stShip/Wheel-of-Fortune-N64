typedef unsigned char u8;
typedef signed int s32;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 index;
    /* 0x0C */ s32 unk_0C;
} State;

typedef struct {
    /* 0x00 */ u8 unk_00[0x30];
    /* 0x30 */ State *state;
} Task;

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04[0x14];
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ void (*callback)(s32);
} Entry;

s32 func_80002CE0(s32 arg0);
void func_80022784(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_80022BC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_80002CE0(44);
    func_80022784(arg0, arg1, (s32)&((Entry *)arg2)[((Task *)arg0)->state->index], 0);
    ((Entry *)arg2)[((Task *)arg0)->state->index].unk_18 = ((Task *)arg0)->state->unk_04;
    do {
        ((Task *)arg0)->state->index++;
        if (((Task *)arg0)->state->index >= arg3) {
            ((Task *)arg0)->state->index = 0;
        }
    } while (((Entry *)arg2)[((Task *)arg0)->state->index].unk_00 == 0);
    ((Task *)arg0)->state->unk_04 = ((Entry *)arg2)[((Task *)arg0)->state->index].unk_18;
    if (((Entry *)arg2)[((Task *)arg0)->state->index].callback != 0) {
        ((Entry *)arg2)[((Task *)arg0)->state->index].callback(((Task *)arg0)->state->index);
    }
    func_80022784(arg0, arg1, (s32)&((Entry *)arg2)[((Task *)arg0)->state->index], 1);
    ((Task *)arg0)->state->unk_0C = 15;
}
