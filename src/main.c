#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>
#include "../include/heap.h"

int comp(const void *a, const void *b) {
  return ((Node *)a)->value - ((Node *)b)->value;
}

int main(int argc, char **argv) {
  MaxHeap *maxheap = createMaxHeap(1<<8);

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
    int count = 0;
    Node *n = pop(maxheap);
    if (n == NULL) return 0;
    int max = abs(n->value);

    // Will need to lookup the slope of the step one line above and one timestep before
    int slope_map[1<<10][TIME_STEPS];

    level_array[count] = n;

    Node *curr = getMax(maxheap);
    if (curr == NULL) return 0;
    while (curr->value == n->value) {
      count++;
      curr = pop(maxheap);
      if (curr == NULL) return 0;
      level_array[count] = curr;
    }
    qsort(level_array, count, sizeof(Node *), comp);

    for (int t = 0; t < TIME_STEPS; t++) {
      bool print_space = true;
      for (int j = 0; j < count; j++) {
        if (level_array[j]->timestep == t) {
          print_space = false;
          
          int ind = level_array[j]->value;
          if (level_array[j]->value < 0) {
            ind = max + abs(level_array[j]->value);
          }
          slope_map[ind][t] = n->direction;

          if (n->direction == 1) {
            if (slope_map[ind-1][t-1] == -1) {
              printf("\\/");
            } else {
              printf("/");
            }
          } else if (n->direction == -1) {
            printf("\\");
          }
        }
      }
      if (print_space) {
        printf(" ");
      }
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
