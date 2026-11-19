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
glabel func_8003CE88
    /* 8003CE88 3C1A8004 */ lui $k0, %hi(func_8003CE98)
    /* 8003CE8C 275ACE98 */ addiu $k0, $k0, %lo(func_8003CE98)
    /* 8003CE90 03400008 */ jr $k0
    /* 8003CE94 00000000 */ nop
