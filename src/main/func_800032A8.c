#include "wof.h"

struct gd_4_s32 { u8 pad[0x4]; s32 v; };
struct gd_8_s32 { u8 pad[0x8]; s32 v; };
struct gd_10_s32 { u8 pad[0x10]; s32 v; };
struct gd_14_s32 { u8 pad[0x14]; s32 v; };
struct gd_18_s32 { u8 pad[0x18]; s32 v; };
struct gd_60_s16 { u8 pad[0x60]; s16 v; };
struct gd_64_s32 { u8 pad[0x64]; s32 v; };
struct n64dk_a800BA2D8 { s32 m0; u8 pad4[0x10]; };
extern struct n64dk_a800BA2D8 D_800BA2D8[];
extern f32 D_800004B4;
extern s32 func_800037A0;
extern s32 func_80003F64;
extern s32 D_800A70A0;
extern s32 D_800B96B8;
extern s32 D_800B96BC;
extern s32 D_800B9950;
extern s32 D_800BA2C8;
extern s32 D_800BA2CC;
extern s32 D_800BA2DC;
extern s32 D_800BA598;
extern s8 D_800BA5C8;
extern s32 D_800BCA68;
extern s32 D_800BCA70;
extern s32 D_800BCA80;
extern s32 D_800BCC30;
extern s32 D_800BCC48;
extern s32 D_800BCC68;
extern s32 D_800BCC80;
extern s32 D_800BCCA0;
extern s32 D_800BCD64;
extern s32 D_800BEDA4;
extern s32 D_800FB818;
s32 func_80038758();
s32 func_8003A568();
s32 func_8003A5C4();
s32 func_8003A638();
s32 func_8003E6C8();
s32 func_800447D8();
s32 func_80045498();

void func_800032A8(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp18;
    f32 sp1C;

    D_800BA5C8 = 0;
    D_800B96B8 = 0;
    ((struct gd_10_s32 *)arg0)->v = (s32)&func_80003F64;
    ((struct gd_18_s32 *)arg0)->v = func_80038758((*(s32 *)arg2));
    sp1C = (((f32)((f64)((u32)((struct gd_4_s32 *)arg2)->v))) * ((f32)((struct gd_18_s32 *)arg0)->v)) / 6e+01f;
    D_800BCD64 = (s32)sp1C;
    if (((f32)((f64)((u32)D_800BCD64))) < sp1C) {
        D_800BCD64++;
    }
    if ((D_800BCD64 & 15) != 0) {
        D_800BCD64 = (D_800BCD64 & -16) + 16;
    }
    D_800B96BC = D_800BCD64 - 16;
    D_800B9950 = D_800BCD64 + 96;
    func_8003A5C4(((s32)&D_800BCCA0), arg0);
    D_800BA2CC = 0;
    D_800BA2C8 = 0;
    sp18 = 0;
    for (;;) {
        if ((u32)sp18 >= 35) {
            break;
        }
        func_8003A568(((sp18 * 20) + ((s32)&D_800BA2DC)), ((sp18 * 20) + ((s32)&D_800BA2C8)));
        D_800BA2D8[sp18].m0 = func_8003A638(0, 0, ((struct gd_14_s32 *)arg0)->v, 1, 2048);
        sp18++;
    }
    D_800BA2D8[sp18].m0 = func_8003A638(0, 0, ((struct gd_14_s32 *)arg0)->v, 1, 2048);
    sp18 = 0;
    for (;;) {
        if ((u32)sp18 >= 2) {
            break;
        }
        (*(s32 *)((sp18 * 4) + ((s32)&D_800BCA68))) = func_8003A638(0, 0, ((struct gd_14_s32 *)arg0)->v, 1, (((struct gd_8_s32 *)arg2)->v * 8));
        sp18++;
    }
    D_800BEDA4 = ((struct gd_8_s32 *)arg2)->v;
    sp18 = 0;
    for (;;) {
        if ((u32)sp18 >= 3) {
            break;
        }
        (*(s32 *)((sp18 * 4) + ((s32)&D_800BCA70))) = func_8003A638(0, 0, ((struct gd_14_s32 *)arg0)->v, 1, 128);
        ((struct gd_60_s16 *)(*(s32 *)((sp18 * 4) + ((s32)&D_800BCA70))))->v = 2;
        ((struct gd_64_s32 *)(*(s32 *)((sp18 * 4) + ((s32)&D_800BCA70))))->v = *(s32 *)((sp18 * 4) + ((s32)&D_800BCA70));
        (*(s32 *)(*(s32 *)((sp18 * 4) + ((s32)&D_800BCA70)))) = func_8003A638(0, 0, ((struct gd_14_s32 *)arg0)->v, 1, (D_800B9950 * 4));
        sp18++;
    }
    func_80045498(((s32)&D_800BCC68), ((s32)&D_800BCC80), 8);
    func_80045498(((s32)&D_800BCC30), ((s32)&D_800BCC48), 8);
    func_80045498(((s32)&D_800BA598), ((s32)&D_800FB818), 32);
    func_8003E6C8(((s32)&D_800BCA80), 3, ((s32)&func_800037A0), 0, ((s32)&D_800A70A0), arg1);
    func_800447D8(((s32)&D_800BCA80));
}
