#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} Pair;

extern s32 D_80001534;
extern s32 D_80001538;
extern s32 D_8000153C;
extern Pair *D_80107884;

void func_80020150(s32 arg0, s32 arg1) {
    if (D_800BCD54 == 6) {
        return;
    }
    switch (D_800B96A4) {
    case 0:
        switch ((u32)D_80107884->unk_00) {
        case 112:
            func_8001EFF0(arg0, arg1);
            return;
        case 96:
            func_8001DAF0(arg0, arg1);
            return;
        case 64:
            func_8001D440(arg0, arg1);
            return;
        }
        func_80009D78(D_80107884->unk_00);
        func_80009F98((s32)&D_80001534);
        func_80009D78(D_80107884->unk_04);
        func_80009F98((s32)&D_80001538);
        func_80009F38(&D_8000153C);
    }
}
