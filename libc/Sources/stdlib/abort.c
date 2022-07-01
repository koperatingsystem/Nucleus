// SPDX-License-Identifier: MIT

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

__attribute__((__noreturn__)) void abort(void)
{
	printf("abort()\n");
	while (true) ;
}
