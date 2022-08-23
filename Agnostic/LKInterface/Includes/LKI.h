// SPDX-License-Identifier: MIT

#pragma once

#ifndef LKI_FB_H
#define LKI_FB_H

#include <stdint.h>
#include <stddef.h>

typedef void* Log;

typedef struct LKI {
    Log log;
} LKI;


void LogPrint(Log log, const char* str);

#endif
