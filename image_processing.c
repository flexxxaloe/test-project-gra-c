#include "image_processing.h"

void convert_to_grayscale(uint8_t* img, size_t width, size_t height, float a, float b, float c, uint8_t* grayscale_img) {
    // Реализация конвертации в градации серого
    size_t num_pixels = width * height;

    for (size_t i = 0; i < num_pixels; ++i) {
        size_t base_index = i * 3; // каждый пиксель имеет 3 компонента: R, G, B

        // Извлечение значений компонентов цвета
        uint8_t red = img[base_index];
        uint8_t green = img[base_index + 1];
        uint8_t blue = img[base_index + 2];

        // Вычисление взвешенного среднего для оттенка серого
        uint8_t grayscale_value = (uint8_t)((a * red + b * green + c * blue) / (a + b + c));

        // Запись значения в новое изображение в оттенках серого
        grayscale_img[i] = grayscale_value;
    }
}

void adjust_brightness_contrast(const uint8_t* grayscale_img, size_t width, size_t height, int16_t brightness, float contrast, uint8_t* result_img) {
    // Реализация корректировки яркости и контраста
    size_t num_pixels = width * height;

    for (size_t i = 0; i < num_pixels; ++i) {
        // Извлечение значения оттенка серого
        uint8_t grayscale_value = grayscale_img[i];

        // Корректировка яркости
        int16_t adjusted_brightness = (int16_t)grayscale_value + brightness;
        adjusted_brightness = (adjusted_brightness < 0) ? 0 : ((adjusted_brightness > 255) ? 255 : adjusted_brightness);

        // Корректировка контраста
        float adjusted_contrast = contrast * (adjusted_brightness - 128) + 128;
        adjusted_contrast = (adjusted_contrast < 0) ? 0 : ((adjusted_contrast > 255) ? 255 : adjusted_contrast);

        // Запись значения в новое изображение с корректировкой яркости и контраста
        result_img[i] = (uint8_t)adjusted_contrast;
    }
}
