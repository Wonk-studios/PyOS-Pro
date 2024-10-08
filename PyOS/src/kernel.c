#include <stdint.h>
#include "display.h"
#include "bmp.h"

// Function to read a file from disk (placeholder, replace with actual implementation)
int read_file(const char* filename, uint8_t* buffer, uint32_t buffer_size);

void kernel_main() {
    display_init();
    display_clear();

    // Buffer to hold the BMP file data
    uint8_t bmp_buffer[1024 * 1024]; // 1 MB buffer, adjust size as needed

    // Read the BMP file from disk
    if (read_file("splash_screen.bmp", bmp_buffer, sizeof(bmp_buffer)) == 0) {
        display_bmp(bmp_buffer);
    } else {
        display_puts("Non fatal n1: Failed to load splash screen.\n");
    }

    // Load the interpreter entry
    extern void interpreter_entry();
    interpreter_entry();

    // Hang the system
    while (1) {
        __asm__ __volatile__("hlt");
    }
}