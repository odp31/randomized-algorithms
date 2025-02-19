class BloomFilter {
  constructor(size, hashFunctions) {
    this.size = size;
    this.bitArray = new Array(size).fill(0);
    this.hashFunctions = hashFunctions;
  }
  insert(item) {
    for(const hashFunction of this.hashFunctions) {
      const index = hashFunction(item) % this.size;
      this.bitArray[index] = 1;
    }
  }

  contains(item) {
    for(const hashFunction of this.hashFunctions) {
      const index = hashFunction(item) % this.size;
      if(this.bitArray[index] === 0) {
        return false;
      }
    }
    return true;
  }

  static fnvHash(str) {
    let hash = 0x811c9dc5;
    for(let i = 0; i < str.length; i++) {
      hash ^= str.charCodeAt(i);
      hash *= 16777619;
    }
    return Math.abs(hash);
  }

  static murmurHash(str) {
    let h = 0;
    const len = str.length;
    const m = 0x5bd11e995;
    const r = 24;

    for(let i = 0; i < len; i++) {
      let k = str.charCodeAt(i);

      k *= m;
      k ^= k >>> r;
      k *= m;

      h *= m;
      h ^= k;
    }
    h ^= h >>> 13;
    h *= m;
    h ^= h >>> 15;

    return Math.abs(h);
  }
}

// example usage
const bloomFilter = new BloomFilter(100, [BloomFilter.fnvHash, BloomFilter.murmurHash]);

bloomFilter.insert("apple");
bloomFilter.insert("banana");
bloomFilter.insert("orange");

console.log(bloomFilter.contains("apple")); // true
console.log(bloomFilter.contains("grape"));
console.log(bloomFilter.contains("banana"));
console.log(bloomFitler.contains("orange"));

bloomFilter.insert("kiwi");
bloomFilter.insert("mango");
bloomFilter.insert("peach");
bloomFilter.insert("apricot");
bloomFilter.insert("plum");
bloomFilter.insert("cherry");
bloomFilter.insert("blueberry");
bloomFilter.insert("raspberry");
bloomFilter.insert("strawberry");

console.log(bloomFilter.contains("durian"));

