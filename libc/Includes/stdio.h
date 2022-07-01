// SPDX-License-Identifier: MIT

#pragma once

#include <sys/cdefs.h>

// TODO: add more stuff to comply with C11 / C17

#define EOF (-1)

#ifdef __cplusplus
extern "C"
{
#endif

int printf(const char* restrict format, ...);
int putchar(int character);
int puts(const char* message);

#ifdef __cplusplus
}
#endif
