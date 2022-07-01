// SPDX-License-Identifier: MIT

#include <string.h>

void* memset(void* buffer, int value, size_t size)
{
	unsigned char* buffer_bytes = (unsigned char*)buffer;
    unsigned char value_byte = (unsigned char)value;

	for (size_t i = 0; i < size; i++) buffer_bytes[i] = value_byte;

	return buffer;
}
