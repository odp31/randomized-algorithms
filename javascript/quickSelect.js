function quickSelect(arr, k() {
  if(!arr || arr.length === 0 || k <= 0 || k > arr.length) {
    return null;
  }

  // create copy to avoid modifying original
  const copy = [...arr];

  function partition(low, high) {
    const pivot = copy[high];
    let i = low - 1;

    for(let j = low; j <= high - 1; j++) {
      if(copy[j] < pivot) {
        i++;
        [copy[i], copy[j]] = [copy[j], copy[i]];
      }
    }
    [copy[i+1], copy[high]] = [copy[high], copy[i+1]];
    return i + 1;
  }

  let low = 0;
  let high = copy.length - 1;

  while(low <= high) {
    const pivotIndex = partition(low, high);

    if(pivotIndex === k - 1) {
      return copy[pivotIndex];
    } else if (pivotIndex < k - 1) {
      low = pivotIndex + 1;
    } else {
      high = pivotIndex - 1;
    }
  }
  return null;
}

// example usage
const arr = [5, 2, 8, 1, 9, 4];
const kthSmallest = quickSelect(arr, 3);
console.log("3d smallest:", kthSmallsest);

const kthLargest = quickSelect(arr, arr.length - 2 + 1);
console.log("2nd largest:", kthLargest);

const smallest = quickSelect(arr, 1);
console.log("smallest:", smallest);

const largest = quickSelect(arr, arr.length);
console.log("largest:", largest);

const emptyArr = [];
const result = quickSelect(emptyArr, 2);
console.log("result for empty array:", result);

const invalidK = quickSelect(arr, 7);
console.log("invalid k:", invalidK)

const invalidK2 = quickSelect(arr, 0);
console.log("invalid k:", invalidK2);

console.log("original array:", arr); 
