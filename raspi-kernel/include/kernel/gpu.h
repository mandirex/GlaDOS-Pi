#include <kernel/peripheral.h>
#include <stdint.h>
#ifndef GPU_H
#define GPU_H

#define CHAR_WIDTH 8
#define CHAR_HEIGHT 8

typedef struct pixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} pixel_t;


static struct pixel FORE = {0xff, 0xff, 0xff};
static struct pixel BACK = {0x00, 0x00, 0x00};

void gpu_init(void);

void write_pixel(uint32_t x, uint32_t y, const pixel_t * pixel);

void gpu_putc(char c);

void gpu_setforeground(int r, int g, int b);

void gpu_cls();

void gpu_setcursor(uint32_t x, uint32_t y);

void gpu_movecursor(uint32_t x, uint32_t y);

void newline();

#endif
