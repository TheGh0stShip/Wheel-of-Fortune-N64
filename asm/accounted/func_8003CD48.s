.text
.set noreorder
.globl __osDisableInt ; .align 2 ; ; .ent __osDisableInt,0 ; __osDisableInt: ; .frame $29,0,$31
    mfc0 $8, $12
    and $9, $8, ~0x00000001
    mtc0 $9, $12
    andi $2, $8, 0x00000001
    nop
    jr $31
     nop
.end __osDisableInt
.globl __osRestoreInt ; .align 2 ; ; .ent __osRestoreInt,0 ; __osRestoreInt: ; .frame $29,0,$31
    mfc0 $8, $12
    or $8, $8, $4
    mtc0 $8, $12
    nop
    nop
    jr $31
     nop
.end __osRestoreInt
