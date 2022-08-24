#include <stdint.h>

typedef struct {
    uint16_t isrLow;
    uint16_t kernelCS;
    uint8_t reserved;
    uint8_t attributes;
    uint16_t isrHigh;
} __attribute__((packed)) IDTEntry;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) IDTR;

__attribute__((aligned(0x10)))
static IDTEntry IDTTable[256];

static IDTR idtr;
