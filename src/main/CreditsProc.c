// CreditsProc.c -- shows the credits as puzzles on the board, one after another

#include "wof.h"

// The text of the credits and the titles over them, static char arrays D_8005BF90..D_8005C1CC and
// D_8005C240..D_8005C328: the game's content, which the build takes from the cartridge
// (config/assets.tsv).
#include "assets/creditsText.inc.c"
u8 *creditsText[22] = {
    D_8005BF90, D_8005BFB4, D_8005BFD4, D_8005BFE4, D_8005C000, D_8005C018, D_8005C02C, D_8005C03C,
    D_8005C050, D_8005C064, D_8005C078, D_8005C098, D_8005C0AC, D_8005C0C0, D_8005C0EC, D_8005C114,
    D_8005C128, D_8005C150, D_8005C178, D_8005C198, D_8005C1B4, D_8005C1CC
};
#include "assets/creditsTitles.inc.c"
u8 *creditsTitles[22] = {
    NULL, NULL, D_8005C240, D_8005C250, D_8005C25C, D_8005C26C, D_8005C27C, D_8005C28C, D_8005C2A0,
    D_8005C2B4, D_8005C2C8, D_8005C2DC, D_8005C2F0, D_8005C300, NULL, D_8005C30C, D_8005C314,
    D_8005C328, NULL, NULL, NULL, NULL
};


/*
=====================
CreditsProc

Shows the credits as puzzles on the board, one after another.
=====================
*/
struct procResult_s CreditsProc(proc_t *proc) {
    s32 event;
    s32 i;
    struct procResult_s ret;
    s32 unused;  /* NOTE: unused in the original; guess: its type, the frame shows at most 8 bytes */

    ret.w[1] = 1;
    ret.w[0] = 0;
    while ((event = ProcGetMessage(proc)) != 0) {
        switch (event) {
        case 8:
            i = 0;
            for (;;) {
                if (i >= 22) {
                    break;
                }
                categoryImages[i].texture = 0;
                categoryImages[i].dimTexture = 0;
                i++;
            }
            ResetMotors();
            MakeScreenObj(0, 0, func_80028064, 0x5050000);
            proc->data->credits.step = 0;
            gameMode = 8;
            FreeObjClass(0x5050100, -1);
            KillProcClass(0xA000400, -1, 1);
            FreeObjClass(0xA030000, -1);
            PlaySound(21);
            break;
        case 46:
            StopAllSounds();
            ret.w[1] = 1;
            ret.w[0] = 2;
            FreeObjClass(0x1000000, 0xFF000000);
            FreeObjClass(0xA000000, 0xFF000000);
            FreeObjClass(0x4000000, 0xFF000000);
            ProcPostMessage(proc, 35, 0);
            return ret;
        case 35:
            KillOtherProcs(proc);
            InitObjs();
            StopMovie();
            RestartOpening();
            ret.w[1] = 0;
            ret.w[0] = 0;
            return ret;
        }
    }
    if (proc->data->credits.step >= 22) {
        ProcPostMessage(proc, 46, 0);
        return ret;
    }
    ResetBoard();
    LoadPuzzle(0, creditsText[proc->data->credits.step]);
    if (creditsTitles[proc->data->credits.step] != 0) {
        StrCopy(category, creditsTitles[proc->data->credits.step]);
        InitCategory();
    }
    RevealPuzzle();
    proc->data->credits.step++;
    ret.w[0] = 65 / frameRetraces;
    return ret;
}
