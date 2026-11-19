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
glabel func_8003D3CC
    /* 8003D3CC 3C0A800B */ lui $t2, %hi(D_800B23A0)
    /* 8003D3D0 254A23A0 */ addiu $t2, $t2, %lo(D_800B23A0)
    /* 8003D3D4 01445021 */ addu $t2, $t2, $a0
    /* 8003D3D8 8D490000 */ lw $t1, 0x0($t2)
    /* 8003D3DC 03E09025 */ move $s2, $ra
    /* 8003D3E0 11200025 */ beqz $t1, .L8003D478
    /* 8003D3E4 00000000 */ nop
    /* 8003D3E8 8D2B0008 */ lw $t3, 0x8($t1)
    /* 8003D3EC 8D2C0010 */ lw $t4, 0x10($t1)
    /* 8003D3F0 016C082A */ slt $at, $t3, $t4
    /* 8003D3F4 10200020 */ beqz $at, .L8003D478
    /* 8003D3F8 00000000 */ nop
    /* 8003D3FC 8D2D000C */ lw $t5, 0xC($t1)
    /* 8003D400 01AB6821 */ addu $t5, $t5, $t3
    /* 8003D404 01AC001A */ div $zero, $t5, $t4
    /* 8003D408 15800002 */ bnez $t4, .L8003D414
    /* 8003D40C 00000000 */ nop
    /* 8003D410 0007000D */ break 7
.L8003D414:
    /* 8003D414 2401FFFF */ addiu $at, $zero, -0x1
    /* 8003D418 15810004 */ bne $t4, $at, .L8003D42C
    /* 8003D41C 3C018000 */ lui $at, 0x8000
    /* 8003D420 15A10002 */ bne $t5, $at, .L8003D42C
    /* 8003D424 00000000 */ nop
    /* 8003D428 0006000D */ break 6
.L8003D42C:
    /* 8003D42C 8D2C0014 */ lw $t4, 0x14($t1)
    /* 8003D430 00006810 */ mfhi $t5
    /* 8003D434 000D6880 */ sll $t5, $t5, 2
    /* 8003D438 018D6021 */ addu $t4, $t4, $t5
    /* 8003D43C 8D4D0004 */ lw $t5, 0x4($t2)
    /* 8003D440 256A0001 */ addiu $t2, $t3, 0x1
    /* 8003D444 AD8D0000 */ sw $t5, 0x0($t4)
    /* 8003D448 AD2A0008 */ sw $t2, 0x8($t1)
    /* 8003D44C 8D2A0000 */ lw $t2, 0x0($t1)
    /* 8003D450 8D4B0000 */ lw $t3, 0x0($t2)
    /* 8003D454 11600008 */ beqz $t3, .L8003D478
    /* 8003D458 00000000 */ nop
    /* 8003D45C 0C00F57F */ jal func_8003D5FC
    /* 8003D460 01202025 */ move $a0, $t1
    /* 8003D464 00405025 */ move $t2, $v0
    /* 8003D468 3C048008 */ lui $a0, %hi(D_800841F0)
    /* 8003D46C 01402825 */ move $a1, $t2
    /* 8003D470 0C00F56D */ jal __osEnqueueThread
    /* 8003D474 248441F0 */ addiu $a0, $a0, %lo(D_800841F0)
.L8003D478:
    /* 8003D478 02400008 */ jr $s2
    /* 8003D47C 00000000 */ nop
