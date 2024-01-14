#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "image_processing.h"
#include "image.h"
#include <limits.h>
#include <errno.h>

Image *readPPM(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("File opening failed");
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



int main(int argc, char *argv[]) {
    Image *image = readPPM("C:\\Users\\mihai\\Downloads\\040.ppm");


    if (image) {
        convert_to_grayscale(image, 1.0f,1.0f,1.0f);
        writePPM("output.ppm", image);
        free(image->pixels);
        free(image);
    }

    // Определение длинных опций
    struct option long_options[] = {
            {"version", required_argument, 0, 'V'},
            {"benchmark", optional_argument, 0, 'B'},
            {"output", required_argument, 0, 'o'},
            {"coeffs", required_argument, 0, 'c'},
            {"brightness", required_argument, 0, 'l'},
            {"contrast", required_argument, 0, 'k'},
            {"help", no_argument, 0, 'h'},
            {0, 0, 0, 0}
    };

    // Переменные для хранения результатов разбора опций
    int option;
    int option_index = 0;
    char *output_filename = NULL;
    int version = 0; // По умолчанию используется версия 0
    int benchmark = 0;
    int benchmark_repetitions = 1; // По умолчанию количество повторений равно 1
    float a = 0.0f, b = 0.0f, c = 0.0f; // Для коэффициентов
    int brightness = 0; // Для яркости
    int contrast = 0; // Для контраста

    // Разбор опций
    while ((option = getopt_long(argc, argv,  "V:B:o:c:l:k:h", long_options, &option_index)) != -1) {
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
                brightness = strtol(optarg, &endptr, 10);

                // Проверяем ошибки преобразования
                if ((errno == ERANGE && (brightness == LONG_MAX || brightness == LONG_MIN))
                    || (errno != 0 && brightness == 0)) {
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

                break;
            case 'k':
                contrast = atoi(optarg);
                break;
            case 'h':
                printf("Usage: ..."); // Выведите справку по использованию программы
                return 0;
        }
    }
    printf("Brightness: %d\n", brightness);

    // Разбор позиционных аргументов (например, имя входного файла)
    if (optind < argc) {
        const char *input_filename = argv[optind];
        Image *imagesecondtime = readPPM(input_filename);
        if (image) {
            // Обработка изображения (например, конвертация в градации серого)
            convert_to_grayscale(imagesecondtime, 1.0f, 1.0f, 1.0f);

            // Сохранение результата
            writePPM("output.ppm", imagesecondtime);

            // Освобождение памяти
            free(imagesecondtime->pixels);
            free(imagesecondtime);
        } else {
            fprintf(stderr, "Error reading PPM file.\n");
            return EXIT_FAILURE;
        }
    } else {
        fprintf(stderr, "Error: Missing input file.\n");
        return EXIT_FAILURE;
    }




    return 0;
}
