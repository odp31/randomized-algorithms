#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>


// structure to represent an edge
typedef struct {
  int u;
  int v;
  int weight;
} Edge;


// function to swap 2 edges
void swap_edge(Edge *a, Edge *b) {
  Edge temp = *a;
  *a = *b;
  *b = temp;
}

// function to find minimum edge crossing the cut (using linear search)
Edge find_min_edge(Edge *edges, int num_edges, int *included) {
  Edge min_edge = {-1, -1, INT_MAX};
  for(int i = 0; i < num_edges; i++) {
    if((included[edges[i].u] && !included[edges[i].v]) || (!included[edges[i].u] && included[edges[i].v])) {
      if(edges[i].weight < min_edge.weight) {
        min_edge = edges[i];
      }
    }
  }
  return min_edge;
}

// randomzied Prim's algoritm for MST
Edge* randomized_prims_mst(int num_vertices, Edge *edges, int num_edges, int* mst_size) {
  srand(time(NULL));
  int *included = (int *)calloc(num_vertices, sizeof(int));
  if(included == NULL) {
    perror("memory allocation failed");
    exit(EXIT_FAILURE);
  }
  Edge *mst = (Edge *)malloc(sizeof(Edge) * (num_vertices - 1));
  if(mst == NULL) {
    perror("memory allocation failed");
    free(included);
    exit(EXIT_FAILURE);
  }
  // start with a random vertex
  int start_vertex = rand() % num_vertices;
  included[start_vertex] = 1;

  *mst_size = 0;        // initialize MST size
  for(int i = 0; i < num_vertices - 1; i++) {
    Edge min_edge = find_min_edge(edges, num_edges, included);
    if(min_edge.weight == INT_MAX) {
      free(mst);
      free(included);
      return NULL;
    }
    mst[*mst_size] = min_edge;
    (*mst_size)++;

    if(!included[min_edge.u]) {
      included[min_edge.u] = 1;
    } else {
      included[min_edge.v] = 1;
    }
  }
  free(included);
  return mst;
}


int main() {
  // example graph
  int num_vertices = 5;
  Edge edges[] = {
        {0, 1, 4}, {0, 2, 2}, {1, 2, 1}, {1, 3, 5}, {2, 3, 8}, {2, 4, 10}, {3, 4, 6}
    };
  int num_edges = sizeof(edges) / sizeof(edges[0]);
  int mst_size = 0;

  Edge* mst = randomized_prims_mst(num_vertices, edges, num_edges, &mst_size);

  if(mst != NULL) {
    printf("minimum spanning tree: \n");
    for(int i = 0; i < mst_size; i++) {
      printf("(%d, %d) - Weight: %d\n", mst[i].u, mst[i].v, mst[i].weight);
    }
    free(mst);
  } else {
    printf("no mst found (graph might be disconnected) \n");
  }
  return 0;
}
