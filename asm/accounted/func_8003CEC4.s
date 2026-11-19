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
glabel func_8003CEC4
    /* 8003CEC4 AF400018 */ sw $zero, 0x18($k0)
    /* 8003CEC8 40086800 */ mfc0 $t0, $13 /* Cause */
    /* 8003CECC 03404025 */ move $t0, $k0
    /* 8003CED0 3C1A8008 */ lui $k0, %hi(D_800841F8)
    /* 8003CED4 8F5A41F8 */ lw $k0, %lo(D_800841F8)($k0)
    /* 8003CED8 DD090020 */ ld $t1, 0x20($t0)
    /* 8003CEDC FF490020 */ sd $t1, 0x20($k0)
    /* 8003CEE0 DD090118 */ ld $t1, 0x118($t0)
    /* 8003CEE4 FF490118 */ sd $t1, 0x118($k0)
    /* 8003CEE8 DD090058 */ ld $t1, 0x58($t0)
    /* 8003CEEC FF490058 */ sd $t1, 0x58($k0)
    /* 8003CEF0 DD090060 */ ld $t1, 0x60($t0)
    /* 8003CEF4 FF490060 */ sd $t1, 0x60($k0)
    /* 8003CEF8 DD090068 */ ld $t1, 0x68($t0)
    /* 8003CEFC FF490068 */ sd $t1, 0x68($k0)
    /* 8003CF00 8F5B0118 */ lw $k1, 0x118($k0)
    /* 8003CF04 00004012 */ mflo $t0
    /* 8003CF08 FF480108 */ sd $t0, 0x108($k0)
    /* 8003CF0C 00004010 */ mfhi $t0
    /* 8003CF10 3369FF00 */ andi $t1, $k1, 0xFF00
    /* 8003CF14 FF420028 */ sd $v0, 0x28($k0)
    /* 8003CF18 FF430030 */ sd $v1, 0x30($k0)
    /* 8003CF1C FF440038 */ sd $a0, 0x38($k0)
    /* 8003CF20 FF450040 */ sd $a1, 0x40($k0)
    /* 8003CF24 FF460048 */ sd $a2, 0x48($k0)
    /* 8003CF28 FF470050 */ sd $a3, 0x50($k0)
    /* 8003CF2C FF4B0070 */ sd $t3, 0x70($k0)
    /* 8003CF30 FF4C0078 */ sd $t4, 0x78($k0)
    /* 8003CF34 FF4D0080 */ sd $t5, 0x80($k0)
    /* 8003CF38 FF4E0088 */ sd $t6, 0x88($k0)
    /* 8003CF3C FF4F0090 */ sd $t7, 0x90($k0)
    /* 8003CF40 FF500098 */ sd $s0, 0x98($k0)
    /* 8003CF44 FF5100A0 */ sd $s1, 0xA0($k0)
    /* 8003CF48 FF5200A8 */ sd $s2, 0xA8($k0)
    /* 8003CF4C FF5300B0 */ sd $s3, 0xB0($k0)
    /* 8003CF50 FF5400B8 */ sd $s4, 0xB8($k0)
    /* 8003CF54 FF5500C0 */ sd $s5, 0xC0($k0)
    /* 8003CF58 FF5600C8 */ sd $s6, 0xC8($k0)
    /* 8003CF5C FF5700D0 */ sd $s7, 0xD0($k0)
    /* 8003CF60 FF5800D8 */ sd $t8, 0xD8($k0)
    /* 8003CF64 FF5900E0 */ sd $t9, 0xE0($k0)
    /* 8003CF68 FF5C00E8 */ sd $gp, 0xE8($k0)
    /* 8003CF6C FF5D00F0 */ sd $sp, 0xF0($k0)
    /* 8003CF70 FF5E00F8 */ sd $fp, 0xF8($k0)
    /* 8003CF74 FF5F0100 */ sd $ra, 0x100($k0)
    /* 8003CF78 11200011 */ beqz $t1, .L8003CFC0
    /* 8003CF7C FF480110 */ sd $t0, 0x110($k0)
    /* 8003CF80 3C088008 */ lui $t0, %hi(D_80084228)
    /* 8003CF84 25084228 */ addiu $t0, $t0, %lo(D_80084228)
    /* 8003CF88 8D080000 */ lw $t0, 0x0($t0)
    /* 8003CF8C 2401FFFF */ addiu $at, $zero, -0x1
    /* 8003CF90 01015026 */ xor $t2, $t0, $at
    /* 8003CF94 3C01FFFF */ lui $at, 0xFFFF
    /* 8003CF98 314AFF00 */ andi $t2, $t2, 0xFF00
    /* 8003CF9C 342100FF */ ori $at, $at, 0xFF
    /* 8003CFA0 012A6025 */ or $t4, $t1, $t2
    /* 8003CFA4 03615824 */ and $t3, $k1, $at
    /* 8003CFA8 3108FF00 */ andi $t0, $t0, 0xFF00
    /* 8003CFAC 016C5825 */ or $t3, $t3, $t4
    /* 8003CFB0 01284824 */ and $t1, $t1, $t0
    /* 8003CFB4 0361D824 */ and $k1, $k1, $at
    /* 8003CFB8 AF4B0118 */ sw $t3, 0x118($k0)
    /* 8003CFBC 0369D825 */ or $k1, $k1, $t1
