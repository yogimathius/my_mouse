#include "../inc/my_mouse.h"

int my_mouse(const char* file) {
    FILE* f = fopen(file, "r");
    if (f == NULL) {
        return EXIT_FAILURE;
    }
    char c;
    while ((c = fgetc(f)) != EOF) {
        printf("%c", c);
    }
    fclose(f);
    return EXIT_SUCCESS;
}