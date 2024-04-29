#include "../inc/my_mouse.h"
#include "../inc/matrix.h"

int my_mouse(const char* file) {
    struct Matrix m = Matrix.new();
    if (m.read(file)) {
        m.free();
        return EXIT_FAILURE;
    }

    int dist = m.min_distance();
    if (dist == -1 || dist == 0) {
        printf("MAP ERROR!\n");
        m.free();
        return EXIT_FAILURE;
    }
    m.debug();
    printf("%d STEPS!\n", dist);
    return EXIT_SUCCESS;
}