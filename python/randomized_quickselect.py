import random 

def randomized_quickselect(arr, k):
  """
  finds k-th smallest elemetn in an unsroted array
  """
  if len(arr) == 1:
    return arr[0]

  pivot_index = random.randint(0, len(arr) -1)
  pivot = arr[pivot_index]

  # partition array
  left = [x for x in arr if x < pivot]
  right = [x for x in arr if x > pivot]

  if k < len(left):
    return randomized_quickselect(left, k)
  elif k == len(left):
    return pivot
  else:
    return randomized_quickselect(right, k-len(left) -1)

# example usage
arr = [3, 7, 8, 5, 2, 1, 9, 6, 4]
k = 3
result = randomized_quickselect(arr, k)
print(result) #output: 4

