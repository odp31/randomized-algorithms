#include <iostream>
#include <vector>
#include <string>
#incldue <functional>
#include <cmath>


class BloomFilter {
private:
    std::vector<bool> bitset;
    size_t size;
    size_t num_hash_functions;

    // example hash functions
    std::hash<std::string> hash_fn;


public:
    BloomFilter(size_t expected_elements, double false_positive_rate) {
        size = - (expected_elements * log(false_positive_rate)) / (log(2) * log(2));
        num_hash_functions = std::ceil((size / expected_elements) * log(2));
        bitset.resize(size, false);
    }


    void insert(const std::string& str) {
      for(size_t i = 0; i < num_hash_functions; ++i) {
          size_t hash_val = (hash_fn(str) + i) % size;
          bitset[hash_val] = true;
      }
    }

    bool contains(const std::string& str) const {
      for(size_t i = 0; i < num_hash_functions; ++i) {
        size_t hash_val = (hash_fn(str) + i) % size;
        if(!bitset[hash_val]) {
          return false;
        }
      }
      return true;
    }

    void print() const {
      for(bool b : bitset) {
        std::cout<<b;
      }
      std::cout << std::endl;
    }

    size_t getSize() const { return size; }
    size_t getNumHashFunctions() const { return num_hash_functions;}
}


int main() {
  size_t expected_elements = 100;
  double false_positive_rate = 0.01;

  BloomFilter bf(expected_elements, false_positive_rate);

  std::cout<< "bloom filter size: " << bf.getSize() << " bits" << std::endl;
  std::cout << "number of hash functions: " << bf.getNumHashFunctions() << std::endl;

  bf.insert("apple");
  bf.insert("banana");
  bf.insert("orange");


  std::cout << "Contains 'apple'? " << (bf.contains("apple") ? "Yes" : "No") << std::endl;
  std::cout << "Contains 'grape'? " << (bf.contains("grape") ? "Yes" : "No") << std::endl; // Could be a false positive
  std::cout << "Contains 'kiwi'? " << (bf.contains("kiwi") ? "Yes" : "No") << std::endl; // Could be a false positive

  //bf.print(); //Uncomment to see the bitset.

    return 0;
}
  
