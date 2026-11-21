#include "wof.h"


void StartRound(void) {
    s32 i;
    s32 kind;

    D_800BEE54 = 0;
    if (gameMode == 3) {
        round = 2;
    }
    if (round == 2) {
        jackpot = 5000;
    } else {
        jackpot = 0;
    }
    D_800B9980 = 0;
    if (round != 6) {
        InitWheel();
    }
    switch (round) {
    case 1:
    case 2:
        kind = 2;
        break;
    case 6:
        kind = 0;
        break;
    default:
        kind = 1;
    }
    i = puzzleRanges[kind].base + Random(puzzleRanges[kind].range);
    if (gameMode != 3) {
        while (puzzles[i].used != 0) {
            i = puzzleRanges[kind].base + Random(puzzleRanges[kind].range);
        }
    }
    LoadPuzzle(i, 0);
    canSpin = round < 6;
    canBuyVowel = 0;
    canSolve = 0;
    for (i = 0; i < 3; i++) {
        players[i].unk_010 = 0;
    }
}
