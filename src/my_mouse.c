#include "../inc/my_mouse.h"

int my_mouse(const char* file) {
    struct Matrix m = Matrix.new();
    if (m.read(file) || m.get_size()) {
        m.free();
        return EXIT_FAILURE;
    }
    m.print();
    return EXIT_SUCCESS;
}