# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.0)

project(kOS.Loader LANGUAGES ASM C VERSION 1.0.0)

add_executable(kOS.Loader
        Sources/Bootstrap.S Sources/GDT.c Sources/GDT.S Sources/LoadKernel.c
        Sources/Main.c Includes/multiboot2.h Includes/GDT.h Sources/Blue.c Includes/Blue.h Includes/LoadKernel.h ../Shared/LoaderKernel/Entry.h ../Shared/LoaderKernel/FB.h)

target_compile_options(kOS.Loader PRIVATE -m32 -target i386-pc-none -Wall -Werror -ffreestanding)
target_include_directories(kOS.Loader PRIVATE Includes ../Shared/LoaderKernel)

target_link_libraries(kOS.Loader PUBLIC kOS.libc)
target_link_options(kOS.Loader PRIVATE -nostdlib -z max-page-size=0x1000)
set_target_properties(kOS.Loader PROPERTIES LINK_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/Sources/link.ld)


add_target_output_iso(kOS.Loader boot)
