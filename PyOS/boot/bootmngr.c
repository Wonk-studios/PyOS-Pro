#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ini.h"

#define CONFIG_FILE "config.ini"
#define X86_BOOTLOADER_ADDRESS 0x7C00
#define ARM_BOOTLOADER_ADDRESS 0x80000

typedef struct {
    char verbose_mode[6];
    int timeout;
    char default_os[50];
    char splash_screen[6];
    char log_level[10];
} Config;

static int handler(void* user, const char* section, const char* name, const char* value) {
    Config* pconfig = (Config*)user;

    if (strcmp(section, "boot") == 0) {
        if (strcmp(name, "verbose_mode") == 0) {
            strncpy(pconfig->verbose_mode, value, sizeof(pconfig->verbose_mode));
        } else if (strcmp(name, "timeout") == 0) {
            pconfig->timeout = atoi(value);
        } else if (strcmp(name, "default_os") == 0) {
            strncpy(pconfig->default_os, value, sizeof(pconfig->default_os));
        } else if (strcmp(name, "splash_screen") == 0) {
            strncpy(pconfig->splash_screen, value, sizeof(pconfig->splash_screen));
        } else if (strcmp(name, "log_level") == 0) {
            strncpy(pconfig->log_level, value, sizeof(pconfig->log_level));
        }
    }
    return 1;
}

void read_config(Config* config) {
    if (ini_parse(CONFIG_FILE, handler, config) < 0) {
        printf("Can't load '%s'\n", CONFIG_FILE);
        exit(1);
    }
}

void load_x86_bootloader(int verbose) {
    if (verbose) {
        printf("[bootmngr] [Process: transfer] x86 architecture detected! Loading x86 bootloader...\n");
    }
    // Jump to the x86 bootloader address
    void (*x86_bootloader)() = (void (*)())X86_BOOTLOADER_ADDRESS;
    x86_bootloader();
}

void load_arm_bootloader(int verbose) {
    if (verbose) {
        printf("[bootmngr] [Process: transfer] ARM architecture detected! Loading ARM bootloader...\n");
    }
    // Jump to the ARM bootloader address
    void (*arm_bootloader)() = (void (*)())ARM_BOOTLOADER_ADDRESS;
    arm_bootloader();
}

void detect_and_load_bootloader(int verbose) {
#ifdef ARCH_X86
    load_x86_bootloader(verbose);
#elif defined(ARCH_ARM)
    load_arm_bootloader(verbose);
#else
    printf("FATAL VH001! Illegal architecture, cannot boot. HLT.\n");
    exit(1);
#endif
}

int main() {
    Config config;
    read_config(&config);

    int verbose = (strcmp(config.verbose_mode, "true") == 0);

    detect_and_load_bootloader(verbose);

    return 0;
}