# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.0)

project(kOS.Loader LANGUAGES ASM C VERSION 1.0.0)

add_executable(kOS.Loader
        Sources/Bootstrap.S Sources/GDT.c Sources/GDT.S Sources/LoadKernel.c
        Sources/Main.c Includes/GDT.h Includes/LoadKernel.h)

target_compile_options(kOS.Loader PRIVATE -m32 -target i386-pc-none -Wall -Werror -ffreestanding)
target_include_directories(kOS.Loader PRIVATE Includes)

target_link_libraries(kOS.Loader PUBLIC kOS.libc.32 kOS.LKI.32)
target_link_options(kOS.Loader PRIVATE -nostdlib -z max-page-size=0x1000)

add_target_output_iso(kOS.Loader boot)
