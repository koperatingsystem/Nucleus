// SPDX-License-Identifier: MIT

#pragma once

#include <sys/cdefs.h>
#include <stddef.h>

// TODO: add more stuff to comply with C11 / C17

#ifdef __cplusplus
extern "C"
{
#endif

int     memcmp(const void* restrict destination, const void* restrict source, size_t size);
void*   memcpy(void* restrict destination, const void* restrict source, size_t size);
void*   memmove(void* restrict destination, const void* restrict source, size_t size);
void*   memset(void* destination, int value, size_t size);

size_t strlen(const char* string);

#ifdef __cplusplus
}
#endif