.L8003CFC0:
    /* 8003CFC0 3C09A430 */ lui $t1, %hi(D_A430000C)
    /* 8003CFC4 8D29000C */ lw $t1, %lo(D_A430000C)($t1)
    /* 8003CFC8 1120000B */ beqz $t1, .L8003CFF8
    /* 8003CFCC 00000000 */ nop
    /* 8003CFD0 3C088008 */ lui $t0, %hi(D_80084228)
    /* 8003CFD4 25084228 */ addiu $t0, $t0, %lo(D_80084228)
    /* 8003CFD8 8D080000 */ lw $t0, 0x0($t0)
    /* 8003CFDC 8F4C0128 */ lw $t4, 0x128($k0)
    /* 8003CFE0 2401FFFF */ addiu $at, $zero, -0x1
    /* 8003CFE4 00084402 */ srl $t0, $t0, 16
    /* 8003CFE8 01014026 */ xor $t0, $t0, $at
    /* 8003CFEC 3108003F */ andi $t0, $t0, 0x3F
    /* 8003CFF0 010C4024 */ and $t0, $t0, $t4
    /* 8003CFF4 01284825 */ or $t1, $t1, $t0
.L8003CFF8:
    /* 8003CFF8 AF490128 */ sw $t1, 0x128($k0)
    /* 8003CFFC 40087000 */ mfc0 $t0, $14 /* EPC */
    /* 8003D000 AF48011C */ sw $t0, 0x11C($k0)
    /* 8003D004 8F480018 */ lw $t0, 0x18($k0)
    /* 8003D008 11000014 */ beqz $t0, .L8003D05C
    /* 8003D00C 00000000 */ nop
    /* 8003D010 4448F800 */ cfc1 $t0, $31 /* FpcCsr */
    /* 8003D014 00000000 */ nop
    /* 8003D018 AF48012C */ sw $t0, 0x12C($k0)
    /* 8003D01C F7400130 */ sdc1 $f0, 0x130($k0)
    /* 8003D020 F7420138 */ sdc1 $f2, 0x138($k0)
    /* 8003D024 F7440140 */ sdc1 $f4, 0x140($k0)
    /* 8003D028 F7460148 */ sdc1 $f6, 0x148($k0)
    /* 8003D02C F7480150 */ sdc1 $f8, 0x150($k0)
    /* 8003D030 F74A0158 */ sdc1 $f10, 0x158($k0)
    /* 8003D034 F74C0160 */ sdc1 $f12, 0x160($k0)
    /* 8003D038 F74E0168 */ sdc1 $f14, 0x168($k0)
    /* 8003D03C F7500170 */ sdc1 $f16, 0x170($k0)
    /* 8003D040 F7520178 */ sdc1 $f18, 0x178($k0)
    /* 8003D044 F7540180 */ sdc1 $f20, 0x180($k0)
    /* 8003D048 F7560188 */ sdc1 $f22, 0x188($k0)
    /* 8003D04C F7580190 */ sdc1 $f24, 0x190($k0)
    /* 8003D050 F75A0198 */ sdc1 $f26, 0x198($k0)
    /* 8003D054 F75C01A0 */ sdc1 $f28, 0x1A0($k0)
    /* 8003D058 F75E01A8 */ sdc1 $f30, 0x1A8($k0)
