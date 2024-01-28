//
// Created by mihai on 17.01.2024.
//

#include "benchmark.h"

void benchmarking(int benchmark_repetitions, Image* image, float a, float b, float c, int version) {
    printf("Benchmarking with %d repetitions\n", benchmark_repetitions);

    // check time
    clock_t start_time = clock();
    for (int i = 0; i < benchmark_repetitions; ++i) {
        if(version == 1){
            convert_to_grayscale(image, a, b, c);
            simple_adjust_contrast(image);
        }else if(version == 2){
            simd_convert_to_grayscale(image, a, b, c);
            simd_adjust_contrast(image);

        }else if(version == 3) {
            convert_to_grayscale(image, a, b, c);
            another_adjust_contrast(image);
        } else if(version == 4) {
            convert_to_grayscale(image, a, b, c);
            another_simd_adjust_contrast(image);
        }
        else {
            convert_to_grayscale(image, a, b, c);
            adjust_contrast(image);
        }
    }
    clock_t end_time = clock();


    double execution_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Total execution time: %f seconds\n", execution_time);
}
void test_alg(Image* image, float a, float b, float c, int version) {

    int values[] = {1, 10, 20, 30, 50, 75, 100};
    //int values[] = {1, 10, 50, 100, 150, 200, 250};
    size_t length = sizeof(values) / sizeof(values[0]);
    int versions = 3;
    for(int r = 0; r < versions; r++) {
        version = r;
        for (size_t v = 0; v < length; v++) {
            printf("Benchmarking with %d repetitions\n", values[v]);
            // check time
            clock_t start_time = clock();
            for (int i = 0; i < values[v]; ++i) {
                if (version == 1) {
                    convert_to_grayscale(image, a, b, c);
                    simple_adjust_contrast(image);
                } else if (version == 2) {
                    simd_convert_to_grayscale(image, a, b, c);
                    simd_adjust_contrast(image);

                }
                else {
                    convert_to_grayscale(image, a, b, c);
                    adjust_contrast(image);
                }
            }
            clock_t end_time = clock();
            double execution_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
            printf("Total execution time with %d repetitions: %f seconds\n", values[v], execution_time);
        }
    }
}