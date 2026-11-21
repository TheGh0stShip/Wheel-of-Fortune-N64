#include "wof.h"


s32 CheckSolved(s32 bank) {
    s32 row;
    s32 consonants;
    s32 vowels;
    u8 *p;
    u8 c;

    vowels = 0;
    consonants = 0;
    for (row = 0; row < 4; row++) {
        p = board[row];
        while (p != 0) {
            p = StrChr(p, 43);
            if (p != 0) {
                c = puzzleText[row][p - board[0] - row * 21];
                switch (c) {
                case 'A':
                case 'E':
                case 'I':
                case 'O':
                case 'U':
                    vowels++;
                    break;
                default:
                    consonants++;
                }
                p++;
            }
        }
    }
    if (consonants > 0) {
        return 0;
    }
    if (consonants == 0 && vowels > 0) {
        canSpin = 0;
        return 2;
    }
    if (bank != 0) {
        if (jackpotWon != 0) {
            StartCelebration();
            players[curPlayer].score += jackpot;
        }
        if (players[curPlayer].score < 500) {
            players[curPlayer].score = 500;
        }
        players[curPlayer].total += players[curPlayer].score;
        players[curPlayer].total += players[curPlayer].prize;
        players[0].hasPrize = 0;
        players[1].hasPrize = 0;
        players[2].hasPrize = 0;
    }
    return 1;
}
