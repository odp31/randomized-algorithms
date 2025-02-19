function simulatedAnnealing(initialSolution, costFunction, temperature, coolingRate, iterations) {
  let currentSolution = initialSolution;
  let currentCost = costFunction(currentSolution);
  let bestSolution = currentSolution;
  let bestCost = currentCost;

  for(let i = 0; i < iterations; i++) {
    temperature *= coolingRate;

    const neighborSolution = generateNeighbor(currentSolution);
    const neighborCost = costFunction(neighborSolution);

    const constDifference = neighborCost - currentCost;

    // acceptance prob based on metropolic criterion
    const acceptanceProbability = costDifference < 0 ? 1 : Math.exp(-costDifference / temperature);

    if(acceptanceProbability > Math.random()) {
      currentSolution = neighborSolution;
      currentCost = neighborCost;

      if(currentCost < bestCost) {
        bestSolution = currentSolution;
        bestCost = currentCost;
      }
    }
    if(temperature < 0.001) {
      break;
    }
  }
  return bestSolution;
}

// ex cost function
function tspCost(path) {
  const distances = {
    "A-B" : 10, "A-C": 15, "A-D": 20,
    "B-A" : 10, "B-C": 35, "B-D": 25,
    "C-A": 15, "C-B": 35, "C-D": 30,
    "D-A": 20, "D-B": 25, "D-C": 30
  };

  let cost = 0; 
  for(let i = 0; i < path.length - 1; i++) {
    const edge = path[i] + "-" + path[i+1];
    cost += distances[edge];
  }
  return cost;
}

// ex neighbor generation- traveling salesperson problem simplified
function generateNeighbor(path) {
  const newPath = [...path];
  const index1 = Math.floor(Math.random() * path.length);
  const index2 = Math.floor(Math.random() * path.length);
  [newPath[index1], newPath[index2]] = [newPath[index2], newPath[index1]];
  return newPath;
}

// example usage
const initialSolution = ["A", "B", "C", "D", "A"];
const temperature = 100;
const coolingRate = 0.99;
const iterations = 10000;

const bestPath = simulatedAnnealing(initialSolution, tspCost, temperature, coolingRate, iterations);

console.log("best path", bestPath);
console.log("cost of best path", tspCost(bestPath));

function simpleCost(x) {
  return x*x - 4*x + 5;
}
function simpleNeighbor(x) {
  const delta = (Math.random() - 0.5) * 2;
  return x + delta;
}

const initialX = 10;
const bestX = simulatedAnnealing(initialX, simpleCost, 100, 0.95, 5000);
console.log("best x:", bestX);
console.log("cost of best x:", simpleCost(bestX));
