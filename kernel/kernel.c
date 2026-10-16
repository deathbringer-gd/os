#include <terminal.h>
#include <interupts.h>
#include <PIC.h>

void kernel_main(void) {

    __asm__ volatile ("cli");

    terminal_initialize();
    terminal_write_string("Doors OS or smthing");
    terminal_write_string(".-----------.\n");
    terminal_write_string("|  _______  |\n");
    terminal_write_string("| |       | |\n");
    terminal_write_string("| |       | |\n");
    terminal_write_string("| |       | |\n");
    terminal_write_string("| |_______|o|\n");
    terminal_write_string("|           |\n");
    terminal_write_string("|           |\n");
    terminal_write_string("'-----------'\n");


    init_interupts();
    
    init_pic(32, 40);

    __asm__ volatile ("sti");

    for (;;) {
        __asm__ volatile ("hlt");
    }
}