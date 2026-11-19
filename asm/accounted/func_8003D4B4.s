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
glabel func_8003D4B4
    /* 8003D4B4 3C058008 */ lui $a1, %hi(D_800841F8)
    /* 8003D4B8 8CA541F8 */ lw $a1, %lo(D_800841F8)($a1)
    /* 8003D4BC 40086000 */ mfc0 $t0, $12 /* Status */
    /* 8003D4C0 8CBB0018 */ lw $k1, 0x18($a1)
    /* 8003D4C4 35080002 */ ori $t0, $t0, 0x2
    /* 8003D4C8 ACA80118 */ sw $t0, 0x118($a1)
    /* 8003D4CC FCB00098 */ sd $s0, 0x98($a1)
    /* 8003D4D0 FCB100A0 */ sd $s1, 0xA0($a1)
    /* 8003D4D4 FCB200A8 */ sd $s2, 0xA8($a1)
    /* 8003D4D8 FCB300B0 */ sd $s3, 0xB0($a1)
    /* 8003D4DC FCB400B8 */ sd $s4, 0xB8($a1)
    /* 8003D4E0 FCB500C0 */ sd $s5, 0xC0($a1)
    /* 8003D4E4 FCB600C8 */ sd $s6, 0xC8($a1)
    /* 8003D4E8 FCB700D0 */ sd $s7, 0xD0($a1)
    /* 8003D4EC FCBC00E8 */ sd $gp, 0xE8($a1)
    /* 8003D4F0 FCBD00F0 */ sd $sp, 0xF0($a1)
    /* 8003D4F4 FCBE00F8 */ sd $fp, 0xF8($a1)
    /* 8003D4F8 FCBF0100 */ sd $ra, 0x100($a1)
    /* 8003D4FC 13600009 */ beqz $k1, .L8003D524
    /* 8003D500 ACBF011C */ sw $ra, 0x11C($a1)
    /* 8003D504 445BF800 */ cfc1 $k1, $31 /* FpcCsr */
    /* 8003D508 F4B40180 */ sdc1 $f20, 0x180($a1)
    /* 8003D50C F4B60188 */ sdc1 $f22, 0x188($a1)
    /* 8003D510 F4B80190 */ sdc1 $f24, 0x190($a1)
    /* 8003D514 F4BA0198 */ sdc1 $f26, 0x198($a1)
    /* 8003D518 F4BC01A0 */ sdc1 $f28, 0x1A0($a1)
    /* 8003D51C F4BE01A8 */ sdc1 $f30, 0x1A8($a1)
    /* 8003D520 ACBB012C */ sw $k1, 0x12C($a1)
.L8003D524:
    /* 8003D524 8CBB0118 */ lw $k1, 0x118($a1)
    /* 8003D528 3369FF00 */ andi $t1, $k1, 0xFF00
    /* 8003D52C 1120000D */ beqz $t1, .L8003D564
    /* 8003D530 00000000 */ nop
    /* 8003D534 3C088008 */ lui $t0, %hi(D_80084228)
    /* 8003D538 25084228 */ addiu $t0, $t0, %lo(D_80084228)
    /* 8003D53C 8D080000 */ lw $t0, 0x0($t0)
    /* 8003D540 2401FFFF */ addiu $at, $zero, -0x1
    /* 8003D544 01014026 */ xor $t0, $t0, $at
    /* 8003D548 3C01FFFF */ lui $at, 0xFFFF
    /* 8003D54C 3108FF00 */ andi $t0, $t0, 0xFF00
    /* 8003D550 342100FF */ ori $at, $at, 0xFF
    /* 8003D554 01284825 */ or $t1, $t1, $t0
    /* 8003D558 0361D824 */ and $k1, $k1, $at
    /* 8003D55C 0369D825 */ or $k1, $k1, $t1
    /* 8003D560 ACBB0118 */ sw $k1, 0x118($a1)
.L8003D564:
    /* 8003D564 3C1BA430 */ lui $k1, %hi(D_A430000C)
    /* 8003D568 8F7B000C */ lw $k1, %lo(D_A430000C)($k1)
    /* 8003D56C 1360000B */ beqz $k1, .L8003D59C
    /* 8003D570 00000000 */ nop
    /* 8003D574 3C1A8008 */ lui $k0, %hi(D_80084228)
    /* 8003D578 275A4228 */ addiu $k0, $k0, %lo(D_80084228)
    /* 8003D57C 8F5A0000 */ lw $k0, 0x0($k0)
    /* 8003D580 8CA80128 */ lw $t0, 0x128($a1)
    /* 8003D584 2401FFFF */ addiu $at, $zero, -0x1
    /* 8003D588 001AD402 */ srl $k0, $k0, 16
    /* 8003D58C 0341D026 */ xor $k0, $k0, $at
    /* 8003D590 335A003F */ andi $k0, $k0, 0x3F
    /* 8003D594 0348D024 */ and $k0, $k0, $t0
    /* 8003D598 037AD825 */ or $k1, $k1, $k0
.L8003D59C:
    /* 8003D59C 10800003 */ beqz $a0, .L8003D5AC
    /* 8003D5A0 ACBB0128 */ sw $k1, 0x128($a1)
    /* 8003D5A4 0C00F56D */ jal __osEnqueueThread
    /* 8003D5A8 00000000 */ nop
.L8003D5AC:
    /* 8003D5AC 0800F583 */ j __osDispatchThread
    /* 8003D5B0 00000000 */ nop
