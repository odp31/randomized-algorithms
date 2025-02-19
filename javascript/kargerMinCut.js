function kargetMinCut(graph) {
  const clonedGraph = JSON.parse(JSON.stringify(graph));

  let minCut = Infinity;

  // repeat contraction process to increase probability of finding it 
  for(let i = 0; i < Math.floor(graph.length * Math.log(graph.length)); i++) {
    let currentGraph = JSON.parse(JSON.stringify(clonedGraph));
    let numVertices = currentGraph.length;

    while(numVertices > 2) {
      const edge = pickRandomEdge(currentGraph);
      const u = edge[0];
      const v = edge[1];

      // merge u and v into single vertex
      currentGraph[u] = currentGraph[u].concat(currentGraph[v].filter(neighbor => neighbor !== v).map(neighbor => neighbor === u? u : neighbor));

      // update edges pointing to v to point to u
      for(let j = 0; j < currentGraph.length; j++) {
        currentGraph[j] = currentGraph[j].map(neighbor => neighbor === v ? u : neighbor);
      }
      // remove v
      currentGraph.splice(v, 1);
      numVertices--;
    }
    const cut = currentGraph[0].length;
    minCut = Math.min(minCut, cut);
  }
  return minCut;
}


function pickRandomEdge(graph) {
  const verticesWithEdges = [];
  for(let i = 0; i < graph.length; i++) {
    for(const neighbor of graph[i]) {
      verticesWithEdges.push([i, neighbor]);
    }
  }
  const randomIndex = Math.floor(Math.random() * verticesWithEdges.length);
  return verticesWithEdges[randomIndex];
}

// example graph 
const graph = [
  [1, 2],
  [0, 2, 3],
  [0, 1, 3, 4],
  [1, 2, 4],
  [2, 3]
  ];

const minCut = kargerMinCut(graph);
console.log("min cut:", minCut);

// example with self loops and parallel edges
const graph2 = [
  [1, 1, 2],
  [0, 2],
  [0, 1, 2]
  ];

const minCut2 = kargerMinCut(graph2);
console.log("min cut with self loops and parallel edges:", minCut2);

// example with disconnected nodes
const graph3 = [
  [1],
  [0],
  []
  ];
const minCut3 = kargerMinCut(graph3);
console.log("minimum cut(with disconnected nodes):", minCut3);
