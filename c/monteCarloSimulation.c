#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// function for monte carlo simulation 
double monteCarloSimulation(int iterations, int (*simulationFunction)(void*), void* args) {
  int successes = 0;
  for(int i = 0; i < iterations; i++) {
    if(simulationFunction(args)) {
      successes++;
    }
  }
  return (double)successes / iterations;
}

// estimate pi
int piSimulation(void* args) {
  double x = (double)rand() / RAND_MAX;
  double y = (double)rand() / RAND_MAX;

  if(x * x + y * y <= 1) {
    return 1;
  }
  else {
    return 0;
  }
}

// rolling 2 dice
int diceSimulation(void* args) {
  int die1 = rand() % 6 + 1;
  int die2 = rand() % 6 + 1;

  if(die1 + die2 == 7) {
    return 1;
  } else {
    return 0;
  }
}

// buffon's needle
struct BuffonArgs {
  double needleLength;
};

int buffonNeedleSimulation(void* args) {
  struct BuffonArgs* buffonArgs = (struct BuffonArgs*)args;
  double needleLength = buffonArgs->needleLength;

  double x = (double)rand() / RAND_MAX * M_PI;
  double y = (double)rand() / RAND_MAX;

  double end1 = y + (needleLength / 2) * sin(x);
  double end2 = y - (needleLength / 2) * sin(x);

  if(end1 >= 1 || end2 <= 0) {
    return 1;
  } else {
    return 0;
  }
}

// general simulation with parameters
struct CoinFlipArgs {
  double bias;
};

int coinFlipSimulation(void* args) {
  struct CoinFlipArgs* coinArgs = (struct CoinFlipArgs*)args;
  double bias = coinArgs->bias;

  double randomValue = (double)rand() / RAND_MAX;
  return (randomValue < bias) ? 1 : 0;
}

int main() {
  srand(time(NULL));

  // estimating pi  
  double piEstimate = monteCarloSimulation(100000, piSimulation, NULL);
  double estimatedPi = piEstimate * 4;
  printf("estimated pi: %f\n", estimatedPi);

  // rolling 2 dice
  double sevenProbability = monteCarloSimulation(100000, diceSimulation, NULL);
  printf("probability of rolling a 7: %f\n", sevenProbability);

  // buffon's needle
  struct BuffonArgs buffonArgs;
  buffonArgs.needleLength = 0.5;
  double buffonPiEstimate = monteCarloSimulation(100000, buffonNeedleSimulation, &buffonArgs);
  double buffonEstimatedPi = 2.0 / buffonPiEstimate;
  printf("buffon's needle pi estimate: %f\n", buffonEstimatedPi);

  // coin flip with bias
  struct CoinFlipArgs coinArgs;
  coinArgs.bias = 0.7;
  double biasedCoinFlipProbability = monteCarloSimulation(10000, coinFlipSimulation, &coinArgs);
  printf("biased coin flip probability: %f\n", biasedCoinFlipProbability);

  return 0;
}
