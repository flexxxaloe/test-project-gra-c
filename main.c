#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "image_processing.h"
#include "image.h"
typedef struct {
    unsigned char r, g, b;
} Pixel;

typedef struct {
    int width, height;
    Pixel *pixels;
} Image;

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

void convertToGrayscale(Image *img) {
    for (int i = 0; i < img->width * img->height; ++i) {
        unsigned char gray = (unsigned char)(0.299 * img->pixels[i].r + 0.587 * img->pixels[i].g + 0.114 * img->pixels[i].b);
        img->pixels[i].r = img->pixels[i].g = img->pixels[i].b = gray;
    }
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
    Image *image = readPPM("C:\\Users\\kfedo\\Downloads\\forwork.ppm");
    size_t width, height;

    if (image) {
        int result = read_png_dimensions(image, &width, &height);
        convertToGrayscale(image);
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
    int opt;
    int option_index = 0;
    char *input_filename = NULL;
    char *output_filename = NULL;
    int version = 0; // По умолчанию используется версия 0
    int benchmark = 0;
    int benchmark_repetitions = 1; // По умолчанию количество повторений равно 1
    float a = 0.0, b = 0.0, c = 0.0; // Для коэффициентов
    int brightness = 0; // Для яркости
    int contrast = 0; // Для контраста

    // Разбор опций
    while ((opt = getopt_long(argc, argv,  "V:B::o:c:l:k:h", long_options, &option_index)) != -1) {
        switch (opt) {
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
                brightness = atoi(optarg);
                break;
            case 'k':
                contrast = atoi(optarg);
                break;
            case 'h':
                printf("Usage: ..."); // Выведите справку по использованию программы
                return 0;
        }
    }

    // Разбор позиционных аргументов (например, имя входного файла)
    if (optind < argc) {
        input_filename = argv[optind];
    }

    // Теперь можно выполнить основную логику программы с использованием полученных параметров
    // ...

    return 0;
}