.L8003D05C:
    /* 8003D05C 40086800 */ mfc0 $t0, $13 /* Cause */
    /* 8003D060 AF480120 */ sw $t0, 0x120($k0)
    /* 8003D064 24090002 */ addiu $t1, $zero, 0x2
    /* 8003D068 A7490010 */ sh $t1, 0x10($k0)
    /* 8003D06C 3109007C */ andi $t1, $t0, 0x7C
    /* 8003D070 240A0024 */ addiu $t2, $zero, 0x24
    /* 8003D074 112A00B0 */ beq $t1, $t2, .L8003D338
    /* 8003D078 00000000 */ nop
    /* 8003D07C 240A002C */ addiu $t2, $zero, 0x2C
    /* 8003D080 112A00FF */ beq $t1, $t2, L_8003D480
    /* 8003D084 00000000 */ nop
    /* 8003D088 240A0000 */ addiu $t2, $zero, 0x0
    /* 8003D08C 152A00C3 */ bne $t1, $t2, .L8003D39C
    /* 8003D090 00000000 */ nop
    /* 8003D094 03688024 */ and $s0, $k1, $t0
.L8003D098:
    /* 8003D098 3209FF00 */ andi $t1, $s0, 0xFF00
    /* 8003D09C 00095302 */ srl $t2, $t1, 12
    /* 8003D0A0 15400003 */ bnez $t2, .L8003D0B0
    /* 8003D0A4 00000000 */ nop
    /* 8003D0A8 00095202 */ srl $t2, $t1, 8
    /* 8003D0AC 214A0010 */ addi $t2, $t2, 0x10
.L8003D0B0:
    /* 8003D0B0 3C018000 */ lui $at, %hi(D_80001C38)
    /* 8003D0B4 002A0821 */ addu $at, $at, $t2
    /* 8003D0B8 902A1C38 */ lbu $t2, %lo(D_80001C38)($at)
    /* 8003D0BC 3C018000 */ lui $at, %hi(jtbl_80001C58)
    /* 8003D0C0 002A0821 */ addu $at, $at, $t2
    /* 8003D0C4 8C2A1C58 */ lw $t2, %lo(jtbl_80001C58)($at)
    /* 8003D0C8 01400008 */ jr $t2
    /* 8003D0CC 00000000 */ nop
.L8003D0D0:
    /* 8003D0D0 2401DFFF */ addiu $at, $zero, -0x2001
    /* 8003D0D4 1000FFF0 */ b .L8003D098
    /* 8003D0D8 02018024 */ and $s0, $s0, $at
.L8003D0DC:
    /* 8003D0DC 2401BFFF */ addiu $at, $zero, -0x4001
    /* 8003D0E0 1000FFED */ b .L8003D098
    /* 8003D0E4 02018024 */ and $s0, $s0, $at
.L8003D0E8:
    /* 8003D0E8 40095800 */ mfc0 $t1, $11 /* Compare */
    /* 8003D0EC 40895800 */ mtc0 $t1, $11 /* Compare */
    /* 8003D0F0 0C00F4F3 */ jal send_mesg
    /* 8003D0F4 24040018 */ addiu $a0, $zero, 0x18
    /* 8003D0F8 3C01FFFF */ lui $at, 0xFFFF
    /* 8003D0FC 34217FFF */ ori $at, $at, 0x7FFF
    /* 8003D100 1000FFE5 */ b .L8003D098
    /* 8003D104 02018024 */ and $s0, $s0, $at
.L8003D108:
    /* 8003D108 2401F7FF */ addiu $at, $zero, -0x801
    /* 8003D10C 02018024 */ and $s0, $s0, $at
    /* 8003D110 240A0004 */ addiu $t2, $zero, 0x4
    /* 8003D114 3C018008 */ lui $at, %hi(D_80084088)
    /* 8003D118 002A0821 */ addu $at, $at, $t2
    /* 8003D11C 8C2A4088 */ lw $t2, %lo(D_80084088)($at)
    /* 8003D120 3C1D800B */ lui $sp, %hi(D_800B13A0)
    /* 8003D124 27BD13A0 */ addiu $sp, $sp, %lo(D_800B13A0)
    /* 8003D128 24040010 */ addiu $a0, $zero, 0x10
    /* 8003D12C 11400007 */ beqz $t2, .L8003D14C
    /* 8003D130 27BD0FF0 */ addiu $sp, $sp, 0xFF0
    /* 8003D134 0140F809 */ jalr $t2
    /* 8003D138 00000000 */ nop
    /* 8003D13C 10400003 */ beqz $v0, .L8003D14C
    /* 8003D140 24040010 */ addiu $a0, $zero, 0x10
    /* 8003D144 10000082 */ b .L8003D350
    /* 8003D148 00000000 */ nop
