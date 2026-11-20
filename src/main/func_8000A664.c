#include "wof.h"

typedef struct {
    /* 0x00 */ s32 value;
    /* 0x04 */ s32 kind;
} Result;

typedef struct Task {
    /* 0x00 */ void (*func)(Result *, struct Task *);
    /* 0x04 */ u8 unk_04[0x4];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ u8 unk_18[0x28];
    /* 0x40 */ struct Task *next;
} Task;

extern s32 D_80000894;
extern Task D_800B82A0;

void func_8000A664(void) {
    Result res;
    s32 pad0[2];
    Task *task;

    task = &D_800B82A0;
    while (task->next != 0) {
        task = task->next;
        if (task->func == 0) {
            func_80009F38(&D_80000894);
            return;
        }
        if (task->unk_14 == 0) {
            if (task->unk_0C > 0) {
                if (D_800BCD54 != 6) {
                    task->unk_0C--;
                }
            } else {
                if (D_800BCD54 == 6) {
                    if (task->unk_08 == 0xB000000) {
                        task->func(&res, task);
                    }
                } else {
                    task->func(&res, task);
                }
                switch (res.kind) {
                case 0:
                    func_8000A4A4((s32)task, res.value);
                    break;
                case 1:
                    task->unk_0C = res.value;
                    break;
                case 2:
                    task->unk_10 = res.value;
                    task->unk_14 = 1;
                    break;
                case 3:
                    task->unk_10 = res.value;
                    break;
                }
            }
        }
    }
}
