# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.0)

project(kOS.Specific.amd64.Loader LANGUAGES ASM C VERSION 1.0.0)

add_executable(kOS.Specific.amd64.Loader
        Sources/Bootstrap.S Sources/LoadKernel.c
        Sources/Main.c Includes/LoadKernel.h)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(kOS.Specific.amd64.Loader PRIVATE LOW_RES_FB)
endif()

target_compile_definitions(kOS.Specific.amd64.Loader PRIVATE VERSION=${PROJECT_VERSION})

target_compile_options(kOS.Specific.amd64.Loader PRIVATE ${SHARED_COMPILE_OPTIONS} -m32 -target i686-unknown-none)
target_include_directories(kOS.Specific.amd64.Loader PRIVATE Includes)

target_link_libraries(kOS.Specific.amd64.Loader PUBLIC kOS.libc.Loader kOS.LKI.32 kOS.LKI.Headers)
target_link_options(kOS.Specific.amd64.Loader PRIVATE -nostdlib -z max-page-size=0x1000 -T ${CMAKE_CURRENT_LIST_DIR}/Sources/link.ld)
set_target_properties(kOS.Specific.amd64.Loader PROPERTIES LINK_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/Sources/link.ld)


add_target_output_iso(kOS.Specific.amd64.Loader boot)
