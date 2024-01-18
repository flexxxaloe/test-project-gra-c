#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "image_processing.h"
#include "image.h"
#include <limits.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include "benchmark.h"

void print_help(const char *program_name) {
    printf("Usage: %s [OPTIONS] <input_filename>\n", program_name);
    printf("Options:\n");
    printf("  -V, --version <Zahl>     Die Implementierung, die verwendet werden soll. Hierbei soll mit -V 0 Ihre Hauptimplementierung verwendet werden. Wenn diese Option nicht gesetzt wird, soll ebenfalls die Hauptimplementierung ausgeführt werden.\n");

    printf("  -B, --benchmark <optional Zahl>   Benchmark-Modus aktivieren. Optional kann eine Zahl als Wiederholungszahl für den Benchmark-Modus angegeben werden. Ohne Zahl wird keine Wiederholungen\n");

    printf("  -o, --output <Datei>     Die Ausgabedatei für das bearbeitete Bild.\n");

    printf("  -c, --coeffs <FP Zahl>,<FP Zahl>,<FP Zahl>     Eine Datei mit Koeffizienten für die Anpassung von Helligkeit und Kontrast.\n");

    printf("  -l, --brightness <Zahl>  Der Helligkeitswert für die Anpassung des Bildes.\n");

    printf("  -k, --contrast <Zahl>    Der Kontrastwert für die Anpassung des Bildes.\n");

    printf("  -h, --help               Eine Beschreibung aller Optionen des Programms und Verwendungsbeispiele werden ausgegeben und das Programm danach beendet.\n");

    printf("Examples:\n");
    printf("  ./%s input.ppm -V 1 -B 10 -o output.ppm --brightness 50 --contrast -100\n", program_name);
}
struct option options[] = {
        {"version",    required_argument, 0, 'V'},
        {"benchmark",  optional_argument, 0, 'B'},
        {"output",     required_argument, 0, 'o'},
        {"coeffs",     required_argument, 0, 'c'},
        {"brightness", required_argument, 0, 'l'},
        {"contrast",   required_argument, 0, 'k'},
        {"help",       no_argument,       0, 'h'},
        {0,            0,                 0, 0}
};


int main(int argc, char *argv[]) {
    const char *input_filename = argv[1];
    Image *image = readPPM(input_filename);
    if (image) {

        float a = 0.2126f, b = 0.7152f, c = 0.0722f; // Для коэффициентов
        int version = 0;
        int option;
        int option_index = 0;
        char *output_filename = NULL;
        int benchmark = 0;
        int benchmark_repetitions = 1;
        image->contrast = 0.0f;
        image->brightness = 0;

        // Разбор опций
        while ((option = getopt_long(argc, argv, ":V:B:o:c:l:k:h", options, &option_index)) != -1) {
            switch (option) {
                case 'V':
                    version = atoi(optarg);
                    break;
                case 'B':
                    benchmark = 1;
                    benchmark_repetitions = optarg ? atoi(optarg) : benchmark_repetitions;
                    break;
                case ':':
                    switch (optopt)
                    {
                        case 'B':
                            benchmark = 1;
                            benchmark_repetitions = optarg ? atoi(optarg) : benchmark_repetitions;
                            break;
                        default:
                            fprintf(stderr, "option -%c is missing a required argument\n", optopt);
                            exit(EXIT_FAILURE);

                    }
                    break;

                case 'o':
                    output_filename = optarg;
                    break;
                case '?':
                    // Если возникла ошибка, getopt_long уже вывел сообщение об ошибке
                    return 1;
                case 'c':
                    sscanf(optarg, "%f,%f,%f", &a, &b, &c);
                    break;
                case 'l':
                    errno = 0; // Устанавливаем errno в 0 перед вызовом strtol
                    char *endptr;
                    image->brightness = strtol(optarg, &endptr, 10);
                    // Проверяем ошибки преобразования
                    if (image->brightness < -255 || image->brightness > 255 || errno != 0) {
                        perror("strtol");
                        // Обработка ошибок
                        exit(EXIT_FAILURE);
                    }

                    // Проверяем, была ли строка полностью преобразована
                    if (endptr == optarg) {
                        fprintf(stderr, "No digits were found in --brightness argument\n");
                        // Обработка ошибок
                        exit(EXIT_FAILURE);
                    }

                    //adjust_brightness_contrast( image, brightness, float contrast, Image* result_img);
                    break;
                case 'k':
                    errno = 0; // Устанавливаем errno в 0 перед вызовом strtod
                    char *endpointer;
                    image->contrast = strtof(optarg, &endpointer);
                    // Проверяем ошибки преобразования
                    if (image->contrast < -255.0 || image->contrast > 255.0 || errno != 0) {
                        perror("strtof");
                        // Обработка ошибок
                        exit(EXIT_FAILURE);
                    }

                    // Проверяем, была ли строка полностью преобразована
                    if (endptr == optarg) {
                        fprintf(stderr, "No digits were found in --contrast argument\n");
                        // Обработка ошибок
                        exit(EXIT_FAILURE);
                    }

                    break;

                case 'h':
                    print_help(argv[0]);
                    return 0;
                default:
                    fprintf(stderr, "Unknown option: %c\n", optopt);
                    exit(EXIT_FAILURE);
            }
        }
        if (!output_filename) {
            output_filename = "output.ppm";
        }
        if (benchmark) {
            benchmarking(benchmark_repetitions, image, a, b, c, version);
           // test_alg(image, a, b, c, version); добавить команду t для тестов
        } else {
            if(version == 1){
                convert_to_grayscale(image, a, b, c);
                simple_adjust_contrast(image);
            }else if(version == 2){
                simd_convert_to_grayscale(image, a, b, c);
                simd_adjust_contrast(image);

            }
            else {
                convert_to_grayscale(image, a, b, c);
                adjust_contrast(image);
            }
        }
        writePPM(output_filename, image);
        printf("Brightness: %d\n", image->brightness);
        printf("Contrast: %f\n", image->contrast);
        printf("Coefficients: a=%f, b=%f, c=%f\n", a, b, c);
        printf("Selected version: %d\n", version);
        free(image->pixels);
        free(image);
    }

    return 0;
}