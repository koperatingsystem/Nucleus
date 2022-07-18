# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.0.0)

project(kOS.libc LANGUAGES C ASM VERSION 1.0.0)

set(SOURCES
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

add_library(kOS.libc.32 STATIC
    ${SOURCES}
)

add_library(kOS.libc STATIC
        ${SOURCES}
)

target_compile_options(kOS.libc
    PUBLIC -fshort-wchar -fno-builtin -ffreestanding -nostdinc
    PRIVATE -Wall -Werror
)

target_include_directories(kOS.libc PUBLIC Includes)

target_link_options(kOS.libc.32 PRIVATE -nostdlib)

target_compile_options(kOS.libc
        PUBLIC -fshort-wchar -fno-builtin -ffreestanding -nostdinc -m32 -target i386-pc-none
        PRIVATE -Wall -Werror
        )

target_include_directories(kOS.libc.32 PUBLIC Includes)

target_link_options(kOS.libc.32 PRIVATE -nostdlib)
