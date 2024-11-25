import java.util.Random;

public class MonteCarloSimulation
  {
    private Random random = new Random();

    public double simulate(int numTrials, SimulationFunction function)
    {
      double total = 0;
      for(int i = 0; i < numTrials; i++)
        total += function.simulate();
      return total/numTrials;
    }
    public interface SimulationFunction
      {
        double simulate();
      }
    public class PiSiumulation implements MonteCarloSimulation.SimulationFunction
      {
        @Override
        public double simulate()
        {
          double x = random.nextDouble() * 2 - 1;
          double y = random.nextDouble() * 2 - 1;
          return x * x + y * y <= 1 ? 1: 0;
        }
      }

    public static void main(String[] args)
    {
      MonteCarloSimulation simulation = new MonteCarloSimulation();
      PiSimulation piSimulation = new PiSimulation();
      double piEstimate = simulation.simulate(100000, piSimulation) * 4;
      System.out.println("Estimated pi: " + piEstimate);
    }
  }
