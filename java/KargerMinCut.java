// randomized algorithm that repeatedly contracts edges in a graph until only 2 vertices remain
// edges between these 2 form a cut
// by repeating multiple times we can find the minimum cut with high probability 

import java.util.*;

public class KargerMinCut
  {
    public static int minCut(Map<Integer, Set<Integer>> graph)
    {
      while(graph.size() > 2)
        {
          // choose a random edge
          int u = random.nextInt(graph.size());
          int v = random.nextInt(graph.size());
          while(v == u || !graph.get(u).contains(v))
            {
              u = random.nextInt(graph.size());
              v = random.nextInt(graph.size());
            }
          // merge u and v 
          graph.get(u).addAll(graph.get(v));
          graph.remove(v);
          for(int w : graph.get(u))
            {
              graph.get(w).remove(v);
              graph.get(w).add(u);
            }
        }
      // count edges in final cut
      return graph.values().iterator().next().size();
    }
    public static int repeatedMinCut(Map<Integer, Set<Integer>> graph, int iterations)
    {
      int minCut = Integer.MAX_VALUE;
      for(int i = 0; i < iterations; i++)
        {
          Map<Integer, Set<Integer>> copy = new HashMap<>(graph);
          int cutSize = minCut(copy);
          minCut = Math.min(minCut, cutSize);
        }
      return minCut;
    }
    public static void main(String[] args)
    {
      // example graph 
      Map<Integer, Set<Integer>> graph = new HashMap<>();
      graph.add({2, 3, 5,4654, 3});
      int minCutSize = repeatedMintCut(graph, 100);
      System.out.println("min cut size" + minCutSize);
    }
  }
