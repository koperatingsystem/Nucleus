# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.0.0)
project(kOS.ELFLoader LANGUAGES C VERSION 1.0.0)

set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/Includes/ELF/ProgramHeader.h
    ${CMAKE_CURRENT_LIST_DIR}/Includes/ELF/SectionHeader.h
    ${CMAKE_CURRENT_LIST_DIR}/Includes/ELF.h

    ${CMAKE_CURRENT_LIST_DIR}/Sources/ELF.c
    ${CMAKE_CURRENT_LIST_DIR}/Sources/ProgramHeader.c
    ${CMAKE_CURRENT_LIST_DIR}/Sources/SectionHeader.c
)

add_library(kOS.ELFLoader ${SOURCES})

target_include_directories(kOS.ELFLoader PRIVATE Includes)

add_library(kOS.ELFLoader.32 ${SOURCES})

target_include_directories(kOS.ELFLoader.32 PRIVATE Includes)

target_compile_options(kOS.ELFLoader.32 PUBLIC -m32 -target i386-pc-none)
