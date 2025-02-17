#include <iostream>
#include <random>
#include <cmath>
#include <iomanip>

using namespace std;

//ex 1: estimating pi
double estimatePi(int numSamples) {
  random_device rd;    // obtain random seed from OS
  mt19937 gen(rd());    // standard mersenne_twister_engine seeded with rd()
  uniform_real_distribution<> distrib(0.0,1.0);    // define range for x and y
  int insideCircle = 0;

  for(int i = 0; i < numSamples; ++i) {
    double x = distrib(gen);
    double y = distrib(gen);

    if(x * x + y * y <= 1.0) {
      insideCircle++;
    }
  }
  return 4.0 * insideCircle / numSamples;
}

// ex2: simulating dice roll
int rollDice(){
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> distributor(1,6);
  return distrib(gen);
}


//ex 3: simulating stock price movement
double simulateStockPrice(double initialPrice, double volatility, int numDays) {
  random_device rd;
  mt19937 gen(rd());
  normal_distribution<> distrib(0.0, volatility);

  double price = initialPrice;
  for(int i = 0; i < numDays; ++i) {
    double dailyReturn = distrib(gen);
    price = price * (1 + dailyReturn);
  }
  return price;
}

int main() {
  int numSamplesPi = 1000000;
  double estimatedPi = estimatePi(numSamplesPi);
  cout << "estimated pi using" << numSamplesPi << "samples" << fixed << setprecision(6) << estimatedPi << endl;

  // simulate dice rolls
  int numRolls = 10;
  cout << "\nDice Rolls:" << endl;
  for(int i = 0; i < numRolls; ++i) {
    cout << rollDice() << " ";
  }
  cout << endl;

  //simulating stock price
  double initialPrice = 100.0;
  double volatility = 0.01;
  int numDays = 365;
  double finalPrice = simulateStockPrice(initialPrice, volatility, numDays);
  cout << "\nSimulated Stock Price after " << numDays << " days:" << fixed << setprecision(2) << finalPrice << endl;
  return 0;
}

