# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.0)

project(kOS.Specific.x86)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/Shared/)
include(iso-tools)

add_subdirectory(LKInterface)
add_subdirectory(Loader)
