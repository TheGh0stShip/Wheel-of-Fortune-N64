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
glabel func_800349EC
    /* 800349EC 00000000 */ nop
    /* 800349F0 00E00008 */ jr $a3
    /* 800349F4 40803800 */ mtc0 $zero, $7 /* Reserved07 */
