// SPDX-License-Identifier: MIT

#include <LoadKernel.h>

size_t ElfFindMagicHeaderIndex(ELF_Object* object) {
    for (int i = 0; i < object->section_header_count; i++) {
        if (i == object->header_data.section_header_names_index) {
            continue;
        }

        ELF_Section_Header_Data* section_header = &object->section_headers[i];

        size_t name_offset = object->section_headers[object->header_data.section_header_names_index].offset
            + section_header->name;

        if (name_offset >= object->buffer_length) {
            continue;
        }

        if (memcmp(".magic",object->buffer + name_offset, 7) != 0) {
            continue;
        }

        if (section_header->type != ELF_SH_Type_Program_Data) {
            continue;
        }

        // Found .magic section!
        return i;
    }

    return -1;
}

bool ElfCheckMagicHeaderContents(ELF_Object* object, size_t index) {
    if (index == -1) {
        return false;
    }

    ELF_Section_Header_Data* section_header = &object->section_headers[index];

    size_t magic_offset = section_header->offset;

    if (magic_offset >= object->buffer_length) {
        return false;
    }

    if (memcmp("kOS", object->buffer + magic_offset, 4) != 0) {
        return false;
    }

    return true;
}

bool ElfCopyHeaders(
        char* start, size_t size, size_t expected_size, size_t count,
        void* destination, size_t* dest_count
    )
{
    if (size != expected_size) {
        return false;
    }

    int i;

    for (i = 0; i < 64 && i < count; i++) {
        memcpy(
            &destination[i * size],
            &start[i * size],
            size
        );
    }

    if (i < count) {
        return false;
    }

    *dest_count = i;

    return true;
}

bool ElfGetProgramHeaders(ELF_Object* object) {
    return ElfCopyHeaders(
        &object->buffer[object->header_data.program_header_offset],
        object->header_data.program_header_entry_size,
        sizeof(ELF_Program_Header_Data),
        object->header_data.program_header_entry_count,
        object->program_headers,
        &object->program_header_count
    );
}

bool ElfGetSectionHeaders(ELF_Object* object) {
    return ElfCopyHeaders(
        &object->buffer[object->header_data.section_header_offset],
        object->header_data.section_header_entry_size,
        sizeof(ELF_Section_Header_Data),
        object->header_data.section_header_entry_count,
        object->section_headers,
        &object->section_header_count
    );
}

bool ElfCreateObject(char* buffer, size_t buffer_length, ELF_Object* object) {
    if (object == NULL || buffer == NULL || buffer_length < sizeof(ELF_Header_Data)) return false;

    memcpy(&object->header_data, buffer, sizeof(ELF_Header_Data));

    bool success = true;

    object->buffer = buffer;
    object->buffer_length = buffer_length;

    success &= (
        (memcmp(&object->header_data.magic, ELF_MAGIC, 4) == 0) &&
        object->header_data.machine == ELF_Machine_Type_AMD64 &&
        object->header_data.binary_class == ELF_Class_64 &&
        object->header_data.data_encoding == ELF_Data_Encoding_Little &&
        object->header_data.abi == ELF_ABI_System_V &&
        object->header_data.type == ELF_Executable_Type_Executable
    );

    if (success) {
        success &= ElfGetProgramHeaders(object);
        success &= ElfGetSectionHeaders(object);
    }

    return success;
}

bool ElfLoadObject(ELF_Object* object) {
    /*for (int i = 0; i < object->section_header_count; i++) {
        ELF_Section_Header_Data* section = &object->section_headers[i];

        if (section->type == ELF_SH_Type_No_Bits) {
            if (!section->size) continue;
            if (section->flags & ELF_SH_Flags_Allocated) {
                memset((void*) section->addr, 0, section->size);

                section->offset = (int)object->buffer - (int)section->addr;
            }
        }
    }*/

    // Start from 1 to skip the Null section
    for (int i = 1; i < object->program_header_count; i++) {
        ELF_Program_Header_Data* program = &object->program_headers[i];

        if (program->type == ELF_PH_Type_Load) {
            if (!program->mem_size) continue;
            if (program->flags & ELF_PH_Type_Load) {
                memcpy((void*) program->vaddr, object->buffer + program->offset, program->mem_size);
            }
        }
    }

    return true;
}
