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
    uint16_t    section_header_index;
} ELF_Header_Data;

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
    ELF_ABI_System_V        = 0,
    ELF_ABI_HP_UX           = 1,
    ELF_ABI_NetBSD          = 2,
    ELF_ABI_Linux           = 3,
    ELF_ABI_Hurd            = 4,
    ELF_ABI_Solaris         = 6,
    ELF_ABI_AIX             = 7,
    ELF_ABI_IRIX            = 8,
    ELF_ABI_FreeBSD         = 9,
    ELF_ABI_Tru64           = 10,
    ELF_ABI_Novell_Modesto  = 11,
    ELF_ABI_OpenBSD         = 12,
    ELF_ABI_OpenVMS         = 13,
    ELF_ABI_NonStop         = 14,
    ELF_ABI_AROS            = 15,
    ELF_ABI_Fenix           = 16,
    ELF_ABI_CloudABI        = 17,
    ELF_ABI_OpenVOS         = 18
};

#define ELF_MAGIC "\x7f" "ELF"

typedef struct ELF_Object {
    // Raw data

    ELF_Header_Data header_data;

    // Processed data

    // TODO: Add stuff
} ELF_Object;

bool elf_create_object(char* buffer, size_t buffer_length, ELF_Object* object);

#endif
