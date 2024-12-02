import random

def reservoir_sampling(stream, k):
  """
  Implements reservoir sampling to select k items from a stream of n items 
  Args:
    stream: a list representing the stream of items
    k: the number of items to sample
  Returns:
    a list of k sampled items
  """
  reservoir = []
  for i in range(k):
    reservoir.append(stream[i])

  for i in range(k, len(stream)):
    j = random.randint(0, i)
    if j < k:
      reservoir[j] = stream[i]

  return reservoir

# example usage
stream = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
k = 3
sample = reservoir_sampling(stream, k)
print(sample) 
