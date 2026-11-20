#include "wof.h"

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
} Pair;

extern s32 D_80001534;
extern s32 D_80001538;
extern s32 D_8000153C;
extern Pair *D_80107884;

void func_80021090(s32 arg0) {
    switch ((u32)D_80107884->unk_00) {
    case 112:
        func_800202A0(arg0);
        return;
    case 96:
        func_8001ED48(arg0);
        return;
    case 64:
        switch (D_80107884->unk_04) {
        case 64:
            func_800206C8(arg0);
            break;
        case 96:
            func_80020C98(arg0);
            break;
        }
        return;
    }
    func_80009D78(D_80107884->unk_00);
    func_80009F98((s32)&D_80001534);
    func_80009D78(D_80107884->unk_04);
    func_80009F98((s32)&D_80001538);
    func_80009F38(&D_8000153C);
}
