#pragma once

#ifndef LOADER_GDT_H
#define LOADER_GDT_H

struct GDTEntry {
    unsigned short limitLow;
    unsigned short baseLow;
    unsigned char baseMiddle;
    unsigned char access;
    unsigned char granularity;
    unsigned char baseHigh;
} __attribute__((packed));

struct GDTPointer {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

extern struct GDTEntry GDT[3];
extern struct GDTPointer pointerToGDT;

extern void GDTFlush();

void GDTInstall();

#endif
