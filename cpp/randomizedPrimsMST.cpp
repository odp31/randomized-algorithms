#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

struct Edge {
  int u,v, weight;
};

// comparison function for sorting edges by weight
bool compareEdges(const Edge& a, const Edge& b) {
  return a.weight < b.weight;
}

// function to find parent node in disjoint set
int find(vector<int>& parent, int i) {
  if(parent[i] == i)
    return i;
  return parent[i] = find(parent, parent[i]);
}

// function to perform union of two sets
void unite(vector<int>& parent, vector<int>& rank, int x, int y) {
  int xroot = find(parent, x);
  int yroot = find(parent, y);

  if(xroot != yroot) {
    if(rank[xroot] < rank[yroot])
      parent[xroot] = yroot;
    else if(rank[xroot] > rank[yroot])
      parent[yroot] = xroot;
    else {
      parent[yroot] = xroot;
      rank[xroot]++;
    }
  }
}

vector<Edge> randomizedPrimsMST(int numVertices, vector<Edge>& edges) {
  vector<Edge> mst;


  // shuffle edges randomly
  random_device rd;
  mt19937 g(rd());
  shuffle(edges.begin(), edges.end(), g);

  // initialize disjoint sets
  vector<int> parent(numVertices);
  vector<int> rank(numVertices, 0);
  for(int i = 0; i < numVertices; ++i) {
    parent[i] = i;
  }

  // iterate through shuffled edges
  for(const Edge& edge: edges) {
    int u = edge.u;
    int v = edge.v;
    int weight = edge.weight;

    if(find(parent, u) != find(parent, v)) {
      mst.push_back(edge);
      unite(parent, rank, u, v);
    }
  }
  return mst;
}

int main() {
  int numVertices = 6;
  vector<Edge> edges = {
{0,1,4},{0,2,2},{1,2,1},{1,3,5},{2,3,8},{2,4,10},{3,4,6},{3,5,5},{4,5,3}
};
  vector<Edge> mst = randomizedPrimsMST(numVertices, edges);

  cout << "min spanning tree:" << endl;
  for(const Edge& edge : mst) {
    cout << edge.u << "-" << edge.v << ":" << edge.weight << endl;
  }
  return 0;
}
