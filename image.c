#include <stdio.h>

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


