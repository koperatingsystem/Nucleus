// SPDX-License-Identifier: MIT

#include <string.h>

void* memcpy(void* restrict destination, const void* restrict source, size_t size)
{
	unsigned char* destination_bytes    = (unsigned char*)destination;
	const unsigned char* source_bytes   = (const unsigned char*)source;

	for (size_t i = 0; i < size; i++) destination_bytes[i] = source_bytes[i];

	return destination;
}
