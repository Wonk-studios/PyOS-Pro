#include "mouse.h"
#include "display.h"
#include <stdint.h>
#include <stddef.h>

#define MOUSE_DATA_PORT 0x60
#define MOUSE_STATUS_PORT 0x64
#define MOUSE_COMMAND_PORT 0x64

static int mouse_x = 0;
static int mouse_y = 0;

static void mouse_wait(uint8_t type) {
    uint32_t timeout = 100000;
    if (type == 0) {
        while (timeout--) {
            if ((inb(MOUSE_STATUS_PORT) & 1) == 1) {
                return;
            }
        }
    } else {
        while (timeout--) {
            if ((inb(MOUSE_STATUS_PORT) & 2) == 0) {
                return;
            }
        }
    }
}

static void mouse_write(uint8_t data) {
    mouse_wait(1);
    outb(MOUSE_COMMAND_PORT, 0xD4);
    mouse_wait(1);
    outb(MOUSE_DATA_PORT, data);
}

static uint8_t mouse_read() {
    mouse_wait(0);
    return inb(MOUSE_DATA_PORT);
}

void mouse_init() {
    uint8_t status;

    // Enable the auxiliary mouse device
    mouse_wait(1);
    outb(MOUSE_COMMAND_PORT, 0xA8);

    // Enable the interrupts
    mouse_wait(1);
    outb(MOUSE_COMMAND_PORT, 0x20);
    mouse_wait(0);
    status = (inb(MOUSE_DATA_PORT) | 2);
    mouse_wait(1);
    outb(MOUSE_COMMAND_PORT, 0x60);
    mouse_wait(1);
    outb(MOUSE_DATA_PORT, status);

    // Use default settings
    mouse_write(0xF6);
    mouse_read();  // Acknowledge

    // Enable the mouse
    mouse_write(0xF4);
    mouse_read();  // Acknowledge

    // Register the mouse interrupt handler
    // This is architecture-specific and will depend on your interrupt handling setup
    // For example, on x86 you might use:
    // register_interrupt_handler(IRQ12, mouse_interrupt_handler);
}

void mouse_interrupt_handler() {
    static uint8_t mouse_cycle = 0;
    static int8_t mouse_byte[3];

    mouse_byte[mouse_cycle++] = mouse_read();

    if (mouse_cycle == 3) {
        mouse_cycle = 0;

        int8_t x_offset = mouse_byte[1];
        int8_t y_offset = mouse_byte[2];

        mouse_x += x_offset;
        mouse_y -= y_offset;

        // Ensure the mouse coordinates are within screen bounds
        if (mouse_x < 0) mouse_x = 0;
        if (mouse_y < 0) mouse_y = 0;
        if (mouse_x >= SCREEN_WIDTH) mouse_x = SCREEN_WIDTH - 1;
        if (mouse_y >= SCREEN_HEIGHT) mouse_y = SCREEN_HEIGHT - 1;

        // Display the mouse position (for debugging)
        display_puts("Mouse moved to: ");
        display_putc('0' + mouse_x / 10);
        display_putc('0' + mouse_x % 10);
        display_putc(',');
        display_putc('0' + mouse_y / 10);
        display_putc('0' + mouse_y % 10);
        display_putc('\n');
    }
}

void mouse_get_position(int* x, int* y) {
    if (x) *x = mouse_x;
    if (y) *y = mouse_y;
}