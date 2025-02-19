function randomizedPrimsMST(graph) {
  const numVertices = graph.length;
  const mst = [];
  const visited = new Array(numVertices).fill(false);
  const edges = [];

  // convert adjacency matrix to edge list 
  for(let i = 0; i < numVertices; i++) {
    for(let j = i + 1; j < numVertices; j++) {
      if(graph[i][j] !== Infinity) {
        edges.push([i, j, graph[i][j]]);
      }
    }
  }
  if(edges.length === 0) {
    return mst;
  }
  const startVertex = Math.floor(Math.random() * numVertices);
  visited[startVertex] = true;

  // add edges to mst until all vertices are visited
  while(mst.length < numVertices - 1) {
    const eligibleEdges = [];

    // find all edges connecting visited and unvisited vertices
    for(const edge of edges) {
      const u = edge[0];
      const v = edge[1];
      const weight = edge[2];

      if((visited[u] && !visited[v]) || (!visited[u] && visited[v])) {
        eligibleEdges.push(edge);
      }
    }
    if(eligibleEdges.length === 0) {
      return null;
    }
    // pick random edge from eligible edges
    const randomIndex = Math.floor(Math.random() * eligibleEdges.length);
    const chosenEdge = eligibleEdges[randomIndex];

    const u = chosenEdge[0];
    const v = chosenEdge[1];

    mst.push(chosenEdge);
    visited[u] = true;
    visited[v] = true;
  }
  return mst;
}


// Example usage (adjacency matrix representation):
const graph = [
  [0, 4, Infinity, Infinity, Infinity, Infinity, Infinity, 8, Infinity],
  [4, 0, 8, Infinity, Infinity, Infinity, Infinity, 11, Infinity],
  [Infinity, 8, 0, 7, Infinity, 4, Infinity, Infinity, 2],
  [Infinity, Infinity, 7, 0, 9, 14, Infinity, Infinity, Infinity],
  [Infinity, Infinity, Infinity, 9, 0, 10, Infinity, Infinity, Infinity],
  [Infinity, Infinity, 4, 14, 10, 0, 2, Infinity, Infinity],
  [Infinity, Infinity, Infinity, Infinity, Infinity, 2, 0, 1, 6],
  [8, 11, Infinity, Infinity, Infinity, Infinity, 1, 0, 7],
  [Infinity, Infinity, 2, Infinity, Infinity, Infinity, 6, 7, 0],
];

const mst = randomizedPrimsMST(graph);

if(mst) {
  console.log("minimum spanning tree: ");
  let totalWeight = 0;
  for(const edge of mst) {
    console.log('&{edge[0]} - ${edge[1]} (weight: ${edge[2]})');
    totalWeight += edge[2];
  }
  console.log("total weight: ", totalWeight);
} else {
  console.log("no mst found (graph might be disconnected)");
}

// example with disconnected graph 
const disconnectedGraph = [
  [0, 1, Infinity],
  [1, 0, Infinity],
  [Infinity, Infinity, 0]
  ];
const disconnectedMST = randomziedPrimsMST(disconnectedGraph);
if(disconnectedMST) {
  console.log("mst of disconnected graph:");
  for(const edge of disconnectedMST) {
    console.log('${edge[0]} - ${edge[1]} (weight: ${edge[2]})');
  }
} else {
  console.log("no mst found for disconnected graph");
}

// example with empty graph
const emptyGraph = [];
const emptyMST = randomizedPrimsMST(emptyGraph);
console.log("mst of empty graph:", emptyMST);
