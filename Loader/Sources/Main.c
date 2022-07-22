#include <FB.h>
#include <ASMDefs.h>
#include <GDT.h>

#include <LoadKernel.h>
#include <multiboot2.h>

void lmain(const void *mbi) {
  struct multiboot_tag *tag;
  FB fb;
  // unsigned int mbi_size = *(unsigned int*)mbi;

  for (tag = (struct multiboot_tag *)(mbi + 8);
       tag->type != MULTIBOOT_TAG_TYPE_END;
       tag = (struct multiboot_tag *)((multiboot_uint8_t *)tag +
                                      ((tag->size + 7) & ~7))) {
    switch (tag->type) {
    case MULTIBOOT_TAG_TYPE_FRAMEBUFFER: {
      struct multiboot_tag_framebuffer *tagfb =
          (struct multiboot_tag_framebuffer *)tag;

      if (tagfb->common.framebuffer_type != MULTIBOOT_FRAMEBUFFER_TYPE_RGB) _exit();

      unsigned int offset;

      switch (tagfb->common.framebuffer_bpp) {
      case 8: {
        offset = 1;
      } break;
      case 15:
      case 16: {
        offset = 2;
      } break;
      case 24: {
        offset = 3;
      } break;

      case 32: {
        offset = 4;
      }
      }

      fb = (FB) {
        .height = tagfb->common.framebuffer_height,
        .width = tagfb->common.framebuffer_width,
        .stride = tagfb->common.framebuffer_pitch,
        .offset = offset,
        .size = tagfb->common.size,

        .data = (void*)tagfb->common.framebuffer_addr,

        .red_field_position = tagfb->framebuffer_red_field_position,
        .red_mask_size = tagfb->framebuffer_red_mask_size,
        .green_field_position = tagfb->framebuffer_green_field_position,
        .green_mask_size = tagfb->framebuffer_green_mask_size,
        .blue_field_position = tagfb->framebuffer_blue_field_position,
        .blue_mask_size = tagfb->framebuffer_blue_mask_size
      };

      FB_Colour blue = getColour(&fb, 0, 0, 255);

      for (unsigned x = 0; x < fb.width; x++) {
        for (unsigned y = 0; y < fb.height; y++) {
          putPixel(x, y, blue, &fb);
        }
      }
    }
      break;
    case MULTIBOOT_TAG_TYPE_MODULE: {
        // TODO: Check if the module is the kernel
        // 1) Check if it's an ELF File
        // 2) Find the address of .magic (if it exists)
        // 3) Check if 'kOS' is present
    }
    }
  }

  GDTInstall();

  _exit();
}
