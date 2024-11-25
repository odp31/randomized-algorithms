import random 

def randomized_prims_mst(graph):
  "" finds MST of weighted undirected graph using randomized Prims algorithm """
  mst = []
  visited = set()
  remaining_vertices = set(graph.keys())
  start_vertex = random.choice(list(remaining_vertices))
  visited.add(start_vertex)
  remaining_vertices.remove(start_vertex)

  while remaining_vertices:
    edge_candidates = []
    for v in visited:
      for neighbor, weight in graph[v].items():
        if neighbor not in visited:
          edge_candidates.append((v, neighbor, weight))


  # randomly select edge from candidates
  random.shuffle(edge_candidates)
  min_edge = min(edge_candidates, key=lambda x: x[2])
  mst.append(min_edge)
  visited.add(min_edge[1])
  remaining_vertices.remove(min_edge[1])

return mst

# example usage 
graph = {
    'A': {'B': 2, 'C': 4},
    'B': {'A': 2, 'C': 3, 'D': 8},
    'C': {'A': 4, 'B': 3, 'D': 5, 'E': 6},
    'D': {'B': 8, 'C': 5, 'E': 7},
    'E': {'C': 6, 'D': 7}
}
mst = randomized_prims_mst(graph)
print(mst) 
