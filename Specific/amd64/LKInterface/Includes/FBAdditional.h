// SPDX-License-Identifier: MIT

#pragma once

#ifndef LKI_FBADDITIONAL_H
#define LKI_FBADDITIONAL_H

#include <stdint.h>
#include <stddef.h>

#include <LKI.h>

typedef struct FB {
    uint32_t height;
    uint32_t width;
    uint32_t stride;
    uint8_t offset;
    uint32_t size;

    void* restrict data;

    uint8_t red_field_position;
    uint8_t red_mask_size;
    uint8_t green_field_position;
    uint8_t green_mask_size;
    uint8_t blue_field_position;
    uint8_t blue_mask_size;
} FB;

void initSSFN(FB* fb, void* ssfn);

typedef uint32_t FB_Colour;

FB_Colour FbGetColour(FB* fb, uint8_t r, uint8_t g, uint8_t b);

void FbPutPixel(uint32_t x, uint32_t y, FB_Colour colour, FB* fb);

void FbFillScreen(FB_Colour colour, FB* fb);


#endif
