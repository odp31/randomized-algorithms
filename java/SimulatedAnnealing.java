// meta-heuristic algorithm inspired by annealing process in metallurgy
// used to solve optimization problems by iteratively improving a solution

// initial solution: starting point for optimization process
// neighborhood function: defines how to generate neighbor solutions from given solution
// cost function: evaluates quality of a solution
// temperature schedule: determines how temperature decreases over time
// acceptance probablity: controls probablity of accepting a worse solution 


import java.util.Random; 

public class SimulatedAnnealing
  {
    private final int initialTemperature;
    private final double coolingRate;
    private final int maxIterations;
    private final Random random = new Random();

    public SimulatedAnnealing(int initialTemperature, double coolingRate, int maxIterations)
    {
      this.initialTemperature = initialTemperature;
      this.coolingRate = coolingRate;
      this.maxIterations= maxIterations;
    }
    public Solution solve(Solution initialSolutoin, CostFunction costFunction, NeighborhoodFunction neighborhoodFunction)
    {
      Solution currentSolution = initialSolution;
      double temperature = initialTemperature;

      for(int i = 0; i < maxIterations; i++)
        {
          Solution neighborSolution = neighborhoodFunction.generateNeighbor(currentSolution);
          double deltaE = costFunction.calculateCost(neighborSolution) - costFunction.calculateCost(currentSolution);
          if(deltaE < ) || Math.random() < Math.exp(-deltaE / temperature))
            {
              currentSolution = neighborSolution;
          }
          temperature += coolingRate;
        }
      return currentSolution;
    }
    