.L8003D14C:
    /* 8003D14C 0C00F4F3 */ jal send_mesg
    /* 8003D150 00000000 */ nop
    /* 8003D154 1000FFD0 */ b .L8003D098
    /* 8003D158 00000000 */ nop
.L8003D15C:
    /* 8003D15C 3C088008 */ lui $t0, %hi(D_80084228)
    /* 8003D160 25084228 */ addiu $t0, $t0, %lo(D_80084228)
    /* 8003D164 8D080000 */ lw $t0, 0x0($t0)
    /* 8003D168 3C11A430 */ lui $s1, %hi(D_A4300008)
    /* 8003D16C 8E310008 */ lw $s1, %lo(D_A4300008)($s1)
    /* 8003D170 00084402 */ srl $t0, $t0, 16
    /* 8003D174 02288824 */ and $s1, $s1, $t0
    /* 8003D178 32290001 */ andi $t1, $s1, 0x1
    /* 8003D17C 11200013 */ beqz $t1, .L8003D1CC
    /* 8003D180 00000000 */ nop
    /* 8003D184 3C0CA404 */ lui $t4, %hi(D_A4040010)
    /* 8003D188 8D8C0010 */ lw $t4, %lo(D_A4040010)($t4)
    /* 8003D18C 24090008 */ addiu $t1, $zero, 0x8
    /* 8003D190 3C01A404 */ lui $at, %hi(D_A4040010)
    /* 8003D194 318C0300 */ andi $t4, $t4, 0x300
    /* 8003D198 3231003E */ andi $s1, $s1, 0x3E
    /* 8003D19C 11800007 */ beqz $t4, .L8003D1BC
    /* 8003D1A0 AC290010 */ sw $t1, %lo(D_A4040010)($at)
    /* 8003D1A4 0C00F4F3 */ jal send_mesg
    /* 8003D1A8 24040020 */ addiu $a0, $zero, 0x20
    /* 8003D1AC 12200038 */ beqz $s1, .L8003D290
    /* 8003D1B0 00000000 */ nop
    /* 8003D1B4 10000005 */ b .L8003D1CC
    /* 8003D1B8 00000000 */ nop
.L8003D1BC:
    /* 8003D1BC 0C00F4F3 */ jal send_mesg
    /* 8003D1C0 24040058 */ addiu $a0, $zero, 0x58
    /* 8003D1C4 12200032 */ beqz $s1, .L8003D290
    /* 8003D1C8 00000000 */ nop
.L8003D1CC:
    /* 8003D1CC 32290008 */ andi $t1, $s1, 0x8
    /* 8003D1D0 11200007 */ beqz $t1, .L8003D1F0
    /* 8003D1D4 3C01A440 */ lui $at, %hi(D_A4400010)
    /* 8003D1D8 32310037 */ andi $s1, $s1, 0x37
    /* 8003D1DC AC200010 */ sw $zero, %lo(D_A4400010)($at)
    /* 8003D1E0 0C00F4F3 */ jal send_mesg
    /* 8003D1E4 24040038 */ addiu $a0, $zero, 0x38
    /* 8003D1E8 12200029 */ beqz $s1, .L8003D290
    /* 8003D1EC 00000000 */ nop
.L8003D1F0:
    /* 8003D1F0 32290004 */ andi $t1, $s1, 0x4
    /* 8003D1F4 11200009 */ beqz $t1, .L8003D21C
    /* 8003D1F8 00000000 */ nop
    /* 8003D1FC 24090001 */ addiu $t1, $zero, 0x1
    /* 8003D200 3C01A450 */ lui $at, %hi(D_A450000C)
    /* 8003D204 3231003B */ andi $s1, $s1, 0x3B
    /* 8003D208 AC29000C */ sw $t1, %lo(D_A450000C)($at)
    /* 8003D20C 0C00F4F3 */ jal send_mesg
    /* 8003D210 24040030 */ addiu $a0, $zero, 0x30
    /* 8003D214 1220001E */ beqz $s1, .L8003D290
    /* 8003D218 00000000 */ nop
