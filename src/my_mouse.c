#include "../inc/my_mouse.h"
#include "../inc/matrix.h"

int my_mouse(const char* file) {
    struct Matrix m = Matrix.new();
    if (m.read(file)) {
        m.free();
        return EXIT_FAILURE;
    }
    m.print();
    int dist = m.min_distance();
    printf("Minimum distance: %d\n", dist);
    return EXIT_SUCCESS;
}