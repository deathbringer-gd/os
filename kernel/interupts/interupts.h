#ifndef INTERUPTS_H
#define INTERUPTS_H
#include <stdint.h>

void init_interupts(void);
extern void idt_load(uint32_t idtr_adress);
extern void default_interupt_handler(void);
static void idt_set_gate(uint8_t name, uint32_t handler);

#endif