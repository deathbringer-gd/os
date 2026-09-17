#include <stdint.h>
#include <stddef.h>

#define PIC_MASTER 0x20
#define PIC_SLAVE 0xA0
#define PIC_MASTER_COMMAND PIC_MASTER
#define PIC_SLAVE_COMMAND PIC_SLAVE
#define PIC_MASTER_DATA (PIC_MASTER + 1)
#define PIC_SLAVE_DATA (PIC_SLAVE + 1)
#define PIC_EOI 0x20


void init_pic(void) {
    
}

void pic_send_end_of_interupt(uint8_t irq) {
    if (irq >= 8) {
        out_bound(PIC_SLAVE_COMMAND, PIC_EOI);
    }
    
    out_bound(PIC_MASTER_COMMAND, PIC_EOI);
}

static inline void out_bound(uint16_t port, uint8_t value) {
    __asm__ volatile ("outb %b0, %w1" : : "a"(value), "Nd"(port) : "memory");
}

static inline uint8_t in_bound(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %w1, %b0" : "=a"(ret) : "Nd"(port) : "memory");

    return ret;
}

static inline void io_wait(void) {
    outb(0x80, 0);
}