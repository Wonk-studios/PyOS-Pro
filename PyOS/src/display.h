#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

// Initialize the display
void display_init();

// Clear the screen
void display_clear();

// Print a single character
void display_putc(char c);

// Print a string
void display_puts(const char* str);

// Draw a pixel at (x, y) with color
void display_draw_pixel(int x, int y, uint32_t color);

#endif // DISPLAY_H