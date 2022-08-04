# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.0)

project(kOS.Kernel LANGUAGES ASM C VERSION 1.0.0)

add_executable(kOS.Kernel
    Sources/Main.c
    Sources/Bootstrap.S
    Sources/Magic.S
)

target_compile_options(kOS.Kernel PRIVATE ${KERNEL_COMPILE_OPTIONS})

target_link_options(kOS.Kernel PRIVATE ${KERNEL_LINK_OPTIONS})
target_link_libraries(kOS.Kernel PRIVATE kOS.libc kOS.LKI kOS.LKI.Headers)

set_target_properties(kOS.Kernel PROPERTIES LINK_DEPENDS ${KERNEL_LINK_DEPENDS})
