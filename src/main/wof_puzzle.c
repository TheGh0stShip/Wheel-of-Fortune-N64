// wof_puzzle.c -- the round and its puzzle: starting a game and a round, laying out the puzzle on
// the board, calling letters and checking whether the puzzle is solved
//
// One object from ResetGame to GetHiddenKinds. ResetGame, StartRound, CallLetter, ShowLetter and
// CheckSolved each end off an 8-byte boundary with the next function right after, which happens only
// inside an object; the data ties in LoadPuzzle, CountLetter and IsVowel: CallLetter's vowels and
// consonants lie between LoadPuzzle's alphabet and the category names. Where the object ends after
// GetHiddenKinds the text does not say. Its read-only data starts at 0x80000560 with LoadPuzzle's;
// it has no RCS run.

#include "wof.h"

u8 alphabet[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
s8 vowelLetters[6] = "AEIOU";
s8 consonantLetters[28] = "BCDFGHJKLMNPQRSTVWXYZ";

// The kinds of puzzle by name, thirty static u8 arrays D_8004BA20..D_8004BB90 that only the entries
// of puzzles point at, and the puzzles themselves: the game's content, which the build takes from
// the cartridge (config/assets.tsv).
#include "assets/puzzleKinds.inc.c"

puzzle_t puzzles[3879] = {
#include "assets/puzzles.inc.c"
};


/*
=====================
ResetGame

Sets the round and the player to the first, clears the scores and starts the first round.
=====================
*/
void ResetGame(void) {
    round = 0;
    prizeTaken = 0;
    if (gameMode == 3) {
        round = 2;
        curPlayer = 2;
    } else {
        curPlayer = 0;
    }
    finalSpin = 0;
    players[0].freeSpin = 0;
    players[1].freeSpin = 0;
    players[2].freeSpin = 0;
    ClearScores();
    StartRound();
}


/*
=====================
StartRound

Sets the round's jackpot and wheel and loads a puzzle of the round's kind not used before.
=====================
*/
void StartRound(void) {
    s32 i;
    s32 kind;

    vowelsOnlyAnnounced = 0;
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

/*
=====================
LoadPuzzle

Reads a puzzle (or takes the text given) and lays it out on the four rows of the board.
=====================
*/
void LoadPuzzle(s32 puzzle, u8 *str) {
    s32 line;
    s32 len;
    s32 col;
    s32 maxLen;
    s32 lines;
    s32 indent;
    u8 *text;
    u8 *p;
    u8 buf[104];

    for (len = 0; len < 3; len++) {
        players[len].score = 0;
        players[len].prize = 0;
        players[len].hasPrize = 0;
    }
    category[0] = 0;
    D_800B9655[0] = 0;
    uncalled[0] = 0;
    for (line = 0; line < 4; line++) {
        for (len = 0; len < 14; len++) {
            puzzleText[line][len] = 32;
            board[line][len] = 32;
        }
        puzzleText[line][14] = 0;
        board[line][14] = 0;
    }
    if (str == 0) {
        StrCopy(category, puzzles[puzzle].category);
        ReadRom(puzzles[puzzle].rom, buf, 101);
        text = buf;
        if (gameMode != 3) {
            puzzles[puzzle].used++;
        }
        curPuzzle = puzzle;
    } else {
        text = str;
    }
    maxLen = 0;
    lines = 0;
    p = text;
    for (line = 0; line < 4; line++) {
        len = StrChr(p, 9) - p;
        if (len != 0) {
            lines++;
            if (len > maxLen) {
                maxLen = len;
            }
        }
        p = p + 1 + len;
    }
    line = 1;
    if (lines >= 3) {
        line = 0;
    }
    indent = 1;
    if (maxLen >= 14) {
        indent = 0;
    } else {
        indent = 7 - maxLen / 2;
    }
    while (lines-- > 0) {
        while ((len = StrChr(text, 9) - text) == 0) {
            text++;
        }
        len = StrChr(text, 9) - text;
        if (line == 0) {
            if (len >= 13) {
                if (lines < 3) {
                    line = 1;
                }
            }
        }
        if (line == 0 || line == 3) {
            col = indent - 1;
        } else {
            col = indent;
        }
        if (col < 0) {
            col = 0;
        }
        StrNCopy(&puzzleText[line][col], text, len);
        text = text + 1 + len;
        line++;
    }
    len = StrChr(text, 10) - text;
    StrNCopy(D_800B9655, text, len);
    D_800B9655[len] = 0;
    StrCopy(uncalled, alphabet);
    for (line = 0; line < 4; line++) {
        for (len = 0; len < 14; len++) {
            switch (puzzleText[line][len]) {
            case ' ':
                board[line][len] = ' ';
                break;
            case '\'':
                board[line][len] = '\'';
                break;
            case '&':
                board[line][len] = '&';
                break;
            case '.':
                board[line][len] = '.';
                break;
            case '-':
                board[line][len] = '-';
                break;
            case '/':
                board[line][len] = '/';
                break;
            case '?':
                board[line][len] = '?';
                break;
            default:
                board[line][len] = '+';
            }
        }
    }
}

/*
=====================
CountLetter

How often a letter is in the puzzle; -1 if it was called already.
=====================
*/
s32 CountLetter(register s32 letter) {
    u8 ch;
    s32 i;
    s32 count;
    u8 *p;

    ch = letter;
    p = StrChr(uncalled, ch);
    if (p == 0) {
        return -1;
    }
    count = 0;
    for (i = 0; i < 4; i++) {
        p = puzzleText[i];
        while (p != 0) {
            p = StrChr(p, ch);
            if (p != 0) {
                count++;
                p++;
            }
        }
    }
    return count;
}

/*
=====================
IsVowel

1 if a letter is in vowels.
=====================
*/
s32 IsVowel(register s32 letter) {
    u8 value;

    value = letter;
    if (StrChr(vowelLetters, value) != 0) {
        return 1;
    }
    return 0;
}


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
                prizeTaken = 1;
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


/*
=====================
ShowLetter

Puts a letter on the board wherever the puzzle has it.
=====================
*/
void ShowLetter(register s32 letter) {
    u8 ch;
    s32 i;
    u8 *p;

    ch = letter;
    for (i = 0; i < 4; i++) {
        p = puzzleText[i];
        while (p != 0) {
            p = StrChr(p, ch);
            if (p != 0) {
                board[i][(p - puzzleText[0]) - i * 21] = ch;
                p++;
            }
        }
    }
}


/*
=====================
CheckSolved

0: consonants are hidden, 2: only vowels are, 1: the puzzle is solved (and banks the round's score
if asked)
=====================
*/
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


/*
=====================
GetHiddenKinds

Which kinds of letters the board still hides: 4 both, 3 consonants, 2 vowels, 1 none.
=====================
*/
s32 GetHiddenKinds(void) {
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
    if (consonants > 0 && vowels > 0) {
        return 4;
    }
    if (consonants == 0 && vowels > 0) {
        return 2;
    }
    if (consonants > 0 && vowels == 0) {
        return 3;
    }
    return 1;
}
