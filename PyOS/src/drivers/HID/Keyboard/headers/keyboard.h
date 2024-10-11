#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

// Initialize the keyboard driver
void keyboard_init();

// Keyboard interrupt handler
void keyboard_interrupt_handler();

// Read a character from the keyboard buffer
char keyboard_read_char();

#endif // KEYBOARD_H