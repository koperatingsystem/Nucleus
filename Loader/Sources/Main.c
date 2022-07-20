#include "../../Shared/LoaderKernel/Entry.h"
#include "../../Shared/LoaderKernel/FB.h"
#include <ASMDefs.h>
#include <Blue.h>
#include <GDT.h>

#include <LoadKernel.h>
#include <multiboot2.h>

void lmain(const void *mbi) {
  struct multiboot_tag *tag;
  // unsigned int mbi_size = *(unsigned int*)mbi;

  for (tag = (struct multiboot_tag *)(mbi + 8);
       tag->type != MULTIBOOT_TAG_TYPE_END;
       tag = (struct multiboot_tag *)((multiboot_uint8_t *)tag +
                                      ((tag->size + 7) & ~7))) {
    switch (tag->type) {
    case MULTIBOOT_TAG_TYPE_FRAMEBUFFER: {
      fillBlue(tag);
    }
      break;
    case MULTIBOOT_TAG_TYPE_MODULE: {

    }
    }
  }

  GDTInstall();

  _exit();
}
