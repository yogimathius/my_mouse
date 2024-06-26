#include "../inc/my_mouse.h"
#include "../inc/matrix.h"
#include "../inc/queue.h"

#define min(a, b) ((a < b) ? a : b)

static struct Matrix* self;

static void _print() {
    dprintf(STDOUT_FILENO, "%.*s\n", (int)self->size, self->buffer);
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
    sscanf(line, "%dx%d%c%c%c%c%c", &self->rows, &self->cols, &self->full, &self->empty, &self->path, &self->start, &self->end);
    int index = LF - self->buffer;
    self->header = (char*)malloc(index + 1);
    strncpy(self->header, line, index);
    self->header[index] = '\0';
    memmove(self->buffer, self->buffer + index + 1, self->size - index - 1);
    self->size -= index + 1;
    return 0;
}

static void
_alloc() {
    _get_size();
    if ((self->matrix = (char**)malloc(sizeof(char*) * self->rows)) == NULL) {
        dprintf(2, "Error allocating memory for matrix\n");
        return;
    }
    int i = 0;
    while (i < self->rows) {
        if (((self->matrix)[i] = (char*)malloc(self->cols * sizeof(char))) == NULL) {
            dprintf(2, "Error allocating memory for matrix row\n");
            return;
        }
        i += 1;
    }
}

static bool
_validate_map() {
    if (self->rows <= 0 || self->cols <= 0) {
        return false;
    }

    int entrance_count = 0;
    int exit_count = 0;
    for (int i = 0; i < self->rows; i++) {
        for (int j = 0; j < self->cols; j++) {
            if (self->matrix[i][j] == self->start) {
                entrance_count++;
            }
            else if (self->matrix[i][j] == self->end) {
                exit_count++;
            }
        }
    }
    if (entrance_count != 1) {
        return false;
    }
    if (exit_count != 1) {
        return false;
    }

    char* first_line = self->matrix[0];
    for (int i = 0; i < self->rows; i++) {
        for (int j = 0; j < self->cols; j++) {
            if (strchr(first_line, self->matrix[i][j]) == NULL && self->matrix[i][j] != self->empty && self->matrix[i][j] != self->start && self->matrix[i][j] != self->end) {
                printf("Invalid character found in self: %c\n", self->matrix[i][j]);
                return false;
            }
        }
    }

    return true;
}

static int
_min_distance() {
    int k = 0;
    int i = 0;
    struct Node source = { 0, 0, 0, NULL, NULL };
    struct Node destination = { 0, 0, 0, NULL, NULL };
    _alloc();

    bool visited[self->rows][self->cols];
    while (i < self->rows) {
        int j = 0;
        while (j < self->cols) {
            if (j == self->cols - 1 && self->buffer[k + 1] != '\n') {
                printf("Invalid row length: %d\n", (int)strlen(self->matrix[i]));
                printf("Expected row length: %d\n", self->rows);
                return false;
            }
            if (self->buffer[k] == self->start) {
                source.row = i;
                source.col = j;
                self->matrix[i][j] = self->start;
            }
            else if (self->buffer[k] == self->end) {
                destination.row = i;
                destination.col = j;
                self->matrix[i][j] = self->end;
            }
            else if (self->buffer[k] == self->full) {
                visited[i][j] = true;
                self->matrix[i][j] = self->full;
            }
            else {
                visited[i][j] = false;
                self->matrix[i][j] = self->empty;
            }
            // else {
            //     printf("Invalid character found in self: %c\n", self->buffer[k]);
            //     return 0;
            // }

            if (k < self->size) {
                if (self->buffer[k] == '\n') {
                    j -= 1;
                }
                k += 1;
            }
            else if (self->buffer[k] == '\0') {
                return -1;
            }
            j += 1;
        }
        i += 1;
    }
    if (!_validate_map()) {
        return -1;
    }
    struct Queue q = Queue.new();
    q.append(&q, source.row, source.col, source.distance, NULL);
    visited[source.row][source.col] = true;
    struct Node* destination_node = NULL;

    while (q.head) {
        struct Node* current = (struct Node*)malloc(sizeof(struct Node));
        current = q.pop(&q);
        int row = current->row;
        int col = current->col;
        int dist = current->distance;
        if (row == destination.row && col == destination.col) {
            printf("%s\n", self->header);

            destination_node = current;
            while (destination_node != NULL) {
                int row = destination_node->row;
                int col = destination_node->col;
                if ((row != source.row || col != source.col) && (row != destination.row || col != destination.col)) {
                    self->matrix[destination_node->row][destination_node->col] = self->path;
                }
                destination_node = destination_node->parent;
            }
            return dist - 1;
        }

        // Move up
        if (row - 1 >= 0 && !visited[row - 1][col]) {
            q.append(&q, row - 1, col, dist + 1, current);
            visited[row - 1][col] = true;
        }

        // Move left
        if (col - 1 >= 0 && !visited[row][col - 1]) {
            q.append(&q, row, col - 1, dist + 1, current);
            visited[row][col - 1] = true;
        }

        // Move right
        if (col + 1 < self->cols && !visited[row][col + 1]) {
            q.append(&q, row, col + 1, dist + 1, current);
            visited[row][col + 1] = true;
        }

        // Move down
        if (row + 1 < self->rows && !visited[row + 1][col]) {
            q.append(&q, row + 1, col, dist + 1, current);
            visited[row + 1][col] = true;
        }
    }

    return 0;
}

static void
_debug() {
    int i = 0;
    int j = 0;

    while (i < self->rows) {
        while (j < self->cols) {
            printf("%c", self->matrix[i][j]);
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
            .read = &_read,
            .get_size = &_get_size,
            .alloc = &_alloc,
            .min_distance = &_min_distance,
            .debug = &_debug,
            .print = &_print,
            .free = &_free,
            .validate_map = &_validate_map,
    });
}

const struct MatrixClass Matrix = {
  .new = &_new,
};