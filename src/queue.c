#include "../inc/queue.h"
#include <assert.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

static struct Node*
pop(struct Queue* self) {
    if (!self->head) {
        printf("Queue underflow\n");
        return NULL;
    }

    struct Node* popped = self->head;
    self->head = popped->next;

    if (!self->head) {
        self->cursor = NULL;
    }

    return popped;
}


static void
append(struct Queue* self, void* data, size_t size) {
    struct Node* n = (struct Node*)calloc(1, sizeof(struct Node));
    assert(n);

    n->next = NULL;
    n->data = calloc(1, size);
    assert(n->data);
    memcpy(n->data, data, size);

    if (!self->head) { // The Queue is empty.
        assert(!self->cursor); // cursor = head = NULL now.
        self->head = n;
    }
    else {
        assert(self->cursor);
        self->cursor->next = n;
    }
    self->cursor = n;
}

static void
prepend(struct Queue* self, void* data, size_t size) {
    struct Node* n = (struct Node*)calloc(1, sizeof(struct Node));
    assert(n);

    n->next = self->head;
    n->data = calloc(1, size);
    assert(n->data);
    memcpy(n->data, data, size);

    self->head = n;
    if (!self->cursor) { // The Queue is empty before inserting value.
        self->cursor = n;
    }
}

static struct Queue
new()
{
  return (struct Queue) {
    .head = NULL,
    .cursor = NULL,
    .pop = (void*)&pop,
    .append = (void*)&append,
    .prepend = (void*)&prepend,
  };
}

const struct QueueClass /*QueueProxy*/ Queue = {
  .new = &new,
};