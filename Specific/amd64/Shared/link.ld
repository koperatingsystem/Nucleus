ENTRY(_start)

KERNEL_LMA = 0x00100000;
KERNEL_VMA = 0xC0000000;

SECTIONS
{
    . = KERNEL_LMA;

    .bootstrap :
    {
        Specific/amd64/Loader/CMakeFiles/kOS.Specific.amd64.Loader.dir/Sources/Bootstrap.S.obj (.text)
    }

    . += KERNEL_VMA;

    .text : AT(ADDR(.text) - KERNEL_VMA)
    {
        _code = .;
        *(EXCLUDE_FILE(Specific/amd64/Loader/CMakeFiles/kOS.Specific.amd64.Loader.dir/Sources/Bootstrap.S.obj) .text)
        *(.rodata*)
        . = ALIGN(4096);
    }

   .data : AT(ADDR(.data) - KERNEL_VMA)
   {
        _data = .;
        *(.data)
        . = ALIGN(4096);
   }

   .eh_frame : AT(ADDR(.eh_frame) - KERNEL_VMA)
   {
       _ehframe = .;
       *(.eh_frame)
        . = ALIGN(4096);
   }

   .bss : AT(ADDR(.bss) - KERNEL_VMA)
   {
       _bss = .;
       *(.bss)

       /*
        * You usually need to include generated COMMON symbols
        * under kernel BSS section or use gcc's -fno-common
        */

        *(COMMON)
       . = ALIGN(4096);
   }

   _end = .;

   /DISCARD/ :
   {
        *(.comment)
   }
}
