#include <ASMDefs.h>
#include <GDT.h>
#include <multiboot.h>

void lmain(const void* mb_struct) {
    GDTInstall();

    _exit();
}
