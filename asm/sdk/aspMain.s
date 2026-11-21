/*
 * aspMain -- the SDK's audio microcode, linked whole as the SDK ships it (an object rsp2elf made).
 *
 * The audio manager runs it for every audio task.  No source rebuilds it: the bytes are taken from the
 * cartridge (baserom.z64, which the build writes) and count as asset bytes, not as bytes from source.
 */
	.text
	.globl	aspMainTextStart
aspMainTextStart:
	.incbin	"baserom.z64", 0x37E98, 0xE20
	.globl	aspMainTextEnd
aspMainTextEnd:

	.data
	.globl	aspMainDataStart
aspMainDataStart:
	.incbin	"baserom.z64", 0x847C8, 0x2C0
	.globl	aspMainDataEnd
aspMainDataEnd:
