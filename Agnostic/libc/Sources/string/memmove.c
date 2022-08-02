// SPDX-License-Identifier: MIT

#include <string.h>

void* memmove(void* restrict destination, const void* restrict source, size_t size)
{
	unsigned char* destination_bytes    = (unsigned char*)destination;
	const unsigned char* source_bytes   = (const unsigned char*)source;

	if (destination_bytes < source_bytes)   for (size_t i = 0; i < size; i++)   destination_bytes[i]        = source_bytes[i];
	else                                    for (size_t i = size; i != 0; i--)  destination_bytes[i - 1]    = source_bytes[i - 1];

	return destination;
}
