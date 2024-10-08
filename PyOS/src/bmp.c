#include "bmp.h"
#include "display.h"

void display_bmp(const uint8_t* bmp_data) {
    BMPHeader* bmp_header = (BMPHeader*)bmp_data;
    DIBHeader* dib_header = (DIBHeader*)(bmp_data + sizeof(BMPHeader));

    if (bmp_header->bfType != 0x4D42) { // 'BM' in little-endian
        display_puts("Invalid BMP file\n");
        return;
    }

    int width = dib_header->biWidth;
    int height = dib_header->biHeight;
    int bit_count = dib_header->biBitCount;

    if (bit_count != 24) {
        display_puts("Unsupported BMP format (only 24-bit supported)\n");
        return;
    }

    const uint8_t* pixel_data = bmp_data + bmp_header->bfOffBits;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int pixel_index = (height - 1 - y) * width * 3 + x * 3;
            uint8_t blue = pixel_data[pixel_index];
            uint8_t green = pixel_data[pixel_index + 1];
            uint8_t red = pixel_data[pixel_index + 2];
            uint32_t color = (red << 16) | (green << 8) | blue;
            display_draw_pixel(x, y, color);
        }
    }
}