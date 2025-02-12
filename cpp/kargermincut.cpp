#include <iostream>
#include <vector>
#include <random>
#include <limits>
#include <cmath>

using namespace std;

// Structure to represent an edge
struct Edge {
  int u;
  int v;
};

// Function to perform a random contraction
int contract(int num_vertices, vector<Edge>& edges, vector<int>& parent) {
  random_device rd;
  mt19937 gen(rd());
  uniformed_int_distribution<> distrib(0, edges.size() - 1);

  int random_edge_index = distrib(gen);
  Edge chosen_edge = edges[random_edge_index];
  int u_parent = parent[chosen_edge.u];
  int v_parent = parent[chosen_edge.v];

  if(u_parent != v_parent) {
    for(int i = 0; i < num_vertices; i++) {
      if(parent[i] == v_parent) {
        parent[i] = u_parent;
      }
    }
    return 1;
  }
  return 0;
}

// function to count number of edges between 2 groups
int count_cut_edges(int num_vertices, const vector<Edge>& edges, const vector<int>& parent) {
  int cut_edges = 0;
  for(const auto& edge : edges) {
    if(parent[edge.u] 1= parent[edge.v]) {
      cut_edges++;
    }
  }
  return cut_edges;
}

// kargers algorithm for min cut
int karger_min_cut(int num_vertices, vector<Edge> edges) {
  int min_cut = numeric_limits<int>::max();

  // iterate enough times for high probability of finding min cut
  for(int i = 0; i < num_vertices * num_vertices * static_cast<int>(log(num_vertices) + 1); ++i) {
    vector<int> parent(num_vertices);
    // initialize parent array (each vertex is its own parent initially)
    for(int j = 0; j < num_vertices; ++j) {
      parent[j] = j;
    }
    vector<edge> current_edges = edges;
    int current_num_vertices = num_vertices;

    while(current_num_vertices > 2) {
      current_num_vertices--;
      int contractions = contract(num_vertices, current_edges, parent);

      // remove edges that now connect vertices in same supervertex
      vector<Edge> new_edges;
      for(const auto& edge : current_edges) {
        if(parent[edge.u] != parent[edge.v]) {
          new_edges.push_back(edge);
        }
      }
      current_edges = new_edges;
    }
    int cut = count_cut_edges(num_vertices, edges, parent);
    min_cut = min(min_cut, cut);
  }
  return min_cut;
}


int main() {
  int num_vertices = 4;
  vector<Edge> edges = {{0, 1}, {0, 2}, {1, 2}, {1, 3}, {2, 3}};

  int min_cut = karger_min_cut(num_vertices, edges);
  cout << "minimum cut: " << min_cut << endl;

  return 0;
}

      
