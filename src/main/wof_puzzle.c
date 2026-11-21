// wof_puzzle.c -- the round, its puzzle and its wheel: starting a game and a round, laying out the
// puzzle on the board, calling letters, checking whether the puzzle is solved, the wedges of the wheel
// and the players' scores and turns
//
// One object from ResetGame to NextPlayer. ResetGame, StartRound, CallLetter, ShowLetter, CheckSolved,
// StartSolve, InitWheel, SetWedge, GetWedgeValue, ApplyWedge and ClearScores each end off an 8-byte
// boundary with the next function right after, which happens only inside an object. The data ties in
// the rest: CallLetter's vowels and consonants lie between LoadPuzzle's alphabet and the category
// names; ClaimWedge's read-only items run on into SetWedge's with no 8-byte boundary between; and the
// wheel's wedge tables, which only InitWheel reads, lie below the puzzle's data in .data although
// InitWheel's text lies above ResetGame's, which only one object can do. A 4-byte gap ends the text
// after NextPlayer. Whether NewGame, before ResetGame, is this object's the text does not say. Its
// read-only data starts at 0x80000560 with LoadPuzzle's; it has no RCS run.

#include "wof.h"

// guess: the angle the wheel starts each round at is this object's, as the datum right before the
// wedge tables. It lies between parse_args's data and the wedges, so it is this object's or one of the
// objects between parse_args and ResetGame (boot to InitGame, NewGame); only RoundOverProc uses it,
// and its content is the wheel's.
s32 wheelStartAngles[6] = { -5, -290, -80, -260, -260, -260 };
s32 firstRoundWedges[24] = {
    -1, 300, 250, 900, 400, 150, 250, 400, 300, -2, 400, 500, 200, 700, 500, 200, 300, 400, 500,
    1000, 200, 300, 800, 750
};
s32 secondRoundWedges[24] = {
    -1, 300, 250, 900, 400, 800, 250, 400, 550, -2, 400, 500, 350, 700, 500, 200, 300, 400, 500,
    2500, 200, 300, 800, 750
};
s32 jackpotRoundWedges[24] = {
    -1, 900, 3500, 250, 900, -3, 400, 550, -200, 500, -10000, 600, 200, 1000, 600, 300, 700, 450,
    300, 800, -2, 250, 400, 500
};
s32 laterRoundWedges[24] = {
    350, 900, 300, 250, 900, 200, 400, 550, 200, 500, -10000, 600, 200, -2, 350, 250, 500, 5000,
    300, 800, 500, 700, -1, 1500
};

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
    turnStartZero = 0;
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
        players[i].roundStartZero = 0;
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
    puzzleTail[0] = 0;
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
    StrNCopy(puzzleTail, text, len);
    puzzleTail[len] = 0;
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

/*
=====================
GetUncalledKinds

Which kinds of letters are still uncalled: 4 both, 3 consonants, 2 vowels, 0 none.
=====================
*/
s32 GetUncalledKinds(void) {
    s32 consonants;
    s32 vowels;
    u8 *p;

    vowels = 0;
    consonants = 0;
    for (p = uncalled; *p != 0; p++) {
        switch (*p) {
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
            vowels++;
            break;
        case ' ':
            break;
        default:
            consonants++;
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
    return 0;
}

/*
=====================
CheckPercentDone

The share of the puzzle's letters that are turned, from 0 to 1.
=====================
*/
f32 CheckPercentDone(void) {
    s32 row;
    s32 col;
    f32 count;
    f32 letters;

    count = letters = 0.0f;
    row = 0;
    for (;;) {
        if (row >= 4) {
            break;
        }
        col = 0;
        for (;;) {
            if (col >= 14) {
                break;
            }
            if (board[row][col] == 43) {
                count++;
            }
            if ((u32)puzzleText[row][col] >= 65) {
                if ((u32)puzzleText[row][col] < 91) {
                    letters++;
                }
            }
            col++;
        }
        row++;
    }
    count = letters - count;
    if (letters == 0.0f) {
        FatalError("CheckPercentDone: No letters in puzzle\n");
    }
    return count / letters;
}

/*
=====================
StartSolve

Copies the board into solveBoard, which the player fills in.
=====================
*/
void StartSolve(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 14; j++) {
            solveBoard[i][j] = board[i][j];
        }
    }
}

/*
=====================
CheckSolve

1 and the whole puzzle shown if solveBoard is the puzzle.
=====================
*/
s32 CheckSolve(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 14; j++) {
            if (puzzleText[i][j] != solveBoard[i][j]) {
                return 0;
            }
        }
    }
    i = 0;
    while (i < 4) {
        for (j = 0; j < 14; j++) {
            board[i][j] = puzzleText[i][j];
        }
        i++;
    }
    return 1;
}

