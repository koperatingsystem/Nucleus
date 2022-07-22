// SPDX-License-Identifier: MIT


#include <ELF.h>

#include <string.h>

ELF_Result ELF_Read_Header(ELF_Header* header, uint8_t* buffer, size_t length)
{
    if (header == NULL || buffer == NULL || length < sizeof(ELF_Header_64)) return ELF_Result_Invalid_Arguments;

    ELF_Header internal_header;

    switch (buffer[4])
    {
    case ELF_Class_32:
    {
        internal_header.class = ELF_Class_32;
        ELF_Header_32 header32;
        memcpy(&header32, buffer, sizeof(ELF_Header_32));
        internal_header.header_data.Header_32 = header32;
        break;
    }

    case ELF_Class_64:
    {
        internal_header.class = ELF_Class_64;
        ELF_Header_64 header64;
        memcpy(&header64, buffer, sizeof(ELF_Header_64));
        internal_header.header_data.Header_64 = header64;
        break;
    }

    default:
        return ELF_Result_Invalid_Data;
    }

    memcpy(header, &internal_header, sizeof(ELF_Header));
    return ELF_Result_Success;
}
