// SPDX-License-Identifier: MIT

#include <FB.h>
#include <string.h>

FB_Colour getColour(FB* fb, uint8_t r, uint8_t g, uint8_t b) {
  return
      (r << fb->red_field_position) |
      (b << fb->blue_field_position) |
      (g << fb->green_field_position);
}

void putPixel(uint32_t x, uint32_t y, FB_Colour colour, FB* fb) {
  uint8_t *pixel =
      fb->data + fb->stride * y + fb->offset * x;
  memcpy(pixel, &colour, fb->offset);
}
