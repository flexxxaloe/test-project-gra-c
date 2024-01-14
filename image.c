#include <stdio.h>
#include <stdlib.h>
#include <png.h>

void read_png_dimensions(const char* filename, size_t* width, size_t* height) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return;
    }

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) {
        fclose(file);
        fprintf(stderr, "Error creating PNG read structure\n");
        return;
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        png_destroy_read_struct(&png, NULL, NULL);
        fclose(file);
        fprintf(stderr, "Error creating PNG info structure\n");
        return;
    }

    png_init_io(png, file);
    png_read_info(png, info);

    *width = png_get_image_width(png, info);
    *height = png_get_image_height(png, info);

    png_destroy_read_struct(&png, &info, NULL);
    fclose(file);
}

int main() {
    size_t width, height;
    const char* filename = "your_image.png";

    read_png_dimensions(filename, &width, &height);

    printf("Image dimensions: %zu x %zu\n", width, height);

    return 0;
}
