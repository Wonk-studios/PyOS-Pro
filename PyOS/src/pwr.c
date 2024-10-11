#include "pwr.h"
#include "display.h"
#include <stdint.h>

// Function to shut down the kernel
void shutdown_kernel() {
    display_puts("Shutting down...\n");
    
    outw(0xB004, 0x2000);
    while (1) {
    display_puts("VHK12: ACPI FAILED! INITIATING FALLBACK\n);
        __asm__ __volatile__("hlt");
    }
}

// Function to restart the kernel
void restart_kernel() {
    display_puts("Restarting...\n");
    // Add architecture-specific restart code here
    while (1) {
        __asm__ __volatile__("hlt");
    }
}

// Function to put the kernel to sleep
void sleep_kernel() {
    display_puts("Sleeping...\n");
    outw(0x64, 0xFE);
        
    while (1) {
        display_puts("VHK006 ACPI FAILED!\n");
        __asm__ __volatile__("hlt");
    }
}

// Function to hibernate the kernel
void hibernate_kernel() {
    display_puts("VHK001: savestate.sys does not exist.\n");
    outw(0xB004, 0x2000);
    // Add architecture-specific hibernate code here
    while (1) {
        __asm__ __volatile__("hlt");
    }
}
