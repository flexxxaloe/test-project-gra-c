#include "image_processing.h"
#include "image.h"
#include <math.h>
#include <stdio.h>
#include "simplemath.h"
#include <emmintrin.h>
#include <tmmintrin.h>
#include <immintrin.h>

unsigned char clamp(int value, int min, int max) {
    if (value < min) {
        return min;
    } else if (value > max) {
        return max;
    } else {
        return (uint8_t)value;
    }
}

__m128 clampToUint8(__m128 sum, int16_t brightness) {
    // Создаем векторы с минимальным и максимальным значениями
    __m128 scaledSum = _mm_add_ps(sum, _mm_set1_ps((float)brightness));

    // Ограничиваем значения в пределах от 0 до 255
    __m128 clampedSum = _mm_min_ps(_mm_max_ps(scaledSum, _mm_setzero_ps()), _mm_set1_ps(255.0f));

    return clampedSum;
}
void simd_convert_to_grayscale(Image* image, float a, float b, float c) {
    size_t num_pixels = image->width * image->height;

    __m128 coeffa = _mm_set_ps(a, a, a, a);
    __m128 coeffb = _mm_set_ps(b, b, b, b);
    __m128 coeffc = _mm_set_ps(c, c, c, c);
    size_t i;
    for ( i = 0; i < num_pixels - (num_pixels % 4); i += 4) {

        //  4 pixels RGB to SIMD reg
        __m128 pixels_rf = _mm_set_ps(
                image->pixels[i + 3].r,  image->pixels[i+2].r,
               image->pixels[i + 1].r, image->pixels[i].r
        );
        __m128 pixels_gf = _mm_set_ps(
                image->pixels[i + 3].g,  image->pixels[i+ 2].g,
                 image->pixels[i + 1].g, image->pixels[i].g
        );
        __m128 pixels_bf = _mm_set_ps(
                 image->pixels[i + 3].b, image->pixels[i + 2].b,
                image->pixels[i + 1].b,  image->pixels[i].b
        );

        // convert to  float

        // Умножение каждой компоненты цвета на соответствующий коэффициент | mul every component (r g b) with coeff (a b c)
        pixels_rf = _mm_mul_ps(pixels_rf, coeffa);
        pixels_gf = _mm_mul_ps(pixels_gf, coeffb);
        pixels_bf = _mm_mul_ps(pixels_bf, coeffc);

        // Сложение взвешенных компонент | add to get sum
        __m128 sum = _mm_add_ps(_mm_add_ps(pixels_rf, pixels_gf), pixels_bf);

        // Деление на сумму коэффициентов | div -> get (gray value)
        sum = _mm_div_ps(sum, _mm_set_ps1(a + b + c));

        // clamp
     // sum = _mm_min_ps(sum, _mm_set_ps1(255.0f));
        sum = clampToUint8(sum, image->brightness);

        image->pixels[i].r = image->pixels[i].g =  image->pixels[i].b = (uint8_t)_mm_cvtss_f32(_mm_shuffle_ps(sum, sum, _MM_SHUFFLE(0, 0, 0, 0)));
        image->pixels[i + 1].r =image->pixels[i + 1].g = image->pixels[i + 1].b = (uint8_t)_mm_cvtss_f32(_mm_shuffle_ps(sum, sum, _MM_SHUFFLE(1, 1, 1, 1)));
        image->pixels[i + 2].r =image->pixels[i + 2].g = image->pixels[i + 2].b = (uint8_t)_mm_cvtss_f32(_mm_shuffle_ps(sum, sum, _MM_SHUFFLE(2, 2, 2, 2)));
        image->pixels[i + 3].r =image->pixels[i + 3].g = image->pixels[i + 3].b = (uint8_t)_mm_cvtss_f32(_mm_shuffle_ps(sum, sum, _MM_SHUFFLE(3, 3, 3, 3)));


    }
    for (; i < num_pixels; ++i) {
        // Convert RGB to grayscale for the remaining pixels
        unsigned char gray = (unsigned char)((a * image->pixels[i].r + b * image->pixels[i].g + c * image->pixels[i].b) / (a + b + c));
        image->pixels[i].r = gray;
        image->pixels[i].g = gray;
        image->pixels[i].b = gray;
    }
}


