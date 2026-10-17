#include <terminal.h>
#include <interupts.h>
#include <PIC.h>

void kernel_main(void) {

    __asm__ volatile ("cli");

    terminal_initialize();

    init_interupts();
    
    init_pic(32, 40);

    __asm__ volatile ("sti");

    for (;;) {
        __asm__ volatile ("hlt");
    }
}