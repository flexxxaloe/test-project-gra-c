//
// Created by mihai on 14.01.2024.
//

#ifndef IMAGE_H
#define IMAGE_H

#include <stddef.h>

// Функция для чтения ширины и высоты PNG изображения
void read_png_dimensions(const char* filename, size_t* width, size_t* height);

#endif  // IMAGE_H

