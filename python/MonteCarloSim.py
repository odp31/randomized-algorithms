# computational technique that uses random sampling to obtain numerical results
# particularly useful for problems that are difficult to solve analytically or computaitonally expensive

import random
import math

def estimate_pi(num_points):
  num_points_in_circle = 0
  for i in range(num_points):
    x = random.uniform(-1, 1)
    y = random.uniform(-1, 1)
    distance = x**2 + y**2
    if distance <= 1:
      num_points_in_circle += 1
  pi_estimate = 4 * num_points_in_circle / num_points
  return pi_estimate 

if __name__ == "__main__":
  num_points = 1000000
  pi_approx = estimate_pi(num_points)
  print("estimated pi: ", pi_approx)
