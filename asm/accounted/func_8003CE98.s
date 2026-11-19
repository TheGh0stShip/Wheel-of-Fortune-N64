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
glabel func_8003CE98
    /* 8003CE98 3C1A800B */ lui $k0, %hi(D_800B2420)
    /* 8003CE9C 275A2420 */ addiu $k0, $k0, %lo(D_800B2420)
    /* 8003CEA0 FF410020 */ sd $at, 0x20($k0)
    /* 8003CEA4 401B6000 */ mfc0 $k1, $12 /* Status */
    /* 8003CEA8 AF5B0118 */ sw $k1, 0x118($k0)
    /* 8003CEAC 2401FFFC */ addiu $at, $zero, -0x4
    /* 8003CEB0 0361D824 */ and $k1, $k1, $at
    /* 8003CEB4 409B6000 */ mtc0 $k1, $12 /* Status */
    /* 8003CEB8 FF480058 */ sd $t0, 0x58($k0)
    /* 8003CEBC FF490060 */ sd $t1, 0x60($k0)
    /* 8003CEC0 FF4A0068 */ sd $t2, 0x68($k0)
