#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ini.h"

#define CONFIG_FILE "config.ini"

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

void write_config(Config* config) {
    FILE* file = fopen(CONFIG_FILE, "w");
    if (file == NULL) {
        printf("Can't open '%s' for writing\n", CONFIG_FILE);
        exit(1);
    }

    fprintf(file, "[boot]\n");
    fprintf(file, "verbose_mode=%s\n", config->verbose_mode);
    fprintf(file, "timeout=%d\n", config->timeout);
    fprintf(file, "default_os=%s\n", config->default_os);
    fprintf(file, "splash_screen=%s\n", config->splash_screen);
    fprintf(file, "log_level=%s\n", config->log_level);

    fclose(file);
}

void print_menu() {
    printf("PyOS boot configuration menu\n");
    printf("1. Set verbose mode\n");
    printf("2. Set timeout\n");
    printf("3. Set default OS\n");
    printf("4. Set splash screen\n");
    printf("5. Set log level\n");
    printf("6. Save and exit\n");
    printf("Enter your choice: ");
}

void update_config(Config* config) {
    int choice;
    char input[50];

    while (1) {
        print_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter verbose mode (true/false): ");
                scanf("%s", input);
                strncpy(config->verbose_mode, input, sizeof(config->verbose_mode));
                break;
            case 2:
                printf("Enter timeout (seconds): ");
                scanf("%d", &config->timeout);
                break;
            case 3:
                printf("Enter default OS: ");
                scanf("%s", input);
                strncpy(config->default_os, input, sizeof(config->default_os));
                break;
            case 4:
                printf("Enter splash screen (true/false): ");
                scanf("%s", input);
                strncpy(config->splash_screen, input, sizeof(config->splash_screen));
                break;
            case 5:
                printf("Enter log level (info/debug/error): ");
                scanf("%s", input);
                strncpy(config->log_level, input, sizeof(config->log_level));
                break;
            case 6:
                write_config(config);
                printf("Configuration saved.\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

int main() {
    Config config;
    read_config(&config);
    update_config(&config);
    return 0;
}