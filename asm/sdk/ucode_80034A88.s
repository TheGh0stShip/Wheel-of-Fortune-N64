/*
 * The graphics microcode createGfxTask runs, linked whole as an SDK object.
 *
 * Its data says "RSP SW Version: 2.0H, 02-12-97", and the task gives it no output buffer and a yield
 * buffer of 0x900 bytes: one of the SDK's Fast3D-family microcodes that send their output straight to the
 * RDP, gspFast3D or gspF3DNoN.  The bytes do not say which, so the symbols carry their addresses.  No source
 * rebuilds it: the bytes are taken from the cartridge and count as asset bytes.
 */
	.text
	.globl	D_80034A88
D_80034A88:
	.incbin	"baserom.z64", 0x35688, 0x1400

	.data
	.globl	D_80082BC8
D_80082BC8:
	.incbin	"baserom.z64", 0x837C8, 0x800
