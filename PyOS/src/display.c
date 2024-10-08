#include "display.h"

#ifdef __x86_64__
#define VIDEO_MEMORY_ADDRESS 0xB8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define WHITE_ON_BLACK 0x0F

static uint16_t* video_memory = (uint16_t*)VIDEO_MEMORY_ADDRESS;
static int cursor_x = 0;
static int cursor_y = 0;

void display_init() {
    // Initialize the display (if needed)
}

void display_clear() {
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        video_memory[i] = (WHITE_ON_BLACK << 8) | ' ';
    }
    cursor_x = 0;
    cursor_y = 0;
}

void display_putc(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else {
        video_memory[cursor_y * SCREEN_WIDTH + cursor_x] = (WHITE_ON_BLACK << 8) | c;
        cursor_x++;
        if (cursor_x >= SCREEN_WIDTH) {
            cursor_x = 0;
            cursor_y++;
        }
    }

    if (cursor_y >= SCREEN_HEIGHT) {
        display_clear();
    }
}

void display_puts(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        display_putc(str[i]);
    }
}

void display_draw_pixel(int x, int y, uint32_t color) {
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
        return; // Out of bounds
    }
    video_memory[y * SCREEN_WIDTH + x] = (color & 0xFF00) | ' ';
}

#elif defined(__arm__) || defined(__aarch64__)
#define VIDEO_MEMORY_ADDRESS 0xA0000000  // Example address for ARM
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define WHITE_ON_BLACK 0x0F

static uint16_t* video_memory = (uint16_t*)VIDEO_MEMORY_ADDRESS;
static int cursor_x = 0;
static int cursor_y = 0;

void display_init() {
    // Initialize the display (if needed)
}

void display_clear() {
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        video_memory[i] = (WHITE_ON_BLACK << 8) | ' ';
    }
    cursor_x = 0;
    cursor_y = 0;
}

void display_putc(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else {
        video_memory[cursor_y * SCREEN_WIDTH + cursor_x] = (WHITE_ON_BLACK << 8) | c;
        cursor_x++;
        if (cursor_x >= SCREEN_WIDTH) {
            cursor_x = 0;
            cursor_y++;
        }
    }

    if (cursor_y >= SCREEN_HEIGHT) {
        display_clear();
    }
}

void display_puts(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        display_putc(str[i]);
    }
}

void display_draw_pixel(int x, int y, uint32_t color) {
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
        return; // Out of bounds
    }
    video_memory[y * SCREEN_WIDTH + x] = (color & 0xFF00) | ' ';
}

#else
#error "Fatal error VH001: The architecture is not supported. Manual reboot required. HLT"
#endif