.L8003D21C:
    /* 8003D21C 32290002 */ andi $t1, $s1, 0x2
    /* 8003D220 11200007 */ beqz $t1, .L8003D240
    /* 8003D224 3C01A480 */ lui $at, %hi(D_A4800018)
    /* 8003D228 3231003D */ andi $s1, $s1, 0x3D
    /* 8003D22C AC200018 */ sw $zero, %lo(D_A4800018)($at)
    /* 8003D230 0C00F4F3 */ jal send_mesg
    /* 8003D234 24040028 */ addiu $a0, $zero, 0x28
    /* 8003D238 12200015 */ beqz $s1, .L8003D290
    /* 8003D23C 00000000 */ nop
.L8003D240:
    /* 8003D240 32290010 */ andi $t1, $s1, 0x10
    /* 8003D244 11200009 */ beqz $t1, .L8003D26C
    /* 8003D248 00000000 */ nop
    /* 8003D24C 24090002 */ addiu $t1, $zero, 0x2
    /* 8003D250 3C01A460 */ lui $at, %hi(D_A4600010)
    /* 8003D254 3231002F */ andi $s1, $s1, 0x2F
    /* 8003D258 AC290010 */ sw $t1, %lo(D_A4600010)($at)
    /* 8003D25C 0C00F4F3 */ jal send_mesg
    /* 8003D260 24040040 */ addiu $a0, $zero, 0x40
    /* 8003D264 1220000A */ beqz $s1, .L8003D290
    /* 8003D268 00000000 */ nop
.L8003D26C:
    /* 8003D26C 32290020 */ andi $t1, $s1, 0x20
    /* 8003D270 11200007 */ beqz $t1, .L8003D290
    /* 8003D274 00000000 */ nop
    /* 8003D278 24090800 */ addiu $t1, $zero, 0x800
    /* 8003D27C 3C01A430 */ lui $at, %hi(D_A4300000)
    /* 8003D280 3231001F */ andi $s1, $s1, 0x1F
    /* 8003D284 AC290000 */ sw $t1, %lo(D_A4300000)($at)
    /* 8003D288 0C00F4F3 */ jal send_mesg
    /* 8003D28C 24040048 */ addiu $a0, $zero, 0x48
.L8003D290:
    /* 8003D290 2401FBFF */ addiu $at, $zero, -0x401
    /* 8003D294 1000FF80 */ b .L8003D098
    /* 8003D298 02018024 */ and $s0, $s0, $at
.L8003D29C:
    /* 8003D29C 8F5B0118 */ lw $k1, 0x118($k0)
    /* 8003D2A0 2401EFFF */ addiu $at, $zero, -0x1001
    /* 8003D2A4 3C098008 */ lui $t1, %hi(D_80084224)
    /* 8003D2A8 0361D824 */ and $k1, $k1, $at
    /* 8003D2AC AF5B0118 */ sw $k1, 0x118($k0)
    /* 8003D2B0 25294224 */ addiu $t1, $t1, %lo(D_80084224)
    /* 8003D2B4 8D2A0000 */ lw $t2, 0x0($t1)
    /* 8003D2B8 11400003 */ beqz $t2, .L8003D2C8
    /* 8003D2BC 2401EFFF */ addiu $at, $zero, -0x1001
    /* 8003D2C0 10000023 */ b .L8003D350
    /* 8003D2C4 02018024 */ and $s0, $s0, $at
.L8003D2C8:
    /* 8003D2C8 240A0001 */ addiu $t2, $zero, 0x1
    /* 8003D2CC AD2A0000 */ sw $t2, 0x0($t1)
    /* 8003D2D0 0C00F4F3 */ jal send_mesg
    /* 8003D2D4 24040070 */ addiu $a0, $zero, 0x70
    /* 8003D2D8 3C0A8008 */ lui $t2, %hi(D_800841F0)
    /* 8003D2DC 8D4A41F0 */ lw $t2, %lo(D_800841F0)($t2)
    /* 8003D2E0 2401EFFF */ addiu $at, $zero, -0x1001
    /* 8003D2E4 02018024 */ and $s0, $s0, $at
    /* 8003D2E8 8D5B0118 */ lw $k1, 0x118($t2)
    /* 8003D2EC 0361D824 */ and $k1, $k1, $at
    /* 8003D2F0 10000017 */ b .L8003D350
    /* 8003D2F4 AD5B0118 */ sw $k1, 0x118($t2)
