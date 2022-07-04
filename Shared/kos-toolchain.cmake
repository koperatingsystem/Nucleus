# SPDX-License-Identifier: MIT

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)

set(CMAKE_C_COMPILER clang)
set(CMAKE_C_COMPILER_TARGET amd64-pc-none)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_COMPILER_TARGET amd64-pc-none)

set(CMAKE_C_LINK_EXECUTABLE "clang -fuse-ld=lld <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o<TARGET> <LINK_LIBRARIES>")
set(CMAKE_CXX_LINK_EXECUTABLE "ld.lld -fuse-ld=lld <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o<TARGET> <LINK_LIBRARIES>")

set(kOS 1)
