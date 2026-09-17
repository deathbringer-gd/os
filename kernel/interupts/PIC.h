#ifndef PIC_H
#define PIC_H

#include <stdint.h>
#include <stddef.h>

void init_pic(void);
static void inline out_bound(uint16_t port, uint8_t value);
static inline uint8_t in_bound(uint16_t port);
static inline void io_wait(void);
void pic_send_end_of_interupt(uint8_t irq);

#endif