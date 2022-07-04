# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.0)

project(kOS.Loader LANGUAGES ASM C VERSION 1.0.0)

add_executable(kOS.Loader
        Sources/Bootstrap.S
        Sources/Main.c Includes/multiboot.h)

target_compile_options(kOS.Loader PRIVATE -m32 -Wall -Werror -ffreestanding)
target_include_directories(kOS.Loader PRIVATE Includes)

target_link_options(kOS.Loader PRIVATE -nostdlib)

add_target_output_iso(kOS.Loader boot)
