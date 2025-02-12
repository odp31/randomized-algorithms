#include <stdio.h>
#include <stdlib.h>

// function to swap 2 integers
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}


// partition function 
int partition(int arr[], int low, int high) {
  int pivot = arr[high];
  int i = (low - 1);

  for(int j = low; j <= high - 1; j++) {
    if(arr[j] < pivot) {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[high]);
  return (i + 1);
}


// quickselect function to find the k-th smallest element

int quickselect(int arr[], int low, int high, int k) {
  if (k > 0 && k <= high - low + 1) {
    int partitionIndex = partition(arr, low, high);

    if(partitionIndex - low == k - 1) {
      return arr[partitionIndex];
    }
    if(partitionIndex - low > k - 1) {
      return arr[partitionIndex];
    }
    return quickselect(arr, partitionIndex + 1, high, k - (partitionIndex - low + 1));
  }
  return -1;
}

int main() {
  int arr[] = {10, 4, 5, 8, 6, 11, 26};
  int n = sizeof(arr) / sizeof(arr[0]);
  int k = 3;    // find 3rd smallest element

  int result = quickselect(arr, 0, n - 1, k);

  if(result != -1) {
    printf("the %d-th smallest element is %d\n", k, result);
  } else {
    printf("invalid input for k\n");
  }
  // example for finding median
  k = (n + 1) / 2;
  result = quickselect(arr, 0, n -1, k);
  if(result != -1) {
    printf("median element is %d\n", result);
  } else {
    printf("invalid input for k\n");
  }
  return 0;
}
