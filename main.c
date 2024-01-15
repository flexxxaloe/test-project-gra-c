#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "image_processing.h"
#include "image.h"
#include <limits.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
Image *readPPM(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("File opening failed read PPM");
        return NULL;
    }

    char buffer[16];
    if (!fgets(buffer, sizeof(buffer), fp)) {
        perror("Reading PPM type failed");
        fclose(fp);
        return NULL;
    }

    if (buffer[0] != 'P' || buffer[1] != '6') {
        fprintf(stderr, "Invalid image format (must be 'P6')\n");
        fclose(fp);
        return NULL;
    }

    Image *img = malloc(sizeof(Image));
    if (!img) {
        fprintf(stderr, "Unable to allocate memory for image\n");
        fclose(fp);
        return NULL;
    }

    // Skip comments
    char c = getc(fp);
    while (c == '#') {
        while (getc(fp) != '\n');
        c = getc(fp);
    }
    ungetc(c, fp);

    // Read image size
    if (fscanf(fp, "%d %d", &img->width, &img->height) != 2) {
        fprintf(stderr, "Invalid image size (error loading 'width' and 'height')\n");
        fclose(fp);
        free(img);
        return NULL;
    }

    // Read rgb component
    int rgb_comp_color;
    if (fscanf(fp, "%d", &rgb_comp_color) != 1) {
        fprintf(stderr, "Invalid rgb component (error loading 'rgb_comp_color')\n");
        fclose(fp);
        free(img);
        return NULL;
    }

    // Check rgb component depth
    if (rgb_comp_color!= 255) {
        fprintf(stderr, "'rgb_comp_color' must be 255\n");
        fclose(fp);
        free(img);
        return NULL;
    }

    while (fgetc(fp) != '\n');
    img->pixels = (Pixel *)malloc(img->width * img->height * sizeof(Pixel));

    if (!img->pixels) {
        fprintf(stderr, "Unable to allocate memory for pixels\n");
        fclose(fp);
        free(img);
        return NULL;
    }

    // Read pixel data from file
    if (fread(img->pixels, 3 * img->width, img->height, fp) != img->height) {
        fprintf(stderr, "Error loading image\n");
        fclose(fp);
        free(img->pixels);
        free(img);
        return NULL;
    }

    fclose(fp);
    return img;
}

void writePPM(const char *filename, Image *img) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("File opening failed");
        return;
    }

    fprintf(fp, "P6\n%d %d\n255\n", img->width, img->height);
    fwrite(img->pixels, 3 * img->width, img->height, fp);
    fclose(fp);
}
void print_help(const char *program_name) {
    printf("Usage: %s [OPTIONS] <input_filename>\n", program_name);
    printf("Options:\n");
    printf("  -V, --version <Zahl>     Die Implementierung, die verwendet werden soll. Hierbei soll mit -V 0 Ihre Hauptimplementierung verwendet werden. Wenn diese Option nicht gesetzt wird, soll ebenfalls die Hauptimplementierung ausgeführt werden.\n");
    // ... (остальные опции)
    printf("  -h, --help               Eine Beschreibung aller Optionen des Programms und Verwendungsbeispiele werden ausgegeben und das Programm danach beendet.\n");
    printf("Examples:\n");
    printf("  %s -V 1 -B 10 input.ppm -o output.ppm --brightness 50 --contrast -100\n", program_name);
}


int main(int argc, char *argv[]) {
    const char *input_filename = argv[1];
    Image *image = readPPM(input_filename);
    if (image) {
        // Обработка изображения (например, конвертация в градации серого)



        float a = 0.2126f, b = 0.7152f, c = 0.0722f; // Для коэффициентов
        int version = 0; // По умолчанию используется версия 0
        // Определение длинных опций
        struct option long_options[] = {
                {"version",    required_argument, 0, 'V'},
                {"benchmark",  optional_argument, 0, 'B'},
                {"output",     required_argument, 0, 'o'},
                {"coeffs",     required_argument, 0, 'c'},
                {"brightness", required_argument, 0, 'l'},
                {"contrast",   required_argument, 0, 'k'},
                {"help",       no_argument,       0, 'h'},
                {0,            0,                 0, 0}
        };

        // Переменные для хранения результатов разбора опций
        int option;
        int option_index = 0;
        char *output_filename = NULL;
        int benchmark = 0;
        int benchmark_repetitions = 1; // По умолчанию количество повторений равно 1
        image->contrast = 0.0f;
        image->brightness = 0;

        // Разбор опций
        while ((option = getopt_long(argc, argv, "V:B:o:c:l:k:h", long_options, &option_index)) != -1) {
            switch (option) {
                case 'V':
                    version = atoi(optarg);
                    break;
                case 'B':
                    benchmark = 1;
                    benchmark_repetitions = optarg ? atoi(optarg) : benchmark_repetitions;
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
        if(version == 1){
            convert_to_grayscale(image, a, b, c);
            simple_adjust_contrast(image);
        }else if(version == 2){
            simd_convert_to_grayscale(image, a, b, c);
            adjust_contrast(image);

        }
        else {
            convert_to_grayscale(image, a, b, c);
            adjust_contrast(image);
        }
        if (!output_filename) {
            // Здесь вы можете использовать output_filename для записи изображения
            output_filename = "output.ppm";
            writePPM(output_filename, image);
        }
        if (benchmark) {
            printf("Benchmarking with %d repetitions\n", benchmark_repetitions);

            // Измеряем время выполнения функции
            clock_t start_time = clock();
            for (int i = 0; i < benchmark_repetitions; ++i) {
                if(version == 1){
                    convert_to_grayscale(image, a, b, c);
                    simple_adjust_contrast(image);
                }else if(version == 2){
                    simd_convert_to_grayscale(image, a, b, c);
                    adjust_contrast(image);

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
        writePPM(output_filename, image);
        printf("Brightness: %d\n", image->brightness);
        printf("Contrast: %f\n", image->contrast);

        free(image->pixels);
        free(image);


        printf("Coefficients: a=%f, b=%f, c=%f\n", a, b, c);
        printf("Selected version: %d\n", version);
        // Разбор позиционных аргументов (например, имя входного файла)
    }


    return 0;
}