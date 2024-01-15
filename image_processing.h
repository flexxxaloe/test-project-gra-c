#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include <stdint.h>
#include <stddef.h>
#include "image.h"
void convert_to_grayscale(Image* image, float a, float b, float c);
void adjust_brightness_contrast(const Image* grayscale_img, int16_t brightness, float contrast, Image* result_img);
void adjust_contrast(Image *image);
void simple_adjust_contrast(Image *image);
#endif // IMAGE_PROCESSING_H
