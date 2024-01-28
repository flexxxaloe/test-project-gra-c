#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include <stdint.h>
#include <stddef.h>
#include <emmintrin.h>
#include "image.h"
void convert_to_grayscale(Image* image, float a, float b, float c);
__m128 clampToUint8(__m128 sum, int16_t brigthness);
void simd_convert_to_grayscale(Image* image, float a, float b, float c);
void adjust_brightness_contrast(const Image* grayscale_img, int16_t brightness, float contrast, Image* result_img);
void adjust_contrast(Image *image);
void simple_adjust_contrast(Image *image);
void simd_adjust_contrast(Image *image);
void another_adjust_contrast(Image *image);
void another_simd_adjust_contrast(Image *image);
#endif // IMAGE_PROCESSING_H
