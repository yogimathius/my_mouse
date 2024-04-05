#include "../inc/my_mouse.h"

#define min(a, b) ((a < b) ? a : b)

static struct Matrix* self;

static void _print() {
    dprintf(STDOUT_FILENO, "%.*s", (int)self->size, self->buffer);
}

static int
_read(const char* file) {
    struct stat s;
    int fd = open(file, O_RDONLY);
    if (fd == -1) {
        dprintf(2, "Error opening file: '%s'\n", file);
        return 1;
    }
    if (fstat(fd, &s) == -1) {
        dprintf(2, "Error stat size file: '%s'\n", file);
        close(fd);
        return 1;
    }
    self -= __MatrixClass_self_alignement;
    if ((self->buffer = (char*)malloc(s.st_size)) == NULL) {
        dprintf(2, "Error allocating memory for buffer\n");
        close(fd);
        return 1;
    }
    if ((self->size = read(fd, self->buffer, s.st_size)) == -1) {
        dprintf(2, "Failed to read file: '%s'\n", file);
        free(self->buffer);
        close(fd);
        return 1;
    }
    close(fd);
    return 0;
}

static int
_get_size() {
    const char* LF = strchr(self->buffer, '\n');
    if (LF == NULL) {
        printf("No newline found in buffer\n");
        return 1;
    }
    char line[SIZE];
    strncpy(line, self->buffer, LF - self->buffer);
    line[LF - self->buffer] = '\0';

    self->cols = self->rows = atoi(line);
    int index = LF - self->buffer;

    memmove(self->buffer, self->buffer + index + 1, self->size - index - 1);
    self->size -= index + 1;
    return 0;
}

static void
_alloc() {
    _get_size();
    if ((self->matrix = (int**)malloc(sizeof(int*) * self->rows)) == NULL) {
        dprintf(2, "Error allocating memory for matrix\n");
        return;
    }
    int i = 0;
    while (i < self->rows) {
        if (((self->matrix)[i] = (int*)malloc(self->cols * sizeof(int))) == NULL) {
            dprintf(2, "Error allocating memory for matrix row\n");
            return;
        }
        i += 1;
    }
}

// TODO: Update this function to check for the mouse map instead of bsq
static void
_build() {
    int k = 0;
    int i = 0;

    _alloc();
    self->max_val = 0;
    self->max_row = 0;
    self->max_col = 0;
    while (i < self->rows) {
        int j = 0;
        while (j < self->cols) {
            if (i == 0 || j == 0) {
                self->matrix[i][j] = (self->buffer[k] == 'o') ? 0 : 1;
            }
            else {
                if (self->buffer[k] == '.') {
                    self->matrix[i][j] = min(min(self->matrix[i - 1][j], self->matrix[i][j - 1]), self->matrix[i - 1][j - 1]) + 1;
                    if (self->matrix[i][j] > self->max_val) {
                        self->max_val = self->matrix[i][j];
                        self->max_row = i;
                        self->max_col = j;
                    }
                }
                else {
                    self->matrix[i][j] = 0;
                }
            }
            if (k < self->size) {
                if (self->buffer[k] == '\n') {
                    j -= 1;
                }
                k += 1;
            }
            j += 1;
        }
        i += 1;
    }
}

static void
_debug() {
    int i = 0;
    int j = 0;

    while (i < self->rows) {
        while (j < self->cols) {
            printf("%d", self->matrix[i][j]);
            j += 1;
        }
        printf("\n");
        j = 0;
        i += 1;
    }
}

static void
_free() {
    free(self->buffer);
    int i = 0;
    while (i < self->rows) {
        if (self->matrix[i]) {
            free(self->matrix[i]);
        }
        i += 1;
    }
    free(self->matrix);
}


static struct Matrix
_new() {
    return *(self = &(struct Matrix) {
        .matrix = NULL,
            .rows = 0,
            .cols = 0,
            .max_val = 0,
            .max_row = 0,
            .max_col = 0,
            .read = &_read,
            .get_size = &_get_size,
            .alloc = &_alloc,
            .build = &_build,
            .debug = &_debug,
            .print = &_print,
            .free = &_free,
    });
}

const struct MatrixClass Matrix = {
  .new = &_new,
};