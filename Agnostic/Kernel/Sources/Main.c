// SPDX-License-Identifier: MIT

#include <Entry.h>
#include <FB.h>
#include <stdbool.h>

void KaOSMain(FB* framebuffer_info) {
    FB_Colour blue = FbGetColour(framebuffer_info, 0, 0, 200);

    for (unsigned x = 0; x < framebuffer_info->width; x++) {
        for (unsigned y = 0; y < framebuffer_info->height; y++) {
            FbPutPixel(x, y, blue, framebuffer_info);
        }
    }

    while (true) ;
}
