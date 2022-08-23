// SPDX-License-Identifier: MIT

.global GDTFlush
.type GDTFlush, @function
.extern pointerToGDT
GDTFlush:
    lgdt [pointerToGDT]
    mov %ax, 0x10
    mov %ds, %ax
    mov %es, %ax
    mov %fs, %ax
    mov %gs, %ax
    mov %ss, %ax
    jmp returnToC
returnToC:
    ret
