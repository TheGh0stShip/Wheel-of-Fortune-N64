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
glabel func_8003D5B4
    /* 8003D5B4 8C980000 */ lw $t8, 0x0($a0)
    /* 8003D5B8 8CAF0004 */ lw $t7, 0x4($a1)
    /* 8003D5BC 0080C825 */ move $t9, $a0
    /* 8003D5C0 8F0E0004 */ lw $t6, 0x4($t8)
    /* 8003D5C4 01CF082A */ slt $at, $t6, $t7
    /* 8003D5C8 14200007 */ bnez $at, .L8003D5E8
    /* 8003D5CC 00000000 */ nop
.L8003D5D0:
    /* 8003D5D0 0300C825 */ move $t9, $t8
    /* 8003D5D4 8F180000 */ lw $t8, 0x0($t8)
    /* 8003D5D8 8F0E0004 */ lw $t6, 0x4($t8)
    /* 8003D5DC 01CF082A */ slt $at, $t6, $t7
    /* 8003D5E0 1020FFFB */ beqz $at, .L8003D5D0
    /* 8003D5E4 00000000 */ nop
.L8003D5E8:
    /* 8003D5E8 8F380000 */ lw $t8, 0x0($t9)
    /* 8003D5EC ACB80000 */ sw $t8, 0x0($a1)
    /* 8003D5F0 AF250000 */ sw $a1, 0x0($t9)
    /* 8003D5F4 03E00008 */ jr $ra
    /* 8003D5F8 ACA40008 */ sw $a0, 0x8($a1)
