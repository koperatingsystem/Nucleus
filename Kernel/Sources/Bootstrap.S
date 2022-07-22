.section .text
.global _start
.type _start, @function
_start:
    cli
1:  hlt
    jmp 1
