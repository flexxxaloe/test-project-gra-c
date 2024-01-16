#include <stdio.h>
#include "image.h"
#include <stdlib.h>

void read_ppm_dimensions(const char* filename, size_t* width, size_t* height) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    char magic_number[3];
    if (fscanf(file, "%2s", magic_number) != 1 || magic_number[0] != 'P' || magic_number[1] != '6') {
        fclose(file);
        fprintf(stderr, "Not a valid PPM file\n");
        return;
    }

    if (fscanf(file, "%zu %zu", width, height) != 2) {
        fclose(file);
        fprintf(stderr, "Error reading PPM dimensions\n");
        return;
    }

    fclose(file);
}
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

