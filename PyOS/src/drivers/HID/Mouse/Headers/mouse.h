#indef MOUSE_H
#define MOUSE_H

#include <stdint.h>

void mouse_init();
void mouse_interrupt_handler();
void mouse_get_position(int* x, int* y);

#endif // MOUSE_H