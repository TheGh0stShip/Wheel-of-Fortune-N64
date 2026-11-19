.text
.globl osWritebackDCache ; .align 2 ; ; .ent osWritebackDCache,0 ; osWritebackDCache: ; .frame $29,0,$31
    blez $5, 2f
    li $11, 0x2000
    bgeu $5, $11, 3f
    move $8, $4
    addu $9, $4, $5
    bgeu $8, $9, 2f
    addiu $9, $9, -16
    andi $10, $8, (16 -1)
    subu $8, $8, $10
1:
    .set noreorder
    cache (0x18 | 0x1), ($8)
    bltu $8, $9, 1b
     addiu $8, $8, 16
    .set reorder
2:
    jr $31
3:
    li $8, 0x80000000
    addu $9, $8, $11
    addiu $9, $9, -16
4:
    .set noreorder
    cache (0x0 | 0x1), ($8)
    bltu $8, $9, 4b
     addiu $8, $8, 16
    .set reorder
    jr $31
.end osWritebackDCache
