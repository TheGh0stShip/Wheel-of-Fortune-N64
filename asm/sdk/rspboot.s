/*
 * rspboot -- the SDK's RSP boot microcode, linked whole as the SDK ships it (an object rsp2elf made).
 *
 * Every RSP task names it as its ucode_boot.  No source rebuilds it: the bytes are taken from the cartridge
 * (baserom.z64, which the build writes) and count as asset bytes, not as bytes from source.
 */
	.text
	.globl	rspbootTextStart
rspbootTextStart:
	.incbin	"baserom.z64", 0x355B8, 0xD0
	.globl	rspbootTextEnd
rspbootTextEnd:
