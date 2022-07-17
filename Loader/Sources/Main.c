#include <ASMDefs.h>
#include <GDT.h>

void lmain(const void* mb_struct) {
    GDTInstall();

    _exit();
}