void convert_to_grayscale(Image* image, float a, float b, float c) {
    // Реализация конвертации в градации серого | convert to gray
    size_t num_pixels = image->width * image->height;

    for (size_t i = 0; i < num_pixels; ++i) {

        unsigned char red = image->pixels[i].r;
        unsigned char green = image->pixels[i].g;
        unsigned char blue = image->pixels[i].b;

        // gray value
        unsigned char grayscale_value = (unsigned char)((a * red + b * green + c * blue) / (a + b + c));
        grayscale_value = clamp((int)image->brightness + grayscale_value, 0, 255);

        image->pixels[i].r = grayscale_value;
        image->pixels[i].g = grayscale_value;
        image->pixels[i].b = grayscale_value;
    }
}

void adjust_contrast(Image *image) {
    float contrast = image->contrast;
    // picture size
    size_t num_pixels = image->width * image->height;

    //mean_brightness -> мю или как оно там называется
    float mean_brightness = 0.0f;
    for (size_t i = 0; i < num_pixels; ++i) {
        mean_brightness += (float)(image->pixels[i].r + image->pixels[i].g + image->pixels[i].b)/3;
    }
    mean_brightness /= (float)num_pixels;



    float brightness_deviation = 0.0f;
    for (size_t i = 0; i < num_pixels; ++i) {
        brightness_deviation += powf((float)image->pixels[i].r - mean_brightness, 2);
    }


    brightness_deviation = sqrtf(brightness_deviation / (float)num_pixels);



    for (size_t i = 0; i < num_pixels; ++i) {
        float adjusted_brightness;
        if(brightness_deviation == 0 || contrast == 0){
             adjusted_brightness = (float)image->pixels[i].r;
        } else {
            adjusted_brightness = (contrast / brightness_deviation) * (float)image->pixels[i].r +
                                        mean_brightness * (1 - (contrast / brightness_deviation));
        }

        image->pixels[i].r = clamp((int)adjusted_brightness, 0, 255);
        image->pixels[i].g = clamp((int)adjusted_brightness, 0, 255);
        image->pixels[i].b = clamp((int)adjusted_brightness, 0, 255);
    }
}
void simple_adjust_contrast(Image *image) {
    float contrast = image->contrast;

    size_t num_pixels = image->width * image->height;


    float mean_brightness = 0.0f;
    for (size_t i = 0; i < num_pixels; ++i) {
        mean_brightness += (float)(image->pixels[i].r + image->pixels[i].g + image->pixels[i].b)/3;
    }
    mean_brightness /= (float)num_pixels;


    float brightness_deviation = 0.0f;
    for (size_t i = 0; i < num_pixels; ++i) {
        brightness_deviation += power((float)image->pixels[i].r - mean_brightness, 2);
    }
    brightness_deviation = sqrtfunc(brightness_deviation / (float)num_pixels);



    for (size_t i = 0; i < num_pixels; ++i) {
        float adjusted_brightness;
        if(brightness_deviation == 0|| contrast == 0){
            adjusted_brightness = (float)image->pixels[i].r;
        } else {
            adjusted_brightness = (contrast / brightness_deviation) * (float)image->pixels[i].r +
                                  mean_brightness * (1 - (contrast / brightness_deviation));
        }
        image->pixels[i].r = clamp((int)adjusted_brightness, 0, 255);
        image->pixels[i].g = clamp((int)adjusted_brightness, 0, 255);
        image->pixels[i].b = clamp((int)adjusted_brightness, 0, 255);
    }
}

