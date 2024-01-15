#include "image_processing.h"
#include "image.h"
#include <math.h>

uint8_t clamp(int value, int min, int max) {
    if (value < min) {
        return min;
    } else if (value > max) {
        return max;
    } else {
        return (uint8_t)value;
    }
}

void convert_to_grayscale(Image* image, float a, float b, float c) {
    // Реализация конвертации в градации серого
    size_t num_pixels = image->width * image->height;

    for (size_t i = 0; i < num_pixels; ++i) {
        // Извлечение значений компонентов цвета текущего пикселя
        unsigned char red = image->pixels[i].r;
        unsigned char green = image->pixels[i].g;
        unsigned char blue = image->pixels[i].b;

        // Вычисление взвешенного среднего для оттенка серого
        uint8_t grayscale_value = (uint8_t)((a * red + b * green + c * blue) / (a + b + c));
        grayscale_value = clamp((int)image->brightness + grayscale_value, 0, 255);
        // Запись значения в текущий пиксель в оттенках серого
        image->pixels[i].r = grayscale_value;
        image->pixels[i].g = grayscale_value;
        image->pixels[i].b = grayscale_value;
    }
}
void adjust_contrast(Image *image) {
    float contrast = image->contrast;
    // Реализация коррекции контраста
    size_t num_pixels = image->width * image->height;

    // Вычисление среднего значения яркости
    float mean_brightness = 0.0f;
    for (size_t i = 0; i < num_pixels; ++i) {
        mean_brightness += (float)(image->pixels[i].r + image->pixels[i].g + image->pixels[i].b)/3;
    }
    mean_brightness /= (float)num_pixels;

    // Вычисление стандартного отклонения яркости
    float brightness_deviation = 0.0f;
    for (size_t i = 0; i < num_pixels; ++i) {
        brightness_deviation += powf((float)image->pixels[i].r - mean_brightness, 2);
    }
    brightness_deviation = sqrtf(brightness_deviation / (float)num_pixels);

    // Коррекция контраста
    for (size_t i = 0; i < num_pixels; ++i) {
        float adjusted_brightness;
        if(brightness_deviation == 0){
             adjusted_brightness = mean_brightness;
        } else {
            adjusted_brightness = (contrast / brightness_deviation) * (float)image->pixels[i].r +
                                        mean_brightness * (1 - (contrast / brightness_deviation));
        }
        image->pixels[i].r = clamp((int)adjusted_brightness, 0, 255);
        image->pixels[i].g = clamp((int)adjusted_brightness, 0, 255);
        image->pixels[i].b = clamp((int)adjusted_brightness, 0, 255);
    }
}

/*
void adjust_brightness_contrast(const Image* grayscale_img, int16_t brightness, float contrast, Image* result_img) {
    // Реализация корректировки яркости и контраста
    size_t num_pixels = grayscale_img->width * grayscale_img->height;

    for (size_t i = 0; i < num_pixels; ++i) {
        // Извлечение значения оттенка серого
        uint8_t grayscale_value = grayscale_img->pixels[i].r; // Предполагается, что изображение уже в оттенках серого

        // Корректировка яркости
        int16_t adjusted_brightness = (int16_t)grayscale_value + brightness;
        adjusted_brightness = (adjusted_brightness < 0) ? 0 : ((adjusted_brightness > 255) ? 255 : adjusted_brightness);

        // Корректировка контраста
        float adjusted_contrast = contrast * (adjusted_brightness - 128) + 128;
        adjusted_contrast = (adjusted_contrast < 0) ? 0 : ((adjusted_contrast > 255) ? 255 : adjusted_contrast);

        // Запись значения в новое изображение с корректировкой яркости и контраста
        result_img->pixels[i].r = (uint8_t)adjusted_contrast;
        result_img->pixels[i].g = (uint8_t)adjusted_contrast;
        result_img->pixels[i].b = (uint8_t)adjusted_contrast;
    }
}
 */
