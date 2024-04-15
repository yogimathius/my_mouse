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

  void (* const pop)(struct Queue* self);
  void (* const append)(struct Queue* self, void* data, size_t size);
  void (* const prepend)(struct Queue* self, void* data, size_t size);
  //   void (* const traverse)(struct Queue* self, Callback func);
};

extern const struct QueueClass {
  struct Queue(*new)();
} Queue;

#endif 