.L8003D2F8:
    /* 8003D2F8 2401FDFF */ addiu $at, $zero, -0x201
    /* 8003D2FC 01014024 */ and $t0, $t0, $at
    /* 8003D300 40886800 */ mtc0 $t0, $13 /* Cause */
    /* 8003D304 0C00F4F3 */ jal send_mesg
    /* 8003D308 24040008 */ addiu $a0, $zero, 0x8
    /* 8003D30C 2401FDFF */ addiu $at, $zero, -0x201
    /* 8003D310 1000FF61 */ b .L8003D098
    /* 8003D314 02018024 */ and $s0, $s0, $at
.L8003D318:
    /* 8003D318 2401FEFF */ addiu $at, $zero, -0x101
    /* 8003D31C 01014024 */ and $t0, $t0, $at
    /* 8003D320 40886800 */ mtc0 $t0, $13 /* Cause */
    /* 8003D324 0C00F4F3 */ jal send_mesg
    /* 8003D328 24040000 */ addiu $a0, $zero, 0x0
    /* 8003D32C 2401FEFF */ addiu $at, $zero, -0x101
    /* 8003D330 1000FF59 */ b .L8003D098
    /* 8003D334 02018024 */ and $s0, $s0, $at
.L8003D338:
    /* 8003D338 24090001 */ addiu $t1, $zero, 0x1
    /* 8003D33C A7490012 */ sh $t1, 0x12($k0)
    /* 8003D340 0C00F4F3 */ jal send_mesg
    /* 8003D344 24040050 */ addiu $a0, $zero, 0x50
    /* 8003D348 10000001 */ b .L8003D350
    /* 8003D34C 00000000 */ nop
.L8003D350:
    /* 8003D350 3C0A8008 */ lui $t2, %hi(D_800841F0)
    /* 8003D354 8D4A41F0 */ lw $t2, %lo(D_800841F0)($t2)
    /* 8003D358 8F490004 */ lw $t1, 0x4($k0)
    /* 8003D35C 8D4B0004 */ lw $t3, 0x4($t2)
    /* 8003D360 012B082A */ slt $at, $t1, $t3
    /* 8003D364 10200007 */ beqz $at, .L8003D384
    /* 8003D368 00000000 */ nop
    /* 8003D36C 3C048008 */ lui $a0, %hi(D_800841F0)
    /* 8003D370 03402825 */ move $a1, $k0
    /* 8003D374 0C00F56D */ jal __osEnqueueThread
    /* 8003D378 248441F0 */ addiu $a0, $a0, %lo(D_800841F0)
    /* 8003D37C 0800F583 */ j __osDispatchThread
    /* 8003D380 00000000 */ nop
.L8003D384:
    /* 8003D384 3C098008 */ lui $t1, %hi(D_800841F0)
    /* 8003D388 252941F0 */ addiu $t1, $t1, %lo(D_800841F0)
    /* 8003D38C 8D2A0000 */ lw $t2, 0x0($t1)
    /* 8003D390 AF4A0000 */ sw $t2, 0x0($k0)
    /* 8003D394 0800F583 */ j __osDispatchThread
    /* 8003D398 AD3A0000 */ sw $k0, 0x0($t1)
.L8003D39C:
    /* 8003D39C 3C018008 */ lui $at, %hi(D_800841FC)
    /* 8003D3A0 AC3A41FC */ sw $k0, %lo(D_800841FC)($at)
    /* 8003D3A4 24090001 */ addiu $t1, $zero, 0x1
    /* 8003D3A8 A7490010 */ sh $t1, 0x10($k0)
    /* 8003D3AC 24090002 */ addiu $t1, $zero, 0x2
    /* 8003D3B0 A7490012 */ sh $t1, 0x12($k0)
    /* 8003D3B4 400A4000 */ mfc0 $t2, $8 /* BadVaddr */
    /* 8003D3B8 AF4A0124 */ sw $t2, 0x124($k0)
    /* 8003D3BC 0C00F4F3 */ jal send_mesg
    /* 8003D3C0 24040060 */ addiu $a0, $zero, 0x60
    /* 8003D3C4 0800F583 */ j __osDispatchThread
    /* 8003D3C8 00000000 */ nop
.section .rodata
.section .rodata.jtbl_80001C58, "a"
glabel jtbl_80001C58
    .word .L8003D350
    .word .L8003D318
    .word .L8003D2F8
    .word .L8003D15C
    .word .L8003D108
    .word .L8003D29C
    .word .L8003D0D0
    .word .L8003D0DC
    .word .L8003D0E8
