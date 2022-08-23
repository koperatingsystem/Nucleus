// SPDX-License-Identifier: MIT

.code64

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

    movabsq $stack_top, %rsp

	movabsq $(kOSMain), %rax
    callq   *%rax
