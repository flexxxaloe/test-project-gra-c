#include <stdio.h>
#include "stdlib.h"


// from https://ru.stackoverflow.com/questions/566475/%D0%92%D1%8B%D1%87%D0%B8%D1%81%D0%BB%D0%B5%D0%BD%D0%B8%D0%B5-%D0%BA%D0%B2%D0%B0%D0%B4%D1%80%D0%B0%D1%82%D0%BD%D0%BE%D0%B3%D0%BE-%D0%BA%D0%BE%D1%80%D0%BD%D1%8F-%D0%B1%D0%B5%D0%B7-%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D1%87%D0%BD%D1%8B%D1%85-%D0%BC%D0%B5%D1%82%D0%BE%D0%B4%D0%BE%D0%B2
//from https://en.wikipedia.org/wiki/Fast_inverse_square_root
float sqrtfunc(float number) {
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y  = number;
    i  = * ( long * ) &y;
    i  = 0x5f3759df - ( i >> 1 );
    y  = * ( float * ) &i;
    y  = y * ( threehalfs - ( x2 * y * y ) );   // 1 итерация
//  y  = y * ( threehalfs - ( x2 * y * y ) );   // 2 итерация, можно удалить
    return 1/y;
}

float power(float base, int exponent) {
    if (exponent < 0) {
        fprintf(stderr, "Exponent should be non-negative for this example.\n");
        return -1.0f; // Вернем значение -1 для обозначения ошибки
    }

    float result = 1.0f;

    for (int i = 0; i < exponent; i++) {
        result *= base;
    }

    return result;
}