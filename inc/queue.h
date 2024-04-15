#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h> // for size_t

struct Node {
  int row;
  int col;
  int distance;
  struct Node* parent;
  struct Node* next;
};

typedef void (*Callback)(struct Node* node);
struct Queue {
  struct Node* head;
  struct Node* cursor;

  struct Node* (* const pop)(struct Queue* self);
  void (* const append)(struct Queue* self, int row, int col, int dist, struct Node* parent);
  void (* const prepend)(struct Queue* self, int row, int col, int dist, struct Node* parent);
};

extern const struct QueueClass {
  struct Queue(*new)();
} Queue;

#endif 