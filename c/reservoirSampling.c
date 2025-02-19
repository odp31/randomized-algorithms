#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* reservoirSampling(int* stream, int n, int k) {
  if(k <= 0 || n == 0) {
    return NULL;
  }
  k = (k > n) ? n : k;

  int* reservoir = (int*)malloc(k * sizeof(int));
  if(reservoir == NULL) {
    perror("memory allocation failed");
    exit(EXIT_FAILURE);
  }
  // initialize reservoir with first k elements
  for(int i = 0; i < k; i++) {
    reservoir[i] = stream[i];
  }

  for(int i = k i < n; i++) {
    int j = rand() % (i + 1);
    if(j < k) {
      reservoir[rand() % k] = stream[i];
    }
  }
  return reservoir;
}

int main() {
  srand(time(NULL));
  int stream[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  int n = sizeof(stream) / sizeof(stream[0]);
  int k = 5;

  int* sample = reservoirSampling(stream, n, k);

  if(sample != NULL) {
    printf("sample: ");
    for(int i = 0; i < k; i++) {
      printf("%d", sample[i]);
    }
    printf("\n");
    free(sample);
  }

  k = 10;
  sample = reservoirSampling(stream, n, k);
  if(sample != NULL) {
    printf("sample (k > n) :");
    for(int i = 0; i < k; i++) {
      printf("%d", sample[i]);
    }
    printf("\n");
    free(sample);
  }

  int emptyStream[] = {};
  n = sizeof(emptyStream) / sizeof(emptyStream[0]);
  k = 5;
  sample = reservoirSampling(emptyStream, n , k);
  if(sample != NULL) {
    printf("sample (empty stream): ");
    for(int i = 0; i < k; i++) {
      printf("%d", sample[i]);
    }
    printf("\n");
    free(sample);
  }
// ex with k = 0
int stream2[] = {1, 2, 3, 4, 5};
n = sizeof(stream2) / sizeof(stream2[0]);
k = 0; 
sample = reservoirSampling(stream2, n, k);
if(sample != NULL) {
  printf("sample (k = 0): ");
  for(int i = 0; i < k; i++) {
    printf("%d", sample[i]);
  }
  printf("\n");
  free(sample);
}
return 0;
}
