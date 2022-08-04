// SPDX-License-Identifier: MIT

#include <FB.h>
#include <string.h>

#define SSFN_CONSOLEBITMAP_CONTROL
#define SSFN_CONSOLEBITMAP_TRUECOLOR
#include <ssfn.h>

void initSSFN(FB* fb, void* ssfn) {
    ssfn_src = ssfn;

    ssfn_dst.ptr = fb->data;
    ssfn_dst.fg = getColour(fb, 0, 0, 0);
    ssfn_dst.bg = 0x00000000;
    ssfn_dst.p = fb->width * fb->offset;
    ssfn_dst.x = 0;
    ssfn_dst.y = 0;
}

FB_Colour getColour(FB* fb, uint8_t r, uint8_t g, uint8_t b) {
    return
        (r << fb->red_field_position) |
            (b << fb->blue_field_position) |
            (g << fb->green_field_position);
}

void putPixel(uint32_t x, uint32_t y, FB_Colour colour, FB* fb) {
    uint8_t* pixel =
        fb->data + fb->stride * y + fb->offset * x;
    memcpy(pixel, &colour, fb->offset);
}

void fillScreen(FB_Colour colour, FB* fb) {
    for (uint32_t x = 0; x < fb->width; x++) {
        for (uint32_t y = 0; y < fb->height; y++) {
            putPixel(x, y, colour, fb);
        }
    }
}

void print(FB* fb, const char* str) {
    size_t str_len = strlen(str);
    for (size_t i = 0; i < str_len; i++) {
        ssfn_putc(str[i]);
    }
}

void printError(FB* fb, const char* str) {
    ssfn_dst.fg = getColour(fb, 255, 0, 0);
    print(fb, str);
    ssfn_dst.fg = 0xFFFFFFFF;
}
