// technique used to select a random sample of k items from a stream of n items where n is unknown or very large
// particularly useful in scenarios where its impractical to store all items in memory 

import java.util.Random;

public class ReservoirSampling {
  public static void reservoirSample(int[] stream, int k) {
    int[] reservoir = new int[k];
    Random rand = new Random();

    // fill reservoir with first k items
    for(int i = 0; i < k; i++) {
      reservoir[i] = stream[i];
    }
    // process remaining items
    for(int i = k; i < stream.length; i++) {
      int j = rand.nextInt(i + 1);
      if(j < k) {
        reservoir[j] = stream[i];
      }
    }
    // print sampled items
    for(int item : reservoir) {
      System.out.print(item + " ");
    }
  }
  public static void main(String[] args)
  {
    int[] stream = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int k = 3;
    reservoirSample(stream, k);
  }
}
