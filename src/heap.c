#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../include/heap.h"

int parent(int i)
{
    return (i - 1) / 2;
}
int left(int i)
{
    return (2 * i + 1);
}
int right(int i)
{
    return (2 * i + 2);
}

Node *getMax(MaxHeap *h)
{
  if (h->heap_size == 0) return NULL;
  return h->harr[0];
}

void insertKey(MaxHeap *h, int k, int direction, int timestep) {
  h->heap_size++;
  int i = h->heap_size - 1;
  Node *n = malloc(sizeof(Node));
  n->value = k;
  n->direction = direction;
  n->timestep = timestep;
  h->harr[i] = n;
  printf("inserted: (%d, %d, %d)\n", n->value, n->direction, n->timestep);

  while (i != 0 && h->harr[parent(i)]->value < h->harr[i]->value)
  {
    swap(h->harr[i], h->harr[parent(i)]);
    i = parent(i);
  }
}

void decreaseKey(struct MaxHeap *h, int i, int new_val)
{
    h->harr[i]->value = new_val;
    while (i != 0 && h->harr[parent(i)]->value < h->harr[i]->value)
    {
        swap(h->harr[i], h->harr[parent(i)]);
        i = parent(i);
    }
}

Node *pop(struct MaxHeap *h)
{
  if (h->heap_size == 0) return NULL;
    if (h->heap_size <= 0) {
        Node *n = (Node *)malloc(sizeof(Node));
        n->value = INT_MAX;
        n->direction = 0;
        n->timestep = 0;
        return n;
    }
    if (h->heap_size == 1)
    {
        h->heap_size--;
        return h->harr[0];
    }

    Node *root = h->harr[0];
    h->harr[0] = h->harr[h->heap_size - 1];
    h->heap_size--;
    MaxHeapify(h, 0);

    return root;
}

void deleteKey(struct MaxHeap *h, int i)
{
    decreaseKey(h, i, INT_MAX);
    pop(h);
}

MaxHeap *createMaxHeap(int capacity) {
    struct MaxHeap *h = (MaxHeap *)malloc(sizeof(struct MaxHeap));
    h->heap_size = 0;
    h->capacity = capacity;
    h->harr = (Node **)malloc(capacity * sizeof(Node *));
    return h;
}

void MaxHeapify(struct MaxHeap *h, int i)
{
    int l = left(i);
    int r = right(i);
    int largest = i;

    if (l < h->heap_size && h->harr[l]->value > h->harr[i]->value)
        largest = l;
    if (r < h->heap_size) {
    if (h->harr[r]->value > h->harr[largest]->value)
        largest = r;
    }
    if (largest != i)
    {
        swap(h->harr[i], h->harr[largest]);
        MaxHeapify(h, largest);
    }
}

void swap(Node *x, Node *y)
{
  Node temp = {0}; 
  temp.value = x->value;
  temp.direction = x->direction;
  x->value = y->value;
  x->direction = y->direction;
  y->value = temp.value;
  y->direction = temp.direction;
}

void print_heap(MaxHeap *h, int curr) {
  if (curr >= h->heap_size) return;
  printf("(%d, %d) ", h->harr[curr]->value, h->harr[curr]->direction);
  print_heap(h, left(curr));
  print_heap(h, right(curr));
}
