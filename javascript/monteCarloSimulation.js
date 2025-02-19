function monteCarloSimulation(iterations, simulationFunction) {
  let successes = 0;

  for(let i = 0; i < iterations; i++) {
    const result = simulationFunction();
    if(result) {
      successes++;
    }
  }
  return successes / iterations;
}


// estimating pi
function piSimulation() {
  const x = Math.random();
  const y = Math.random();

  if(x * x + y * y <= 1) {
    return true;
  } else {
    return false;
  }
}
const piEstimate = monteCarloSimulation(100000, piSimulation);
const estimatedPi = piEstimate * 4;
console.log("estimated pi:", estimatedPi);

// rolling 2 dice, prob of sum being 7
function diceSimulation() {
  const die1 = Math.floor(Math.random() * 6) + 1;
  const die2 = Math.floor(Math.random() * 6) + 1;

  if(die1 + die2 === 7) {
    return true;
  } else {
    return false;
  }
}

const sevenProbability = monteCarloSimulation(100000, diceSimulation);
console.log("probabiliy of rolling a 7:", sevenProbability);

// buffon's needle
function buffonNeedleSimulation(needleLength) {
  const x = Math.random() * Math.PI;
  const y = Math.random();

  const end1 = y + (needleLength / 2) * Math.sin(x);
  const end2 = y - (needleLength / 2) * Math.sin(x);

  if(end1 >= 1 || end2 <= 0) {
    return true;
  } else {
    return false;
  }
}

const buffonPiEstimate = monteCarloSimulation(100000, () => buffonNeedleSimulation(0.5));
const buffonEstimatedPi = 2 / buffonPiEstimate;
console.log("buffon's needle pi estimate:", buffonEstimatedPi);

// ex 4
function generalSimulation(iterations, simulationFunction, ...args) {
  let successes = 0;
  for(let i = 0; i < iterations; i++) {
    const result = simulationFunction(...args);
    if(result) {
      sucesses++;
    }
  }
  return successes / iterations;
}

function coinFlipSimulation(bias) {
  return Math.random() < bias;
}

const biasedCoinFlipProbability = generalSimulation(1000, coinFlipSimulation, 0.7);
console.log("biased coin flip:", biasedCoinFlipProbability);
