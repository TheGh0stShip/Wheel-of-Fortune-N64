/*
 * A second graphics microcode of the same family as the one at 0x80034A88, linked whole as an SDK object.
 *
 * 2659 of the first 0x1400 bytes of its text and 34 of its 0x800 bytes of data differ from that one's.
 * Nothing in the code names it: the game links it and never runs it.  The bytes do not say which SDK
 * microcode it is, so the symbols carry their addresses.  No source rebuilds it: the bytes are taken from
 * the cartridge and count as asset bytes.
 */
	.text
	.globl	D_80035E88
D_80035E88:
	.incbin	"baserom.z64", 0x36A88, 0x1410

	.data
	.globl	D_800833C8
D_800833C8:
	.incbin	"baserom.z64", 0x83FC8, 0x800
