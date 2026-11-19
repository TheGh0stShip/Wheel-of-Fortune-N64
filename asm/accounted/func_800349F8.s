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
glabel func_800349F8
    /* 800349F8 40082000 */ mfc0 $t0, $4 /* Context */
    /* 800349FC 31080080 */ andi $t0, $t0, 0x80
    /* 80034A00 15000002 */ bnez $t0, .L80034A0C
    /* 80034A04 00000000 */ nop
    /* 80034A08 03E00008 */ jr $ra
.L80034A0C:
    /* 80034A0C 40803800 */ mtc0 $zero, $7 /* Reserved07 */
