#include <FB.h>
#include <ASMDefs.h>
#include <LoadKernel.h>
#include <multiboot2.h>

extern void initSSFN(FB* fb, void* ssfn);

void lmain(const void* mbi) {
    struct multiboot_tag* tag;
    FB fb = (FB) {.width = 0};
    uint8_t blue[] = {0, 0, 255};

    int cur_idx = 0;
    struct multiboot_tag_module* modules[64] = {0};

    for (tag = (struct multiboot_tag*) (mbi + 8);
         tag->type != MULTIBOOT_TAG_TYPE_END;
         tag = (struct multiboot_tag*) ((multiboot_uint8_t*) tag +
             ((tag->size + 7) & ~7))) {
        switch (tag->type) {
            case MULTIBOOT_TAG_TYPE_FRAMEBUFFER: {
                struct multiboot_tag_framebuffer* tagfb =
                    (struct multiboot_tag_framebuffer*) tag;

                if (tagfb->common.framebuffer_type != MULTIBOOT_FRAMEBUFFER_TYPE_RGB) _exit();

                unsigned int offset = 4;

                if (tagfb->common.framebuffer_bpp != 32) {
                    _exit();
                }

                fb = (FB) {
                    .height = tagfb->common.framebuffer_height,
                    .width = tagfb->common.framebuffer_width,
                    .stride = tagfb->common.framebuffer_pitch,
                    .offset = offset,
                    .size = tagfb->common.size,

                    .data = (void*) tagfb->common.framebuffer_addr,

                    .red_field_position = tagfb->framebuffer_red_field_position,
                    .red_mask_size = tagfb->framebuffer_red_mask_size,
                    .green_field_position = tagfb->framebuffer_green_field_position,
                    .green_mask_size = tagfb->framebuffer_green_mask_size,
                    .blue_field_position = tagfb->framebuffer_blue_field_position,
                    .blue_mask_size = tagfb->framebuffer_blue_mask_size
                };

                FB_Colour fb_blue = FbGetColour(&fb, blue[0], blue[1], blue[2]);

                FbFillScreen(fb_blue, &fb);
            }
                break;
            case MULTIBOOT_TAG_TYPE_MODULE: {
                struct multiboot_tag_module* module_tag =
                    (struct multiboot_tag_module*) tag;

                modules[cur_idx] = module_tag;

                cur_idx++;
            }
        }
    }

    void* ssfn = NULL;

    for (int i = 0; i < 64 && (modules[i] != NULL); i++) {
        if (memcmp((void*)modules[i]->mod_start, "SFN2", 4) == 0) {
            ssfn = (void*)modules[i]->mod_start;
            break;
        }
    }

    if (ssfn == NULL) _exit();

    initSSFN(&fb, ssfn);

    ELF_Object obj;

    FbPrint(&fb, "Welcome to kOS.Loader\n");

    FbPrint(&fb, "Trying to find the kernel...\n");

    bool found = false;

    for (int i = 0; i < 64 && (modules[i] != NULL); i++) {
        struct multiboot_tag_module* module_tag = modules[i];

        bool success = ElfCreateObject((char*) module_tag->mod_start,
                                       module_tag->mod_end - module_tag->mod_start,
                                       &obj
        );

        if (!success) {
            continue;
        }

        size_t magic_idx = ElfFindMagicHeaderIndex(&obj);
        if (magic_idx == -1) {
            continue;
        } else {
            if (ElfCheckMagicHeaderContents(&obj, magic_idx)) {
                // Found kOS!
                FbPrint(&fb, "Found kOS!\n");
                found = true;
                break;
            }
        }
    }

    if (!found) {
        FbPrintError(&fb, "Couldn't find kOS!\n");
        _exit();
    }

    FbPrint(&fb, "Loading kOS...\n");



    _exit();
}
