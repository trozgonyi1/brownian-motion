#ifndef HEAP_H
#define HEAP_H

typedef struct Node {
  int value;
  int direction;
  int timestep;
} Node;

typedef struct MaxHeap {
  Node **harr;
  int capacity;
  int heap_size;
} MaxHeap;

int parent(int i);
int left(int i);
int right(int i);
Node *getMax(MaxHeap *h);

MaxHeap *createMaxHeap(int capacity);

void insertKey(struct MaxHeap *h, int k, int direction, int timestep);
void decreaseKey(struct MaxHeap *h, int i, int new_val);
Node *pop(struct MaxHeap *h);
void deleteKey(struct MaxHeap *h, int i);
void MaxHeapify(struct MaxHeap *h, int i);
void swap(Node *x, Node *y);
void print_heap(MaxHeap *h, int curr);
#endif