void simd_adjust_contrast(Image *image) {
    float contrast = image->contrast;
    size_t num_pixels = image->width * image->height;


    __m128 sum = _mm_setzero_ps();
    size_t i;
    __m128 red;
    __m128 green;
    __m128 blue;
    for (i = 0; i < num_pixels - (num_pixels % 4); i += 4) {
         red = _mm_set_ps(
                image->pixels[i + 3].r,  image->pixels[i + 2].r,
                image->pixels[i + 1].r, image->pixels[i].r
        );
         green = _mm_set_ps(
                image->pixels[i + 3].g,  image->pixels[i + 2].g,
                image->pixels[i + 1].g, image->pixels[i].g
        );
         blue = _mm_set_ps(
                image->pixels[i + 3].b, image->pixels[i + 2].b,
                image->pixels[i + 1].b,  image->pixels[i].b
        );
        sum =  _mm_add_ps(sum,_mm_div_ps(_mm_add_ps(_mm_add_ps(red, green), blue), _mm_set1_ps(3.0f)));
    }
    float mean_brightness = _mm_cvtss_f32(_mm_hadd_ps(_mm_hadd_ps(sum, sum), sum));

    for (; i < num_pixels; ++i) {
        mean_brightness += (float)(image->pixels[i].r + image->pixels[i].g + image->pixels[i].b)/3;
    }
    mean_brightness /= (float)num_pixels;



    float brightness_deviation = 0.0f;
    for (size_t a = 0; a < num_pixels; ++a) {
        brightness_deviation += powf((float)image->pixels[a].r - mean_brightness, 2);
    }
    brightness_deviation = sqrtf(brightness_deviation / (float)num_pixels);
    // """""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""



    size_t a;
    for (a = 0; a < num_pixels - (num_pixels % 4); a += 4) {


        __m128 pixel_values = _mm_set_ps(
                image->pixels[a + 3].r, image->pixels[a + 2].r, image->pixels[a + 1].r, image->pixels[a].r
        );

        __m128 adjusted_brightness = pixel_values;

        if (brightness_deviation == 0 || contrast == 0) {
            // Если нет коррекции, оставляем значения как есть | nothing
        } else {
            //check other version if doesn`t understand | если ниче непонятно тут тоже самое что и в версии выше
            adjusted_brightness = _mm_add_ps(
                    _mm_mul_ps(_mm_div_ps(_mm_set1_ps(contrast), _mm_set1_ps(brightness_deviation)), adjusted_brightness),
                    _mm_mul_ps(_mm_set1_ps(mean_brightness), _mm_sub_ps(_mm_set1_ps(1.0f), _mm_div_ps(_mm_set1_ps(contrast), _mm_set1_ps(brightness_deviation))))
            );
        }

        adjusted_brightness = _mm_max_ps(_mm_min_ps(adjusted_brightness, _mm_set1_ps(255.0f)), _mm_set1_ps(0.0f));
        //shift to get appropriate value
        image->pixels[a].r = image->pixels[a].g =  image->pixels[a].b = (uint8_t)_mm_cvtss_f32(_mm_shuffle_ps(adjusted_brightness, adjusted_brightness, _MM_SHUFFLE(0, 0, 0, 0)));
        image->pixels[a + 1].r =image->pixels[a + 1].g = image->pixels[a + 1].b = (uint8_t)_mm_cvtss_f32(_mm_shuffle_ps(adjusted_brightness, adjusted_brightness, _MM_SHUFFLE(1, 1, 1, 1)));
        image->pixels[a + 2].r =image->pixels[a + 2].g = image->pixels[a + 2].b = (uint8_t)_mm_cvtss_f32(_mm_shuffle_ps(adjusted_brightness, adjusted_brightness, _MM_SHUFFLE(2, 2, 2, 2)));
        image->pixels[a + 3].r =image->pixels[a + 3].g = image->pixels[a + 3].b = (uint8_t)_mm_cvtss_f32(_mm_shuffle_ps(adjusted_brightness, adjusted_brightness, _MM_SHUFFLE(3, 3, 3, 3)));

    }
    for (; a < num_pixels; ++a) {

        float adjusted_brightness;
        if(brightness_deviation == 0|| contrast == 0){
            adjusted_brightness = (float)image->pixels[a].r;
        } else {
            adjusted_brightness = (contrast / brightness_deviation) * (float)image->pixels[a].r +
                                  mean_brightness * (1 - (contrast / brightness_deviation));
        }

        image->pixels[a].r = clamp((int)adjusted_brightness, 0, 255);
        image->pixels[a].g = clamp((int)adjusted_brightness, 0, 255);
        image->pixels[a].b = clamp((int)adjusted_brightness, 0, 255);
    }
}
void another_adjust_contrast(Image *image) {
    float contrast = image->contrast;

    size_t num_pixels = image->width * image->height;


    float mean_brightness = 0.0f;
    for (size_t i = 0; i < num_pixels; ++i) {
        mean_brightness += (float)(image->pixels[i].r + image->pixels[i].g + image->pixels[i].b)/3;
    }
    mean_brightness /= (float)num_pixels;


    for (size_t i = 0; i < num_pixels; ++i) {
        float adjusted_brightness;
        if((1 + contrast * (image->pixels[i].r - mean_brightness) == 0)){
            adjusted_brightness = 0;
        } else {
            adjusted_brightness = image->pixels[i].r/(1 + contrast * (image->pixels[i].r - mean_brightness));
        }
        image->pixels[i].r = clamp((int)adjusted_brightness, 0, 255);
        image->pixels[i].g = clamp((int)adjusted_brightness, 0, 255);
        image->pixels[i].b = clamp((int)adjusted_brightness, 0, 255);
    }
}
void another_simd_adjust_contrast(Image *image) {
    float contrast = image->contrast;
    size_t num_pixels = image->width * image->height;


    __m128 sum = _mm_setzero_ps();
    size_t i;
    __m128 red;
    __m128 green;
    __m128 blue;
    for (i = 0; i < num_pixels - (num_pixels % 4); i += 4) {
        red = _mm_set_ps(
                image->pixels[i + 3].r,  image->pixels[i + 2].r,
                image->pixels[i + 1].r, image->pixels[i].r
        );
        green = _mm_set_ps(
                image->pixels[i + 3].g,  image->pixels[i + 2].g,
                image->pixels[i + 1].g, image->pixels[i].g
        );
        blue = _mm_set_ps(
                image->pixels[i + 3].b, image->pixels[i + 2].b,
                image->pixels[i + 1].b,  image->pixels[i].b
        );
        sum =  _mm_add_ps(sum,_mm_div_ps(_mm_add_ps(_mm_add_ps(red, green), blue), _mm_set1_ps(3.0f)));
    }
    float mean_brightness = _mm_cvtss_f32(_mm_hadd_ps(_mm_hadd_ps(sum, sum), sum));

    for (; i < num_pixels; ++i) {
        mean_brightness += (float)(image->pixels[i].r + image->pixels[i].g + image->pixels[i].b)/3;
    }
    mean_brightness /= (float)num_pixels;



    size_t a;
    for (a = 0; a < num_pixels - (num_pixels % 4); a += 4) {


        __m128 pixel_values = _mm_set_ps(
                image->pixels[a + 3].r, image->pixels[a + 2].r, image->pixels[a + 1].r, image->pixels[a].r
        );

        __m128 adjusted_brightness = pixel_values;


        adjusted_brightness = _mm_div_ps(adjusted_brightness,_mm_add_ps(_mm_set1_ps(1.0f),_mm_mul_ps(_mm_set1_ps(contrast),_mm_sub_ps(adjusted_brightness, _mm_set1_ps(mean_brightness)))));


        adjusted_brightness = _mm_max_ps(_mm_min_ps(adjusted_brightness, _mm_set1_ps(255.0f)), _mm_set1_ps(0.0f));
        //shift to get appropriate value
        image->pixels[a].r = image->pixels[a].g =  image->pixels[a].b = (uint8_t)_mm_cvtss_f32(_mm_shuffle_ps(adjusted_brightness, adjusted_brightness, _MM_SHUFFLE(0, 0, 0, 0)));
        image->pixels[a + 1].r =image->pixels[a + 1].g = image->pixels[a + 1].b = (uint8_t)_mm_cvtss_f32(_mm_shuffle_ps(adjusted_brightness, adjusted_brightness, _MM_SHUFFLE(1, 1, 1, 1)));
        image->pixels[a + 2].r =image->pixels[a + 2].g = image->pixels[a + 2].b = (uint8_t)_mm_cvtss_f32(_mm_shuffle_ps(adjusted_brightness, adjusted_brightness, _MM_SHUFFLE(2, 2, 2, 2)));
        image->pixels[a + 3].r =image->pixels[a + 3].g = image->pixels[a + 3].b = (uint8_t)_mm_cvtss_f32(_mm_shuffle_ps(adjusted_brightness, adjusted_brightness, _MM_SHUFFLE(3, 3, 3, 3)));

    }
    for (; a < num_pixels; ++a) {

        float adjusted_brightness;
        if((1 + contrast * (image->pixels[i].r - mean_brightness) == 0)){
            adjusted_brightness = 0;
        } else {
            adjusted_brightness = image->pixels[i].r/(1 + contrast * (image->pixels[i].r - mean_brightness));
        }

        image->pixels[a].r = clamp((int)adjusted_brightness, 0, 255);
        image->pixels[a].g = clamp((int)adjusted_brightness, 0, 255);
        image->pixels[a].b = clamp((int)adjusted_brightness, 0, 255);
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