.set ALIGN,    1<<0
.set MEMINFO,  1<<1
.set VMODE,    1<<2
.set FLAGS,    ALIGN | MEMINFO | VMODE
.set MAGIC,    0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.long 0
.long 0
.long 0
.long 0
.long 0
.long 0
.long 1920
.long 1080
.long 32

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

    cmp %eax, 0x2BADB002
    jne non_multiboot

	mov $stack_top, %esp
	mov $stack_top, %ebp

	push	%ebx
	call	lmain

non_multiboot:
    cli
1:  hlt
    jmp 1

.global _exit
.type _exit, @function
_exit:
    cli
1:  hlt
    jmp 1
