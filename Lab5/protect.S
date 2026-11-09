.equ WEB_BASE,  0x41500000
.equ GAME_BASE, 0x44500000

.section .text
.global _start
_start:
    ldr  x0, =vectors          // where to go if the MMU blocks an access
    msr  vbar_el1, x0
    isb

    // ----- NO MMU -----
    ldr  x0, =WEB_BASE
    mov  x1, #0x41
    str  x1, [x0]              // Web Browser saves 'A' in its memory
web_nommu:
    nop
    ldr  x0, =WEB_BASE
    str  xzr, [x0]             // Game writes into Web Browser's memory
game_nommu:
    nop

    // ----- WITH MMU -----
    ldr  x0, =l2_code
    ldr  x1, =0x40000705
    str  x1, [x0]
    ldr  x0, =l1_web
    ldr  x1, =l2_web
    ldr  x2, =l3_web
    ldr  x3, =WEB_BASE
    bl   build_tables
    ldr  x0, =l1_game
    ldr  x1, =l2_game
    ldr  x2, =l3_game
    ldr  x3, =GAME_BASE
    bl   build_tables
    ldr  x1, =0xFF00
    msr  mair_el1, x1
    ldr  x1, =0x803519
    msr  tcr_el1, x1

    ldr  x0, =l1_web           // run Web Browser
    msr  ttbr0_el1, x0
    isb
    tlbi vmalle1
    dsb  ish
    isb
    mrs  x1, sctlr_el1
    orr  x1, x1, #1            // MMU ON
    msr  sctlr_el1, x1
    isb
    mov  x0, #0
    mov  x1, #0x41
    str  x1, [x0]              // Web Browser saves 'A'
web_mmu:
    nop

    ldr  x0, =l1_game          // switch to Game
    msr  ttbr0_el1, x0
    isb
    tlbi vmalle1
    dsb  ish
    isb
    ldr  x0, =WEB_BASE
    str  xzr, [x0]             // Game tries the same write
attack_mmu:
    nop                        // only reached if NOT blocked
    b    attack_mmu

build_tables:
    orr  x4, x1, #3
    str  x4, [x0]
    ldr  x4, =l2_code
    orr  x4, x4, #3
    str  x4, [x0, #8]
    orr  x4, x2, #3
    str  x4, [x1]
    ldr  x5, =0x707
    orr  x4, x3, x5
    mov  x6, #0
1:  str  x4, [x2, x6, lsl #3]
    add  x4, x4, #0x1000
    add  x6, x6, #1
    cmp  x6, #16
    b.lt 1b
    ret

.balign 2048
vectors:
    .skip 0x200
    mrs  x10, esr_el1          // why it was blocked
    mrs  x11, far_el1          // which address
fault_caught:
    b    fault_caught

.section .bss
.balign 4096
l1_web:  .space 4096
l2_web:  .space 4096
l3_web:  .space 4096
l1_game: .space 4096
l2_game: .space 4096
l3_game: .space 4096
l2_code: .space 4096
