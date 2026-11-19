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
glabel func_8003D788
    /* 8003D788 0C00FA06 */ jal func_8003E818
    /* 8003D78C 00002025 */ move $a0, $zero
