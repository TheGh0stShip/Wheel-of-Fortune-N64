.macro glabel label
    .global \label
    \label:
.endm
.macro jlabel label
    \label:
.endm

.set noat
.set noreorder
.section .text
glabel gap_8003D480
    /* 8003D480 3C013000 */ lui $at, 0x3000
    /* 8003D484 01014824 */ and $t1, $t0, $at
    /* 8003D488 00094F02 */ srl $t1, $t1, 28
    /* 8003D48C 240A0001 */ addiu $t2, $zero, 0x1
    /* 8003D490 152AFFC2 */ bne $t1, $t2, L_8003D39C
