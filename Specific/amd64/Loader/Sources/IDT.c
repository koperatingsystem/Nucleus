#include <LKI.h>

#define log_isr(isr) \
    void isr_##isr(void) { \
        LogPrint(0x0, "Interrupt called: " #isr "\n"); \
    }

#define noop_isr(isr) \
    void isr_##isr(void) { \
        return; \
    }

noop_isr(0)
noop_isr(1)
noop_isr(2)
noop_isr(3)
noop_isr(4)
noop_isr(5)
noop_isr(6)
noop_isr(7)
log_isr(8)
noop_isr(9)
log_isr(10)
log_isr(11)
log_isr(12)
log_isr(13)
log_isr(14)
noop_isr(15)
noop_isr(16)
log_isr(17)
noop_isr(18)
noop_isr(19)
noop_isr(20)
noop_isr(21)
noop_isr(22)
noop_isr(23)
noop_isr(24)
noop_isr(25)
noop_isr(26)
noop_isr(27)
noop_isr(28)
noop_isr(29)
log_isr(30)
noop_isr(31)
