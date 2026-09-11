#include <stdint.h>
#include "interupts.h"
#include "terminal.h"
#include "idt_load.asm"
#include "default_interupt_handler.asm"

struct idt_entry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attributes;
    uint16_t offset_high;
} __attribute__((packed)); //stop compiler adding padding

struct idtr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));


static struct idt_entry idt[256];
static struct idtr idtr;
extern void idt_load(uint32_t idtr_adress);

static void idt_set_gate(uint8_t number, uint32_t handler) {
    idt[number].offset_low = (uint16_t)(handler & 0xFFFF);
    idt[number].selector = 0x08;
    idt[number].zero = 0;
    idt[number].type_attributes = 0x8E;
    idt[number].offset_high = (uint16_t)(handler >> 16 & 0xFFFF);
}

void init_interupts(void) {
    for (int i = 0; i < 256; i++) {
        idt_set_gate(i, (uint32_t)default_interupts_handler);
    }
    
    idtr.limit = sizeof(struct idt_entry) * 256 - 1;
    idtr.base = (uint32_t)&idt;
    idt_load((uint32_t)&idtr);
}