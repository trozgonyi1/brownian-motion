#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "../include/heap.h"

int comp(const void *a, const void *b) {
  return ((Node *)a)->value - ((Node *)b)->value;
}

int main(int argc, char **argv) {
  MaxHeap *maxheap = createMaxHeap(1<<6);

  srand(time(NULL));
  
  int TIME_STEPS = 100;

  int total = 0;
  for (int i = 0; i < TIME_STEPS; i++) {
    int direction = rand() % 2;
    if (direction == 0) direction = -1;
    insertKey(maxheap, total, direction, i);
    total += direction;
  }

  while (maxheap->heap_size > 0) {
    Node *level_array[BUFSIZ];
    int i = 0;
    Node *n = pop(maxheap);

    for (int i = 0; i < n->timestep; i++) {
      printf(" ");
    }

    if (n->direction == 1) {
      printf("/");
    } else if (n->direction == -1) {
      printf("\\");
    }
    printf("\n");
/*    level_array[i] = n;
    
    Node *curr;
    while ((curr = getMax(maxheap))->value == n->value && curr != NULL) {
      i++;
      curr = pop(maxheap);
      if (curr->value == INT_MAX) break;
      level_array[i] = curr;
    }
    int size = sizeof(level_array)/sizeof(level_array[0]);
    qsort(level_array, size, sizeof(Node *), comp);

    for (int j = 0; j < TIME_STEPS; j++) {
      for (int k = 0; k < i; k++) {
        if (level_array[k]->timestep == j) {
          if (level_array[k]->direction == 1) {
            printf("/");
          } else if (level_array[k]->direction == -1) {
            printf("\\");
          }
        } else {
          printf(" ");
        }
      }
    }
    printf("\n");*/
  }

  return 0;
}
