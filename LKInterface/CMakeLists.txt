# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.0)

project(kOS.LKI LANGUAGES ASM C VERSION 1.0.0)

set(SOURCES
        Sources/FB.c
        Includes/FB.h
        Includes/Entry.h
        Includes/multiboot2.h
)

set(COMPILE_OPTS_PUBLIC  -fshort-wchar -fno-builtin -ffreestanding -nostdinc)
set(COMPILE_OPTS_PRIVATE -Wall -Werror)

add_library(kOS.LKI STATIC ${SOURCES})

target_compile_options(kOS.LKI
        PUBLIC ${COMPILE_OPTS_PUBLIC}
        PRIVATE ${COMPILE_OPTS_PRIVATE}
        )

target_include_directories(kOS.LKI PUBLIC Includes)

target_link_options(kOS.LKI PRIVATE -nostdlib)

target_link_libraries(kOS.LKI PUBLIC kOS.libc)

add_library(kOS.LKI.32 STATIC ${SOURCES})

target_compile_options(kOS.LKI.32
        PUBLIC ${COMPILE_OPTS_PUBLIC} -m32 -target i686-unknown-none
        PRIVATE ${COMPILE_OPTS_PRIVATE}
        )

target_include_directories(kOS.LKI.32 PUBLIC Includes)

target_link_options(kOS.LKI.32 PRIVATE -nostdlib)

target_link_libraries(kOS.LKI.32 PUBLIC kOS.libc.32)

