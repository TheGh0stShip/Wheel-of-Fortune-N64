#include "wof.h"


/*
=====================
CallLetter

Calls a letter for the player: scores it by the wedge and returns how often it is in the puzzle.
=====================
*/
s32 CallLetter(register s32 c, s32 kind) {
    u8 letter;
    s32 i;
    s32 count;
    u8 *p;

    letter = c;
    canSpin = 1;
    canBuyVowel = 1;
    canSolve = 1;
    switch (kind) {
    case 0:
        p = StrChr(consonantLetters, letter);
        if (p == 0) {
            return -3;
        }
        break;
    case 1:
        p = StrChr(vowelLetters, letter);
        if (p == 0) {
            return -2;
        }
        break;
    default:
        p = StrChr(vowelLetters, letter);
        if (p != 0) {
            kind = 1;
        } else {
            kind = 0;
        }
        break;
    }
    p = StrChr(uncalled, letter);
    if (p == 0) {
        return -1;
    }
    uncalled[p - uncalled] = 32;
    count = 0;
    for (i = 0; i < 4; i++) {
        p = puzzleText[i];
        while (p != 0) {
            p = StrChr(p, letter);
            if (p != 0) {
                count++;
                p++;
            }
        }
    }
    if (finalSpin != 0) {
        if (kind == 0) {
            players[curPlayer].score += finalSpinValue * count;
        }
        return count;
    }
    if (count > 0 && kind == 0) {
        if (GetWedgeValue() > 0) {
            if (GetWedgeValue() == 10000) {
                players[curPlayer].prize += 10000;
                D_800B9538 = 1;
                players[curPlayer].hasPrize = 1;
                ClaimWedge();
            } else {
                players[curPlayer].score += GetWedgeValue() * count;
            }
            goto end;
        }
    }
    if (kind != 0) {
        players[curPlayer].score -= 250;
    } else if (count > 0) {
        if (kind == 0) {
            if (GetWedgeValue() < -4) {
                players[curPlayer].freeSpin = 1;
                ClaimWedge();
            end:;
            }
        }
    }
    return count;
}
