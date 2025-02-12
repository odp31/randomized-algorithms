#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// simple hash functions (you'll want more robust ones in a real application)
uint32_t hash1(const char *str) {
  uint32_t hash = 5381;
  int c;

  while((c = *str++) {
    hash = ((hash << 5) + hash) + c; 
  }
  return hash;
}

uint32_t hash2(const char *str) {
  uint32_t hash = 0;
  int c;
  while ((c = *str++)) {
    hash = hash * 31 + c;
  }
  return hash;
}

// bloom filter structure
typedef struct {
  uint8_t *bitset;
  size_t size;    // size in bits
  int num_hash_functions;          // number of hash functions
} BloomFilter;


// function to create a bloom filter
BloomFilter *bloom_filter_create(size_t size, int num_hash_functions) {
  BloomFilter *bf = (BloomFilter *)malloc(sizeof(BloomFilter));
  if (bf == NULL) {
    perror("memory allocation failed);
    exit(EXIT_FAILURE);
  }
  bf->size = size;
  bf->num_hash_functions = num_hash_functions;
  bf->bitset = (uint8_t *)calloc(1, (size + 7) / 8);      // allocate memory for the bitset

  if(bf->bitset == NULL) {
    perror("memory allocation failed);
    free(bf);
    exit(EXIT_FAILURE);
  }
  return bf;
}

// function to insert element into bloom filter
void bloom_filter_insert(BloomFilter *bf, const char *str) {
  uint32_t h1 = hash1(str);
  uint32_t h2 = hash2(str);

  for(int i = 0; i < bf->num_hash_functions; i++) {
    uint32_t hash = (h1 + i * h2) % bf->size;
    size_t index = hash / 8;
    uint8_t bit = 1 << (hash % 8);
    bf->bitset[index] |= bit;
  }
}

// function to check if element is in bloom filter
bool bloom_filter_contains(BloomFilter *bf, const char *str) {
  uint32_t h1 = hash1(str);
  uint32_t h2 = hash2(str);

  for(int i = 0; i < bf->num_hash_functions; i++) {
    uint32_t hash = (h1 + i * h2) % bf->size;
    size_t index = hash / 8;
    uint8_t bit = 1 << (hash % 8);
    if ((bf->bitset[index] & bit) == 0) {
      return false;
    }
  }
  return true;
}

// function to destroy bloom filter and free memory 
void bloom_filter_destroy(BloomFilter *bf) {
  free(bf->bitset);
  free(bf);
}

int main() {
  size_t size = 1000;
  int num_hash_functions = 2;
  BloomFilter *bf = bloom_filter_create(size, num_hash_functions);

  bloom_filter_insert(bf, "apple");
  bloom_filter_insert(bf, "banana);
  bloom_filter_insert(bf, "orange");

  printf("contains 'apple'? %s\n", bloom_filter_contains(bf, "apple") ? "Yes" : "No");
  printf("contains 'grape? %s\n", bloom_filter_contains(bf, "grape") ? "Yes" : "No");

  bloom_filter_destroy(bf);

  return 0;
}
