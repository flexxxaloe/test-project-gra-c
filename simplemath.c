#include <stdio.h>
#include "stdlib.h"


// from https://ru.stackoverflow.com/questions/566475/%D0%92%D1%8B%D1%87%D0%B8%D1%81%D0%BB%D0%B5%D0%BD%D0%B8%D0%B5-%D0%BA%D0%B2%D0%B0%D0%B4%D1%80%D0%B0%D1%82%D0%BD%D0%BE%D0%B3%D0%BE-%D0%BA%D0%BE%D1%80%D0%BD%D1%8F-%D0%B1%D0%B5%D0%B7-%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D1%87%D0%BD%D1%8B%D1%85-%D0%BC%D0%B5%D1%82%D0%BE%D0%B4%D0%BE%D0%B2
float sqrtfunc(float n) {
    float l = 0;
    float r = 1e30;  // Большое число для float
    float m;

    while (r - l > 1e-4) {  // Точность для float
        m = l + (r - l) / 2;
        if (m * m > n)
            l = m;
        else
            r = m;
    }
    return m;
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