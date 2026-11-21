#include "wof.h"

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
