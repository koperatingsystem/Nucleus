# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.18.0)

project(kOS.Kernel LANGUAGES ASM C VERSION 1.0.0)

add_executable(kOS.Kernel
    ${CMAKE_CURRENT_LIST_DIR}/Sources/Kernel/Main.c
    ${CMAKE_CURRENT_LIST_DIR}/Sources/Kernel/Bootstrap.S
)

target_compile_options(kOS.Kernel PRIVATE -m64 -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -Wall -Werror -ffreestanding)
target_include_directories(kOS.Kernel PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Includes)

target_link_options(kOS.Kernel PRIVATE -nostdlib -T ${CMAKE_CURRENT_LIST_DIR}/Sources/Kernel/link.ld -z max-page-size=0x1000)
target_link_libraries(kOS.Kernel PRIVATE kOS.libc)