/*
=====================
InitWheel

Sets the 24 wedges of the wheel for the round.
=====================
*/
void InitWheel(void) {
    s32 i;
    s32 value;

    curWedge = 0;
    i = 0;
    while (i < 24) {
        switch (round) {
        case 0:
            value = firstRoundWedges[i];
            break;
        case 1:
            value = secondRoundWedges[i];
            break;
        case 2:
            value = jackpotRoundWedges[i];
            break;
        default:
            value = laterRoundWedges[i];
        }
        wedges[i].claimed = 0;
        if (value == -10000) {
            if (prizeTaken != 0) {
                wedges[i].value = -1;
                StrCopy(wedges[i].name, "BANKRUPT");
                wedges[i].special = 0;
                wedges[i].claimed = 1;
            } else {
                wedges[i].value = value;
                StrCopy(wedges[i].name, "10000");
                wedges[i].special = 1;
            }
        } else if (value < -4) {
            wedges[i].value = value;
            StrCopy(wedges[i].name, "FREE SPIN");
            wedges[i].special = 1;
        } else if (value == -1) {
            wedges[i].value = -1;
            StrCopy(wedges[i].name, "BANKRUPT");
            wedges[i].special = 0;
        } else if (value == -2) {
            wedges[i].value = -2;
            StrCopy(wedges[i].name, "LOOSE TURN");
            wedges[i].special = 0;
        } else if (value == -3) {
            wedges[i].value = -3;
            StrCopy(wedges[i].name, "JACKPOT");
            wedges[i].special = 1;
        } else {
            wedges[i].value = value;
            IntToStr(wedges[i].name, value);
            wedges[i].special = 0;
        }
        i++;
    }
}

/*
=====================
ClaimWedge

Takes the prize off the wedge the wheel stopped on: the 10000 becomes BANKRUPT, a free spin its
value.
=====================
*/
void ClaimWedge(void) {
    if (wedges[curWedge].value == -10000) {
        wedges[curWedge].value = -1;
        StrCopy(wedges[curWedge].name, "BANKRUPT");
        wedges[curWedge].special = 0;
        wedges[curWedge].claimed = 1;
        return;
    }
    wedges[curWedge].value = wedges[curWedge].value * -1;
    IntToStr(wedges[curWedge].name, wedges[curWedge].value);
    wedges[curWedge].special = 0;
    wedges[curWedge].claimed = 1;
}

/*
=====================
SetWedge

The wedge the wheel stopped on, from its angle (or a random one for -1)
=====================
*/
void SetWedge(f32 degrees) {
    s32 angle;

    if (degrees == -1.0f) {
        curWedge += Random(24);
    } else {
        angle = (s32)degrees;
        if (angle < 0) {
            angle *= -1;
        }
        angle %= 360;
        curWedge = angle / 15;
        wedgeThird = angle / 5;
    }
    if (curWedge >= 24) {
        curWedge %= 24;
    }
}

/*
=====================
GetWedgeValue

The value of curWedge; the 10000 wedge is 10000 only in its middle third, else BANKRUPT.
=====================
*/
s32 GetWedgeValue(void) {
    s32 result;
    s32 rem;

    if (wedges[curWedge].value == -10000) {
        rem = wedgeThird % 3;
        if (rem == 1) {
            result = 10000;
        } else {
            result = -1;
        }
    } else {
        result = wedges[curWedge].value;
    }
    return result;
}

/*
=====================
ApplyWedge

Acts on curWedge: a final spin keeps its value, BANKRUPT clears the round's score, the jackpot round
adds to the jackpot.
=====================
*/
void ApplyWedge(s32 final) {
    if (final != 0) {
        finalSpinValue = GetWedgeValue();
    } else {
        if (GetWedgeValue() == -1) {
            players[curPlayer].score = 0;
            players[curPlayer].prize = 0;
            players[curPlayer].hasPrize = 0;
        }
        if (round == 2) {
            if (GetWedgeValue() > 0) {
                jackpot += GetWedgeValue();
            }
        }
    }
    return;
}

/*
=====================
ClearScores

Sets every player's scores to 0.
=====================
*/
void ClearScores(void) {
    s32 i;

    players[0].score = 0;
    players[0].total = 0;
    players[0].prize = 0;
    for (i = 0; i < 10; i++) {
        StrCopy(players[0].scoreStrings[i], "0");
    }
    players[1].score = 0;
    players[1].total = 0;
    players[1].prize = 0;
    for (i = 0; i < 10; i++) {
        StrCopy(players[1].scoreStrings[i], "0");
    }
    players[2].score = 0;
    players[2].total = 0;
    players[2].prize = 0;
    for (i = 0; i < 10; i++) {
        StrCopy(players[2].scoreStrings[i], "0");
    }
}

/*
=====================
NextPlayer

Passes the turn to the next player, or for a new round to the round's first.
=====================
*/
void NextPlayer(s32 newRound) {
    turnStartZero = 0;
    jackpotWon = 0;
    if (newRound == 0) {
        if (CheckSolved(0) == 2) {
            canSpin = 0;
        } else {
            canSpin = 1;
        }
        canBuyVowel = 1;
        canSolve = 1;
        curPlayer++;
        if (curPlayer >= 3) {
            curPlayer = 0;
        }
        return;
    }
    curPlayer = round % 3;
}
