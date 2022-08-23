// SPDX-License-Identifier: MIT

#include <Entry.h>
#include <LKI.h>
#include <stdbool.h>

void kOSMain(LKI* lki) {
    LogPrint(lki->log, "Welcome to the kOS kernel!\n");

    while (true) ;
}
