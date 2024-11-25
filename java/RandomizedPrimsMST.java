import java.util.*;

public class RandomizedPrimsMST
  {
    static class Edge
      {
        int src, dest, weight;
        public Edge(int src, int dest, int weight)
        {
          this.src = src;
          this.dest = dest;
          this.weight = weight;
        }
      }
    static class Graph
      {
        int V, E;
        Edge edge[];

        Graph(int v, int e)
        {
          V = v;
          E = e;
          edge = new Edge[E];
          for(int i = 0; i < e; i++)
            edge[i] = new Edge(0, 0, 0);
        }
      }
    static class MinHeapNode
      {
        int v;
        int key;
        public MinHeapNode(int v, int key)
        {
          this.v = v;
          this.key = key;
        }
      }
    static class MinHeap
      {
        int capacity;
        int size;
        int[] pos;
        MinHeapNode[] array;
        public MinHeap(int capacity)
        {
          this.capacity = capacity;
          size = 0;
          pos = new int[capacity];
          array = new MinHeapNode[capacity];
        }
        // functions to heapify heap
        void minHeapify(int idx)
        {
          int smallest = idx;
          int left = 2 * idx + 1;
          int right = 2 * idx + 2;
          if(left < size && array[left].key < array[smallest].key)
            smallest = left;
          if(right < size && array[right].key < array[smallest].key)
            smallest = right;
          if(smallest != idx)
          {
            MinHeapNode smallestNode = array[smallest];
            MinHeapNode idxNode = array[idx];
            pos[smallestNode.v] = idx;
            pos[idxNode.v] = smallest;
            swapMinHeapNode(smallest, idx);
            minHeapify(smallest);
          }
        }
        void swapMinHeapNode(int a, int b)
        {
          MinHeapNode t = array[a];
          array[a] = array[b];
          array[b] = t;
        }
        void decreaseKey(int v, int key)
        {
          int i = pos[v];
          array[i].key = key;
          while(i > 0 && array[i].key < array[(i - 1) / 2].key)
            {
              pos[array[i].v] = (i - 1) / 2;
              pos[array[(i - 1) / 2].v] = i;
              swapMinHeapNode(i, (i - 1) / 2);
              i = (i - 1) / 2;
            }
        }
        MinHeapNode extractMin()
        {
          if(size <= 0)
            return null;
          if(size == 1) {
            size --;
            pos[array[0].v] = -1;
            return array[0];
          }
          MinHeapNode root = array[0];
          MinHeapNode lastNode = array[size - 1];
          array[0] = lastNode;
          // update position of last node
          pos[lastNode.v] = 0;
          pos[root.v] = -1;
          size--;
          minHeapify(0);
          return root;
        }
        Boolean isEmpty()
        {
          return size == 0;
        }
        Boolean isInMinHeap(int v)
        {
          return pos[v] < size;
        }
      }
    void primMST(Graph graph)
    {
      int V = graph.V; 
      int E = graph.E;
      int parent[] = new int[V];
      int key[] = new int[V];

      // create minheap with initial key value as infintie for all vertices
      MinHeap minHeap = new MinHeap(V);
      // initialize all keys to infinite
      for(int i = 0; i < V; i++)
        {
          key[i] = Integer.MAX_VALUE;
          minHeap.array[i] = new MinHeapNode(i, key[i]);
          minHeap.pos[i] = i;
        }
      // make key 0 so that vertex is picked as first vertex
      key[0] = 0;
      minHeap.decreaseKey(0, key[0]);
      // extract vertices one by one form min heap
      while (!minHeap.isEmpty())
        {
          MinHeapNode minHeapNode = minHeap.extractMin();
          int u = minHeapNode.v;
          for(Edge edge : graph.edge)
            {
              int v = edge.dest;
              if(minHeap.isInMinHeap(v) && edge.weight <  key[v])
              {
                key[v] = edge.weight;
                parent[v] = u;
                minHeap.decreaseKey(v, key[v]);
              }
            }
        }
      printMST(parent, graph.V, graph.edge);
    }
    // utility function to print constructed MST stored in parent
    void printMST(int parent[], int n, Edge edge[])
    {
      System.out.println("Edge \tWeight");
      for(int i = 1; i < n; i++)
        System.out.println(parent[i] + " - " + i + "\t" + edge[i].weight);
    }

    public static void main(String[] args)
    {
      int V = 9, E = 14; 
      Graph graph = new Graph(V, E);
      // Add edge 0-1
        graph.edge[0].src = 0;
        graph.edge[0].dest = 1;
        graph.edge[0].weight = 4;

        // Add edge 0-7
        graph.edge[1].src = 0;
        graph.edge[1].dest   
 = 7;
        graph.edge[1].weight = 8;

        // Add edge 1-2
        graph.edge[2].src = 1;
        graph.edge[2].dest = 2;
        graph.edge[2].weight = 8;

        // Add edge 1-7
        graph.edge[3].src = 1;
        graph.edge[3].dest = 7;
        graph.edge[3].weight = 11;

        // Add edge 2-3
        graph.edge[4].src = 2;
        graph.edge[4].dest = 3;
        graph.edge[4].weight = 7;

        // Add edge 2-8
        graph.edge[5].src = 2;
        graph.edge[5].dest = 8;
        graph.edge[5].weight = 2;

        // Add edge 2-5
        graph.edge[6].src = 2;
        graph.edge[6].dest = 5;
        graph.edge[6].weight = 4;

        // Add edge 3-4
        graph.edge[7].src = 3;
        graph.edge[7].dest = 4;
        graph.edge[7].weight = 9;

        // Add edge 3-5
        graph.edge[8].src = 3;
        graph.edge[8].dest = 5;
        graph.edge[8].weight = 2
      
