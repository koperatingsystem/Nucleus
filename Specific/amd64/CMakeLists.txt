# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.0)

project(kOS.Specific.x86)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/Shared/)
include(iso-tools)

add_subdirectory(LKInterface)
add_subdirectory(Loader)

add_file_iso(${CMAKE_CURRENT_LIST_DIR}/Shared/u_vga16.sfn boot)
add_file_iso(${CMAKE_CURRENT_LIST_DIR}/Shared/grub.cfg boot/grub)
