#include "../inc/my_mouse.h"

int main(const int ac, const char** av) {
    if (ac > 1) {
        return my_mouse(av[1]);
    }
    printf(HELP);
    return EXIT_SUCCESS;
}