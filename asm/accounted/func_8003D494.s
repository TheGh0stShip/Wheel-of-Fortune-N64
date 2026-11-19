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
glabel func_8003D494
    /* 8003D494 00000000 */ nop
    /* 8003D498 8F5B0118 */ lw $k1, 0x118($k0)
    /* 8003D49C 3C012000 */ lui $at, 0x2000
    /* 8003D4A0 24090001 */ addiu $t1, $zero, 0x1
    /* 8003D4A4 0361D825 */ or $k1, $k1, $at
    /* 8003D4A8 AF490018 */ sw $t1, 0x18($k0)
    /* 8003D4AC 1000FFB5 */ b L_8003D384
    /* 8003D4B0 AF5B0118 */ sw $k1, 0x118($k0)
