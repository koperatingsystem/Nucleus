# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.0)

project(kOS.Specific.riscv64.Loader LANGUAGES ASM C VERSION 1.0.0)

add_executable(kOS.Specific.riscv64.Loader
        Sources/Bootstrap.S Sources/Loader.c
        )

target_compile_definitions(kOS.Specific.riscv64.Loader PRIVATE VERSION=${PROJECT_VERSION})

target_compile_options(kOS.Specific.riscv64.Loader PRIVATE ${SHARED_COMPILE_OPTIONS})
target_include_directories(kOS.Specific.riscv64.Loader PRIVATE Includes)

target_link_libraries(kOS.Specific.riscv64.Loader PUBLIC
        kOS.libc.Loader kOS.LKI kOS.LKI.Headers
)

target_link_options(kOS.Specific.riscv64.Loader PRIVATE -nostdlib)
