#include "image_processing.h"
#include "image.h"
void convert_to_grayscale(Image* image, float a, float b, float c) {
    // Реализация конвертации в градации серого
    size_t num_pixels = image->width * image->height;

    for (size_t i = 0; i < num_pixels; ++i) {

        // Извлечение значений компонентов цвета
        unsigned char red = image->pixels->r;
        unsigned char green = image->pixels->g;
        unsigned char blue = image->pixels->b;

        // Вычисление взвешенного среднего для оттенка серого
        uint8_t grayscale_value = (uint8_t)((a * red + b * green + c * blue) / (a + b + c));

        // Запись значения в новое изображение в оттенках серого
        image->pixels[i].r = grayscale_value;
        image->pixels[i].g = grayscale_value;
        image->pixels[i].b = grayscale_value;
    }
}

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

