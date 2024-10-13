#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include savestate.h


void log(const char* message) {
    printf("%s\n", message);
}

bool check_c_module() {
    // Check if the report file exists
    return access("/tmp/report.txt", F_OK) != -1;
}

void kernel(const char* cmd) {
    if (!check_c_module()) {
        printf("PyOS Module reported: INMO Non fatal: 1: Reporter output not found. Read *.txt for more info.\n");
        log("Error: INMO Non fatal: 1: Reporter output not found.");
    }

    if (strcmp(cmd, "shutdown") == 0) {
        shutdown_kernel();
    } else if (strcmp(cmd, "restart") == 0) {
        restart_kernel();
    } else if (strcmp(cmd, "sleep") == 0) {
        sleep_kernel();
    } else if (strcmp(cmd, "hibernate") == 0) {
        hibernate_kernel();
    } else {
        log("Error: Invalid command.");
    }
}

void shutdown_kernel() {
    log("Shutting down...");
	outw(0xB004, 0x2000);
	while (1){
		__asm__ __volatile__("hlt");
	}
	
}

void restart_kernel() {
    log("Restarting...");
	outw(0x64, 0xFE);
}

void sleep_kernel() {
    log("Sleeping...");
	outw(0x64, 0xFE);
}

void hibernate_kernel() {
    log("Hibernating...");
	call_save();
	outw(0xB004, 0x2000);
}

int main() {
    // Example usage
    kernel("shutdown");
    return 0;
}