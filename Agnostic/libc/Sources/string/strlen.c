// SPDX-License-Identifier: MIT

#include <string.h>

size_t strlen(const char *str)
{
	size_t len = 0;
	while (len <= SIZE_MAX && str[len] != '\0') len++;

	return len;
}
