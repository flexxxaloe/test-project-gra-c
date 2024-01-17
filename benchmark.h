//
// Created by mihai on 17.01.2024.
//

#ifndef UNTITLED2_BENCHMARK_H
#define UNTITLED2_BENCHMARK_H
#include <stdio.h>
#include "image_processing.h"
#include "image.h"
#include <time.h>
void benchmarking(int benchmark_repetitions, Image* image, float a, float b, float c, int version);
void test_alg(Image* image, float a, float b, float c, int version);
#endif //UNTITLED2_BENCHMARK_H
