#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h> // for size_t

struct Node {
  int row;
  int col;
  int distance;
  struct Node* next;
};

typedef void (*Callback)(struct Node* node);
struct Queue {
  struct Node* head;
  struct Node* cursor;

  struct Node* (* const pop)(struct Queue* self);
  void (* const append)(struct Queue* self, int col, int row, int dist);
  void (* const prepend)(struct Queue* self, int col, int row, int dist);
};

extern const struct QueueClass {
  struct Queue(*new)();
} Queue;

#endif 