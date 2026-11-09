.equ ADDR0_NOMMU, 0x40400000
.equ WEB_BASE,    0x41500000
.equ GAME_BASE,   0x44500000

.section .text
.global _start
_start:
    // ----- NO MMU -----
    ldr  x0, =ADDR0_NOMMU
    mov  x1, #0x41             // 'A'
    str  x1, [x0]              // Web Browser saves 'A' at Address 0
web_nommu:
    nop
    str  xzr, [x0]             // Game deletes Address 0
game_nommu:
    nop

    // ----- WITH MMU -----
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
    str  x1, [x0]              // Web Browser saves 'A' at Address 0
web_mmu:
    nop

    ldr  x0, =l1_game          // switch to Game
    msr  ttbr0_el1, x0
    isb
    tlbi vmalle1
    dsb  ish
    isb
    mov  x0, #0
    str  xzr, [x0]             // Game deletes Address 0
game_mmu:
    nop
done:
    b    done

build_tables:
    orr  x4, x1, #3
    str  x4, [x0]
    ldr  x4, =0x40000705
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

.section .bss
.balign 4096
l1_web:  .space 4096
l2_web:  .space 4096
l3_web:  .space 4096
l1_game: .space 4096
l2_game: .space 4096
l3_game: .space 4096
