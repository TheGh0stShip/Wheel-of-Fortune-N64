.text
.globl osInvalDCache ; .align 2 ; ; .ent osInvalDCache,0 ; osInvalDCache: ; .frame $29,0,$31
    blez $5, 3f
    li $11, 0x2000
    bgeu $5, $11, 4f
    move $8, $4
    addu $9, $4, $5
    bgeu $8, $9, 3f
    addiu $9, $9, -16
    andi $10, $8, (16 -1)
    beqz $10, 1f
    subu $8, $8, $10
    .set noreorder ; cache (0x14 | 0x1), ($8) ; .set reorder
    bgeu $8, $9, 3f
    addiu $8, $8, 16
1:
    andi $10, $9, (16 -1)
    beqz $10, 2f
    subu $9, $9, $10
    .set noreorder ; cache (0x14 | 0x1), 16($9) ; .set reorder
    bltu $9, $8, 3f
2:
    .set noreorder ; cache (0x10 | 0x1), ($8) ; .set reorder
    .set noreorder
    bltu $8, $9, 2b
     addiu $8, $8, 16
    .set reorder
3:
    jr $31
4:
    li $8, 0x80000000
    addu $9, $8, $11
    addiu $9, $9, -16
5:
    .set noreorder ; cache (0x0 | 0x1), ($8) ; .set reorder
    .set noreorder
    bltu $8, $9, 5b
     addiu $8, $8, 16
    .set reorder
    jr $31
.end osInvalDCache
