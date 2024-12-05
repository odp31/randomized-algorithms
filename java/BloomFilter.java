// probabilistic data structure that tells you if an element is probably in a set
// space efficient but can produce false positives 

import java.util.BitSet;

public class BloomFilter {
  private BitSet bitSet;
  private int numHashFunctions;

  public BloomFilter(int expectedElements, double falsePositiveProbability) {
    int m = (int) (-expectedElements * Math.log(falsePositiveProbability) / Math.pow(Math.log(2), 2));
    numHashFunctions = (int) (Math.log(2) * m / expectedElements);
    bitSet = new BitSet(m);
  }
  public void add(String element) {
    for(int i = 0; i < numHashFunctions; i++) {
      int hash = hashFunction(element, i) % bitSet.size();
      bitSet.set(hash);
    }
  }
  public boolean mightContain(String element) {
    for(int i = 0; i < numHashFunctions; i++) {
      int hash = hashFunction(element, i) % bitSet.size();
      if(!bitSet.get(hash)) {
        return false;
      }
    }
    return true;
  }
  private int hashFunction(String element, int i) {
    int hash = 0;
    for(char c : element.toCharArray()) {
      hash = 31 * hash + c;
    }
    return hash + i;
  }
}
