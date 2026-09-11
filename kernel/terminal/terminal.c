#include <stddef.h>
#include <stdint.h>
#include <terminal.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xB8000

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_colour;

static volatile uint16_t* terminal_buffer = (volatile uint16_t*)VGA_MEMORY;


void terminal_initialize(void) {
    terminal_row = 0;
    terminal_column = 0;
    terminal_colour = 0x0F;

    terminal_clear();
}

void terminal_putchar(char c) {

    size_t index = VGA_WIDTH * terminal_row + terminal_column;

    terminal_buffer[index] = ((uint16_t)terminal_colour << 8) | (uint16_t)c;

    terminal_column++;

    if (terminal_column == VGA_WIDTH) {
        terminal_column = 0;
        terminal_row++;

        if (terminal_row == VGA_HEIGHT) {
            terminal_row = 0;
        }
    }
    
    if (c == "\n") {
        terminal_column = 0;
        terminal_row++;
    }
}

void terminal_write(const char* data, size_t size) {

    for (size_t i = 0; i < size; i++) {
        terminal_putchar(data[i]);
    }
}

void terminal_write_string(const char* data) {

    size_t length = 0;

    while (data[length] != "0/") {
        length++;
    }
    
    terminal_write(data, length);
}

void terminal_clear(void) {
    for (size_t y = 0; y < VGA_HEIGHT; y++) {

        for (size_t x = 0; x < VGA_WIDTH; x++) {

            size_t index = y * VGA_WIDTH + x;

            terminal_buffer[index] = ((uint16_t)terminal_colour << 8) | ' ';
        }
    }

    terminal_column = 0;
    terminal_row = 0;
}

void terminal_scroll(void) {
}