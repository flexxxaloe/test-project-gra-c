//
// Created by mihai on 14.01.2024.
//
#ifndef IMAGE_H
#define IMAGE_H

#include <stddef.h>
#include <stdint.h>
typedef struct {
    unsigned char r, g, b;
} Pixel;

typedef struct {
    int width, height;
    Pixel *pixels;
    int16_t brightness;
    int16_t contrast;
} Image;

void read_png_dimensions(const char* filename, size_t* width, size_t* height);


#endif // IMAGE_H

