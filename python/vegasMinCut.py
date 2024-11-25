# min cut in an undirected graph is a set of edges whose removal disconnects the graph into 
# two or more components, and the number of edges in the cut is minimized

# Karger's algorithm is a randomzied algorithm that repeatedly contracts edges in a graph 
# until only 2 vertices remain; the edges between these 2 vertices form a cut 

import random
def contract(graph):
  """ contracts a random edge in the graph"""
  edge = random.choice(list(graph.items()))
  u, v = edge
  graph.pop(u)
  graph.pop(v)
  new_node = f"{u}, {v}"
  graph[new_node] = set()
  for neighbor, edges in graph.items():
    if u in edges:
      edges.remove(u)
      edges.add(new_node)
    if v in edges:
      edges.remove(v)
      edges.add(new_node)

def min_cut(graph):
  while len(graph) > 2:
    contract(graph)
  return len(list(graph.values())[0])

# Example usage
graph = {
  'A': {'B', 'C'},
  'B': {'A', 'C', 'D'},
  'C': {'A', 'B', 'D', 'E'},
  'D': {'B', 'C', 'E', 'F'},
  'E': {'C', 'D', 'F'},
  'F': {'D', 'E'}
}

min_cut_size = repeated_min_cut(graph, 100)
print("min cut size", min_cut_size)


