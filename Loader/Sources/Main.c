#include <ASMDefs.h>
#include <GDT.h>
#include <multiboot2.h>
#include <string.h>

void lmain(const void* mbi) {
    struct multiboot_tag* tag;
    //unsigned int mbi_size = *(unsigned int*)mbi;

    for (tag = (struct multiboot_tag*) (mbi + 8);
         tag->type != MULTIBOOT_TAG_TYPE_END;
         tag = (struct multiboot_tag*) ((multiboot_uint8_t*) tag
             + ((tag->size + 7) & ~7))) {
        switch (tag->type) {
            case MULTIBOOT_TAG_TYPE_FRAMEBUFFER: {
                multiboot_uint32_t color;
                unsigned i;
                struct multiboot_tag_framebuffer* tagfb
                    = (struct multiboot_tag_framebuffer*) tag;
                void* fb = (void*) (unsigned long) tagfb->common.framebuffer_addr;

                switch (tagfb->common.framebuffer_type) {
                    case MULTIBOOT_FRAMEBUFFER_TYPE_INDEXED: {
                        unsigned int distance;
                        struct multiboot_color* palette = tagfb->framebuffer_palette;

                        color = 0;
                        unsigned int best_distance = 4 * 256 * 256;

                        for (i = 0; i < tagfb->framebuffer_palette_num_colors; i++) {
                            distance = (0xff - palette[i].blue)
                                * (0xff - palette[i].blue)
                                + palette[i].red * palette[i].red
                                + palette[i].green * palette[i].green;
                            if (distance < best_distance) {
                                color = i;
                                best_distance = distance;
                            }
                        }
                    }
                        break;

                    case MULTIBOOT_FRAMEBUFFER_TYPE_RGB:
                        color = ((1 << tagfb->framebuffer_blue_mask_size) - 1)
                            << tagfb->framebuffer_blue_field_position;
                        break;

                    case MULTIBOOT_FRAMEBUFFER_TYPE_EGA_TEXT:color = '\\' | 0x0100;
                        break;

                    default:color = 0xffffffff;
                        break;
                }

                unsigned int offset;

                switch (tagfb->common.framebuffer_bpp) {
                    case 8: {
                        offset = 1;
                    }
                        break;
                    case 15:
                    case 16: {
                        offset = 2;
                    }
                        break;
                    case 24: {
                        offset = 4;
                    }
                        break;

                    case 32: {
                        offset = 4;
                    }
                }

                for (unsigned int x = 0; x < tagfb->common.framebuffer_width; x++) {
                    for (unsigned int y = 0; y < tagfb->common.framebuffer_height; y++) {
                        multiboot_uint8_t* pixel = fb
                            + tagfb->common.framebuffer_pitch * y + offset * x;
                        memcpy(pixel, &color, offset);
                    }
                }
            }
        }
    }

    GDTInstall();

    _exit();
}
