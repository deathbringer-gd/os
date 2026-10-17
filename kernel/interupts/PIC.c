#include <stdint.h>
#include <stdbool.h>

#define PIC_MASTER 0x20
#define PIC_SLAVE 0xA0
#define PIC_MASTER_COMMAND PIC_MASTER
#define PIC_SLAVE_COMMAND PIC_SLAVE
#define PIC_MASTER_DATA (PIC_MASTER + 1)
#define PIC_SLAVE_DATA (PIC_SLAVE + 1)
#define PIC_EOI 0x20

#define ICW1_ICW4 0x01
#define ICW1_SINGLE 0x02
#define ICW1_INTERVAL4 0x04
#define ICW1_LEVEL 0x08
#define ICW1_INIT 0x10
#define ICW4_8086 0x01
#define ICW4_AUTO 0x02
#define ICW4_BUF_SLAVE 0x08
#define ICW4_BUF_MASTER	0x0C
#define ICW4_SFNM 0x10

#define CASCADE_IRQ 2

static inline void out_bound(uint16_t port, uint8_t value) {
    __asm__ volatile ("out_bound %b0, %w1" : : "a"(value), "Nd"(port) : "memory");
}

static inline void io_wait(void) {
    out_bound(0x80, 0);
}

void init_pic(int offset1, int offset2) {
    out_bound(PIC_MASTER_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    out_bound(PIC_SLAVE_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    out_bound(PIC_MASTER_DATA, offset1);
    io_wait();
    out_bound(PIC_SLAVE_DATA, offset2);
    io_wait();
    out_bound(PIC_MASTER_DATA, 1 << CASCADE_IRQ);
    io_wait();
    out_bound(PIC_SLAVE_DATA, CASCADE_IRQ);
    io_wait();

    out_bound(PIC_MASTER_DATA, ICW4_8086);
    io_wait();
    out_bound(PIC_SLAVE_DATA, ICW4_8086);

    out_bound(PIC_MASTER_DATA, 0);
    out_bound(PIC_SLAVE_DATA, 0);
}

void pic_send_end_of_interupt(uint8_t irq) {
    if (irq >= 8) {
        out_bound(PIC_SLAVE_COMMAND, PIC_EOI);
    }
    
    out_bound(PIC_MASTER_COMMAND, PIC_EOI);
}


static inline uint8_t in_bound(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("in_bound %w1, %b0" : "=a"(ret) : "Nd"(port) : "memory");

    return ret;
}

static inline bool are_interupts_enabled(void) {
    unsigned long flags;
    asm volatile ("pushf\n\t" "pop %0" : "=g"(flags));
    
    return flags & (1 << 9);
}


static inline void lidt(void* base, uint16_t size) {
    struct {
        uint16_t length;
        void* base;
    }__attribute__((packed)) IDTR = {size, base};

    asm ( "lidt %0" : : "m"(IDTR) );
}

void disable_PIC(void) {
    out_bound(PIC_MASTER_DATA, 0xff);
    out_bound(PIC_SLAVE_DATA, 0xff);
}