// SPDX-License-Identifier: MIT

#pragma once

#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef _VA_LIST
typedef __builtin_va_list va_list;
#define _VA_LIST
#endif

#define va_start(ap, param) __builtin_va_start(ap, param)
#define va_end(ap)          __builtin_va_end(ap)
#define va_arg(ap, type)    __builtin_va_arg(ap, type)
#define va_copy(dest, src)  __builtin_va_copy(dest, src)

#ifdef __cplusplus
}
#endif
