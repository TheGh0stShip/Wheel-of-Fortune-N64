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
glabel func_80038718
    /* 80038718 27BDFFD8 */ addiu $sp, $sp, -0x28
    /* 8003871C 27A20018 */ addiu $v0, $sp, 0x18
    /* 80038720 AFBF0020 */ sw $ra, 0x20($sp)
    /* 80038724 0C00E036 */ jal func_800380D8
    /* 80038728 AFA20010 */ sw $v0, 0x10($sp)
    /* 8003872C 8FA20018 */ lw $v0, 0x18($sp)
    /* 80038730 8FA3001C */ lw $v1, 0x1C($sp)
    /* 80038734 8FBF0020 */ lw $ra, 0x20($sp)
    /* 80038738 27BD0028 */ addiu $sp, $sp, 0x28
    /* 8003873C 03E00008 */ jr $ra
    /* 80038740 00000000 */ nop
