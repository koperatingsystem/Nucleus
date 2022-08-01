// SPDX-License-Identifier: MIT

#ifndef LOADKERNEL_H
#define LOADKERNEL_H

#include <stdbool.h>
#include <multiboot2.h>
#include <stdint.h>
#include <string.h>

typedef struct ELF_Header_Data
{
    uint8_t     magic[4];
    uint8_t     binary_class;
    uint8_t     data_encoding;
    uint8_t     version_ident;
    uint8_t     abi;
    uint8_t     abi_version;
    uint8_t     padding[7];
    uint16_t    type;
    uint16_t    machine;
    uint32_t    version;
    uint64_t    entrypoint;
    uint64_t    program_header_offset;
    uint64_t    section_header_offset;
    uint32_t    flags;
    uint16_t    header_size;
    uint16_t    program_header_entry_size;
    uint16_t    program_header_entry_count;
    uint16_t    section_header_entry_size;
    uint16_t    section_header_entry_count;
    uint16_t    section_header_names_index;
} ELF_Header_Data;

typedef struct ELF_Program_Header_Data
{
    uint32_t    type;
    uint32_t    flags;
    uint64_t    offset;
    uint64_t    vaddr;
    uint64_t    paddr;
    uint64_t    file_size;
    uint64_t    mem_size;
    uint64_t    align;
} ELF_Program_Header_Data;

typedef struct ELF_Section_Header_Data {
    uint32_t    name;
    uint32_t    type;
    uint64_t    flags;
    uint64_t    addr;
    uint64_t    offset;
    uint64_t    size;
    uint32_t    link;
    uint32_t    info;
    uint64_t    addralign;
    uint64_t    entrysize;
} ELF_Section_Header_Data;

enum ELF_Class
{
    ELF_Class_None,
    ELF_Class_32,
    ELF_Class_64
};

enum ELF_Executable_Type
{
    ELF_Executable_Type_None,
    ELF_Executable_Type_Relocatable,
    ELF_Executable_Type_Executable,
    ELF_Executable_Type_Dynamic,
    ELF_Executable_Type_Core,
};

enum ELF_Machine_Type
{
    ELF_Machine_Type_None,
    ELF_Machine_Type_SPARC      = 0x02,
    ELF_Machine_Type_i386       = 0x03,
    ELF_Machine_Type_MIPS       = 0x08,
    ELF_Machine_Type_PowerPC    = 0x14,
    ELF_Machine_Type_ARM        = 0x28,
    ELF_Machine_Type_SUPERH     = 0x2a,
    ELF_Machine_Type_IA_64      = 0x32,
    ELF_Machine_Type_AMD64      = 0x3e,
    ELF_Machine_Type_AArch64    = 0xb7,
    ELF_Machine_Type_RISC_V     = 0xf3
};

enum ELF_Version
{
    ELF_Version_None,
    ELF_Version_Current
};

enum ELF_Data_Encoding
{
    ELF_Data_Encoding_None,
    ELF_Data_Encoding_Little,
    ELF_Data_Encoding_Big
};

enum ELF_ABI
{
    ELF_ABI_System_V            = 0,
    ELF_ABI_HP_UX               = 1,
    ELF_ABI_NetBSD              = 2,
    ELF_ABI_Linux               = 3,
    ELF_ABI_Hurd                = 4,
    ELF_ABI_Solaris             = 6,
    ELF_ABI_AIX                 = 7,
    ELF_ABI_IRIX                = 8,
    ELF_ABI_FreeBSD             = 9,
    ELF_ABI_Tru64               = 10,
    ELF_ABI_Novell_Modesto      = 11,
    ELF_ABI_OpenBSD             = 12,
    ELF_ABI_OpenVMS             = 13,
    ELF_ABI_NonStop             = 14,
    ELF_ABI_AROS                = 15,
    ELF_ABI_Fenix               = 16,
    ELF_ABI_CloudABI            = 17,
    ELF_ABI_OpenVOS             = 18
};

#define ELF_MAGIC "\x7f" "ELF"

enum ELF_Program_Header_Type {
    ELF_PH_Type_Null            = 0,
    ELF_PH_Type_Load            = 1,
    ELF_PH_Type_Dynamic         = 2,
    ELF_PH_Type_Interpreter     = 3,
    ELF_PH_Type_Note            = 4,
    ELF_PH_Type_Shared_Lib      = 5,
    ELF_PH_Type_PH_Table        = 6,
    ELF_PH_Type_Thread_Local    = 7,
    ELF_PH_Type_LOOS            = 0x60000000,
    ELF_PH_Type_HIOS            = 0x6FFFFFFF,
    ELF_PH_Type_LOPROC          = 0x70000000,
    ELF_PH_Type_HIPROC          = 0x7FFFFFFF
};

enum ELF_Section_Header_Type {
    ELF_SH_Type_Null            = 0,
    ELF_SH_Type_Program_Data    = 1,
    ELF_SH_Type_Symbol_Table    = 2,
    ELF_SH_Type_String_Table    = 3,
    ELF_SH_Type_Reloc_Table_WA  = 4,
    ELF_SH_Type_Hash_Table      = 5,
    ELF_SH_Type_Dyn_Link_Info   = 6,
    ELF_SH_Type_Notes           = 7,
    ELF_SH_Type_No_Bits         = 8,
    ELF_SH_Type_Reloc_Table_NA  = 9,
    ELF_SH_Type_Shared_Lib      = 10,
    ELF_SH_Type_Dyn_Symbol      = 11,
    ELF_SH_Type_Init_Array      = 14,
    ELF_SH_Type_Fini_Array      = 15,
    ELF_SH_Type_Preinit_Array   = 16,
    ELF_SH_Type_Group           = 17,
    ELF_SH_Type_Section_Idx     = 18,
    ELF_SH_Type_Def_Number      = 19,
    ELF_SH_Type_LOOS            = 0x60000000,
};

enum ELF_Section_Header_Flags {
    ELF_SH_Flags_Writable       = 0x1,
    ELF_SH_Flags_Allocated      = 0x2,
    ELF_SH_Flags_Exectuable     = 0x4,
    ELF_SH_Flags_Merged         = 0x10,
    ELF_SH_Flags_Strings        = 0x20,
    ELF_SH_Flags_Link_Info      = 0x40,
    ELF_SH_Flags_Link_Order     = 0x80,
    ELF_SH_Flags_OS_Specific    = 0x100,
    ELF_SH_Flags_Group          = 0x200,
    ELF_SH_Flags_TLS            = 0x400,
    ELF_SH_Flags_OS_Mask        = 0xFF000000,
    ELF_SH_Flags_Proc_Mask      = 0xF0000000
};


typedef struct ELF_Object {
    ELF_Header_Data header_data;

    ELF_Section_Header_Data section_headers[64];
    size_t section_header_count;

    ELF_Program_Header_Data program_headers[64];
    size_t program_header_count;

    char* buffer;
    size_t buffer_length;
} ELF_Object;

bool elf_create_object(char* buffer, size_t buffer_length, ELF_Object* object);

bool elf_get_program_headers(ELF_Object* object);

bool elf_get_section_headers(ELF_Object* object);

bool elf_copy_headers(char* start, size_t size, size_t expected_size, size_t count,
                      void* destination, size_t* dest_count);

bool elf_check_magic_header_contents(ELF_Object* object, size_t index);

size_t elf_find_magic_header_index(ELF_Object* object);

bool elf_load_object(ELF_Object* object);

// SWITCH TO LONG MODE BEFORE DOING THIS
_Noreturn void elf_jump_to_entry_point(ELF_Object* object);

#endif
