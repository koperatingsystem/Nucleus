// SPDX-License-Identifier: MIT

#include <multiboot2.h>

.section .text
    .balign 8
    .align 4
mb_hdr:
    .long 0xE85250D6
    .long 0x0
    .long mb_hdr_end - mb_hdr
    .long -(0xE85250D6 + 0x0 + (mb_hdr_end - mb_hdr))

    # Module align

    .short 0x6
    .short 0x0
    .long 0x8
    .balign 8

    # Framebuffer

    .short 0x5
    .short 0x0
    .long 20
    .long 1920
    .long 1080
    .long 32
    .balign 8

    # Info request

    .short 1
    .short 0
    .long 4*6+8
    .long 5
    .long 1
    .long 3
    .long 9
    .long 6
    .long 10
    .balign 8

    # Terminator tag

    .short 0x0
    .short 0x0
    .long 0x8
mb_hdr_end:

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
.global _start
.type _start, @function
_start:
    cli

    cmp %eax, MULTIBOOT2_BOOTLOADER_MAGIC
    je _exit

	mov $stack_top, %esp

	push	%ebx
	call	lmain

.global _exit
.type _exit, @function
_exit:
    cli
1:  hlt
    jmp 1

