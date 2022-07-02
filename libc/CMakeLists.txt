# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.0.0)

project(kOS.libc LANGUAGES C VERSION 1.0.0)

add_library(kOS.libc STATIC
    Includes/sys/cdefs.h
    Includes/stdbool.h
    Includes/stddef.h
    Includes/stdint.h
    Includes/stdio.h
    Includes/stdlib.h
    Includes/string.h

    Sources/stdio/printf.c
    Sources/stdio/putchar.c
    Sources/stdio/puts.c

    Sources/stdlib/abort.c

    Sources/string/memcmp.c
    Sources/string/memcpy.c
    Sources/string/memmove.c
    Sources/string/memset.c
    Sources/string/strlen.c
)

target_compile_options(kOS.libc
    PUBLIC -fshort-wchar -fno-builtin -ffreestanding -nostdinc
    PRIVATE -Wall -Werror
)

target_include_directories(kOS.libc PUBLIC Includes)

target_link_options(kOS.libc PRIVATE -nostdlib)
