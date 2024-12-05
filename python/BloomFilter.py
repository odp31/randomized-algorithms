import mmh3

class BloomFilter:
  def __init__(self, m, k):
    self.m = m # size of bit array
    self.k = k     # number of hash functions
    self.bit_array = [0] * m

  def add(self, item):
    for i in range(self.k):
      index = mmh3.hash(item, i) % self.m
      self.bit_array[index] = 1

  def might_contain(self, item):
    for i in range(self.k):
      index = mmh3.hash(item, i) % self.m
      if self.bit_array[index] == 0:
        return False
    return True


# example usage
bloom_filter = BloomFilter(1000, 5)
bloom_filter.add("apple")
bloom_filter.add("banana")
bloom_filter.add("cherry")

print(bloom_filter.might_contain("apple")) #output; true
print(bloom_filter.might_contain("grape")) #output; false 
