# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.0)

project(kOS.LKI LANGUAGES ASM C VERSION 1.0.0)

set(SOURCES
        Sources/FB.c
        Includes/multiboot2.h
        Includes/ssfn.h)

add_library(kOS.LKI STATIC ${SOURCES})

target_compile_options(kOS.LKI
        PUBLIC ${SHARED_COMPILE_OPTIONS}
)

target_include_directories(kOS.LKI PUBLIC Includes)

target_link_options(kOS.LKI PRIVATE ${SHARED_LINK_OPTIONS})

target_link_libraries(kOS.LKI PUBLIC kOS.libc kOS.LKI.Headers)

add_library(kOS.LKI.32 STATIC ${SOURCES})

target_compile_options(kOS.LKI.32
        PUBLIC ${SHARED_COMPILE_OPTIONS} -m32 -target i686-unknown-none
)

target_include_directories(kOS.LKI.32 PUBLIC Includes)

target_link_options(kOS.LKI.32 PRIVATE ${SHARED_LINK_OPTIONS})

target_link_libraries(kOS.LKI.32 PUBLIC kOS.libc.Loader kOS.LKI.Headers)

