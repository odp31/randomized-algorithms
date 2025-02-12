#include <stdio.h>
#include <stdlib.h>
#include <limits.h>       // for int_max

// structure to represent an edge
typedef struct {
  int u;
  int v;
} Edge;

// function to perform random contraction
int contract(int num_vertices, Edge *edges, int num_edges, int *parent) {
  int random_edge_index = rand() % num_edges;
  Edge chosen_edge = edges[random_edge_index];
  int u_parent = parent[chosen_edge.u];
  int v_parent = parent[chosen_edge.v];

  if(u_parent != v_parent) {
    for(int i = 0; i < num_vertices; i++) {
      if(parent[i] == v_parent) {
        parent[i] = u_parent;        // merge groups
      }
    }
    return 1;
  }
  return 0;
}

// function to count num edges between 2 groups represented by parent array
int count_cut_edges(int num_vertices, Edge *edges, int num_edges, int *parent) {
  int cut_edges = 0;
  for(int i = 0; i < num_edges; i++) {
    if(parent[edges[i].u] != parent[edges[i].v]) {
      cut_edges++;
    }
  }
  return cut_edges;
}

// karger's algorithm for min-cut
int karger_min_cut(int num_vertices, Edge *edges, int num_edges) {
  int min_cut = INT_MAX;
  for(int i = 0; i < num_vertices * num_vertices * (int)(log(num_vertices)+1); i++) {
    int *parent = (int *)malloc(sizeof(int) * num_vertices);
    if(parent == NULL) {
      perror("memory allocation failed");
      exit(EXIT_FAILURE);
    }
    // initialize parent array
    for(int j = 0; j < num_vertices; j++) {
      parent[j] = j;
    }

    int current_num_vertices = num_vertices;
    int current_num_edges = num_edges;
    Edge *current_edges = (Edge*)malloc(sizeof(Edge) * num_edges);
    if(current_edges == NULL) {
      perror("memory allocation failed");
      free(parent);
      exit(EXIT_FAILURE);
    }
    for(int j = 0; j < num_edges; j++) {
      current_edges[j] = edges[j];
    }
    while(current_num_vertices > 2) {
      current_num_edges -= contract(current_num_vertices, current_edges, current_num_edges, parent);
      current_num_vertices --;
    }
    int cut = count_cut_edges(num_vertices, current_edges, num_edges, parent);
    if(cut < min_cut) {
      min_cut = cut;
    }
    free(current_edges);
    free(parent);
  }
  return min_cut;
}

int main() {
  srand(time(NULL));

  // example graph
  int num_vertices = 4;
  Edge edges[] = {{0, 1}, {0, 2}, {1, 2}, {1, 3}, {2, 3}};
  int num_edges = sizeof(edges) / sizeof(edges[0]);

  int min_cut = karger_min_cut(num_vertices, edges, num_edges);
  printf("minimum cut: %d\n", min_cut);
  return 0;
}

    
    
