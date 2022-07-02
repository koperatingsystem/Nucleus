# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.0)

project(kOS.Kernel LANGUAGES ASM C VERSION 1.0.0)

add_executable(kOS.Kernel
    Sources/Main.c
    Sources/Bootstrap.S
)

target_compile_options(kOS.Kernel PRIVATE -m64 -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -Wall -Werror -ffreestanding)
target_include_directories(kOS.Kernel PRIVATE Includes)

target_link_options(kOS.Kernel PRIVATE -nostdlib -T ${CMAKE_CURRENT_LIST_DIR}/Sources/link.ld -z max-page-size=0x1000)
target_link_libraries(kOS.Kernel PRIVATE kOS.libc)

set_target_properties(kOS.Kernel PROPERTIES LINK_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/Sources/link.ld)
