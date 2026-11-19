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
glabel func_80000400
    /* 80000400 3C1D803F */ lui $sp, 0x803F
    /* 80000404 37BDFFF0 */ ori $sp, $sp, 0xFFF0
    /* 80000408 3C08800A */ lui $t0, %hi(D_800A5078)
    /* 8000040C 25085078 */ addiu $t0, $t0, %lo(D_800A5078)
    /* 80000410 3C098010 */ lui $t1, %hi(D_800FB898)
    /* 80000414 2529B898 */ addiu $t1, $t1, %lo(D_800FB898)
    /* 80000418 11090005 */ beq $t0, $t1, .L80000430
    /* 8000041C 00000000 */ nop
.L80000420:
    /* 80000420 25080004 */ addiu $t0, $t0, 0x4
    /* 80000424 0109082B */ sltu $at, $t0, $t1
    /* 80000428 1420FFFD */ bnez $at, .L80000420
    /* 8000042C AD00FFFC */ sw $zero, -0x4($t0)
.L80000430:
    /* 80000430 0C0018CA */ jal func_80006328
    /* 80000434 00000000 */ nop
    /* 80000438 0001008D */ break 1, 2
    /* 8000043C 00000000 */ nop
