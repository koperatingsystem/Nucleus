// SPDX-License-Identifier: MIT

#ifndef LKI_FB_H
#define LKI_FB_H

#include <stdint.h>

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

typedef uint32_t FB_Colour;

FB_Colour getColour(FB* fb, uint8_t r, uint8_t g, uint8_t b);

void putPixel(uint32_t x, uint32_t y, FB_Colour colour, FB* fb);

void fillScreen(FB_Colour colour, FB* fb);

#endif
