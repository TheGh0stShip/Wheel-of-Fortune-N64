/*
 * The image's entry point. The boot code jumps here once it has copied the image into memory. It sets the
 * stack, clears the uninitialised data and calls the game's main, which never returns.
 *
 * Original assembly: C cannot load $sp, and the game has no stack until this has run. The original names
 * are unknown, so the symbols carry their addresses.
 */
	.set	noreorder
	.set	noat
	.text
	.globl	func_80000400
func_80000400:
	lui	$sp, 0x803F			/* the stack starts 16 bytes below the end of 4 MB of RDRAM */
	ori	$sp, $sp, 0xFFF0
	lui	$t0, %hi(D_800A5078)		/* start of the uninitialised data */
	addiu	$t0, $t0, %lo(D_800A5078)
	lui	$t1, %hi(D_800FB898)		/* its end */
	addiu	$t1, $t1, %lo(D_800FB898)
	beq	$t0, $t1, 2f
	nop
1:
	addiu	$t0, $t0, 4
	sltu	$at, $t0, $t1
	bnez	$at, 1b
	sw	$zero, -4($t0)
2:
	jal	func_80006328
	nop
	.word	0x0001008D			/* break 1, 2 (main returned); as 2.6 has no two-code form */
	nop
