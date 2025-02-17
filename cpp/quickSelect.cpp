#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

//partiton function (lomutos partition scheme)
int partition(vector<int>& arr, int low, int high) {
  // choose last element as pivot
  int pivot = arr[high];

  // index of smaller element and indicates the right positon of pivot found so far
  int i = (low - 1);
  for(int j = low; j <= high - 1; j++) {
    // if current element is smaller than pivot
    if(arr[j] < pivot) {
      i++;
      swap(arr[i], arr[j]);
    }
  }
  swap(arr[i + 1], arr[high]);
  return (i + 1);
}

// quick select function
int quickSelect(vector<int>& arr, int low, int high, int k) {
  if(k > 0 && k <= high - low + 1) {
    //partition array around pivot
    int partitionIndex = partition(arr,low,high);
    if(partitionIndex - low == k - 1) 
      return arr[partitionIndex];
    if(partitionIndex - low > k - 1)
      return quickSelect(arr, low, partitionIndex - 1, k);
    return quickSelect(arr, partitionIndex + 1, high, k - (partitionIndex - low + 1));
  }
  return -1;
}

int main() {
  vector<int> arr = {10, 4, 5, 8, 6, 11, 26};
  int n = arr.size();
  int k = 3;

  int kthSmallest = quickSelect(arr, 0, n - 1, k);
  if(kthSmallest != -1) {
    cout << k << "rd smallest element:" << kthSmallest << endl;
  } else {
    cout << "invalid input: k is outof range" << endl;
  }

  vector<int< arr2 = {10, 4, 5, 8, 6, 11, 26};
  nth_element(arr2.begin(), arr2.begin() + k -1, arr2.end());
  cout << k << "rd smallest element (using n_th element):" <<arr2[k-1] << endl;
  return 0;
}

