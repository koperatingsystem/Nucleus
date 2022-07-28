// SPDX-License-Identifier: MIT

#include <LoadKernel.h>

bool elf_create_object(char* buffer, size_t buffer_length, ELF_Object* object) {
    if (object == NULL || buffer == NULL || buffer_length < sizeof(ELF_Header_Data)) return false;

    memcpy(&object->header_data, buffer, sizeof(ELF_Header_Data));

    bool success = true;

    success &= (memcmp(&object->header_data.magic, ELF_MAGIC, 4) == 0);

    success &= object->header_data.machine == ELF_Machine_Type_AMD64;

    success &= object->header_data.binary_class == ELF_Class_64;

    success &= object->header_data.data_encoding == ELF_Data_Encoding_Little;

    success &= object->header_data.abi == ELF_ABI_System_V;

    success &= object->header_data.type == ELF_Executable_Type_Executable;

    return success;
}
