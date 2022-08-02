// SPDX-License-Identifier: MIT

#include <string.h>

int memcmp(const void* destination, const void* source, size_t size)
{
	const unsigned char* destination_bytes  = (const unsigned char*)destination;
	const unsigned char* source_bytes       = (const unsigned char*)source;

	for (size_t i = 0; i < size; i++) if (destination_bytes[i] != source_bytes[i]) return destination_bytes[i] > source_bytes[i] ? 1 : -1;

	return 0;
}
