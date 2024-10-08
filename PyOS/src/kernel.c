#include <stdint.h>

#ifdef __x86_64__
#define VIDEO_MEMORY_ADDRESS 0xB8000
#elif defined(__arm__) || defined(__aarch64__)
#define VIDEO_MEMORY_ADDRESS 0x00000000  // Placeholder address for ARM
#else
#error "FATAL VH001! Illegal architecture, cannot boot. HLT."
#endif

void clear_screen() {
    uint16_t* video_memory = (uint16_t*)VIDEO_MEMORY_ADDRESS;
    for (int i = 0; i < 80 * 25; i++) {
        video_memory[i] = (0x0F << 8) | ' ';
    }
}

void print_message(const char* message) {
    uint16_t* video_memory = (uint16_t*)VIDEO_MEMORY_ADDRESS;
    for (int i = 0; message[i] != '\0'; i++) {
        video_memory[i] = (0x0F << 8) | message[i];
    }
}

void kernel_main() {
    clear_screen();
    print_message("Kernel Loaded in Secure Long Mode");

    // Load the interpreter entry
    extern void interpreter_entry();
    interpreter_entry();

    // Hang the system
    while (1) {
        __asm__ __volatile__("hlt");
    }
}