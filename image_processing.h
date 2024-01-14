#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include <stdint.h>
#include <stddef.h>

void convert_to_grayscale(uint8_t* img, size_t width, size_t height, float a, float b, float c, uint8_t* grayscale_img);
void adjust_brightness_contrast(const uint8_t* grayscale_img, size_t width, size_t height, int16_t brightness, float contrast, uint8_t* result_img);

#endif // IMAGE_PROCESSING_H
