#include <stdint.h>
#include "display.h"
#include "bmp.h"
#include "keyboard.h"
#include "mouse.h"
#include "pwr.h"

// Function to read a file from disk (placeholder, replace with actual implementation)
int read_file(const char* filename, uint8_t* buffer, uint32_t buffer_size);

void kernel_main() {
    display_init();
    display_clear();

    // Initialize the keyboard and mouse drivers
    keyboard_init();
    mouse_init();

    // Buffer to hold the BMP file data
    uint8_t bmp_buffer[1024 * 1024]; // 1 MB buffer, adjust size as needed

    // Read the BMP file from disk
    if (read_file("splash_screen.bmp", bmp_buffer, sizeof(bmp_buffer)) == 0) {
        display_bmp(bmp_buffer);
    } else {
        display_puts("Failed to load splash screen\n");
    }

    // Load the interpreter entry
    extern void interpreter_entry();
    interpreter_entry();

    // Main loop
    while (1) {
        char c = keyboard_read_char();
        if (c) {
            display_putc(c); // Display the character on the screen
        }

        int mouse_x, mouse_y;
        mouse_get_position(&mouse_x, &mouse_y);
        // Optionally, display the mouse position or handle mouse events

        __asm__ __volatile__("hlt");
    }
}