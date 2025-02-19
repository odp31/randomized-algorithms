#include <iostream>
#include <vector>
#include <random>
#include <algorithm> // for std::copy


std::vector<int> reservoirSampling(const std::vector<int>& stream, int k) {
  if(k <= 0 || stream.empty()) {
    return {};
  }
  int n = stream.size();
  k = std::min(k, n);

  std::vector<int> reservoir(k);
  std::copy(stream.begin(), stream.begin() + k, reservoir.begin());

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(0, k - 1);

  for(int i = k; i < n; i++) {
    std::uniform_int_distribution<> replaceDist(0, i);
    int j = replaceDist(gen);

    if(j < k) {
      reservoir[distrib(gen)] = stream[i];
    }
  }
  return reservoir;
}

// example usage
int main() {
  std::vector<int> stream = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  int k = 5;

  std::vector<int> sample = reservoirSampling(stream, k);
  std::cout << "sample: ";
  for(int val : sample) {
    std::cout << val << " ";
  }
  std::cout << val << " ";
}
std::cout << std::endl;

// example with larger k than stream size 
k = 10; 
sample = reservoirSampling(stream, k);
std::cout << "sample(k > stream size): ";
for(int val : sample) {
  std::cout << val << " ";
}
std::cout << std::endl;

// example with empty stream
std::vector<int> emptyStream;
k = 5; 
sample = reservoirSampling(emptyStream, k);
std::cout<< "sample(empty stream): ";
for(int val : sample) {
  std::cout << val << " ";
}
std::cout << std::endl;

// example with k = 0
k = 0;
sample = reservoirSampling(stream, k);
std::cout << "sample (k = 0):";
for(int val : sample) {
  std::cout << val << " ";
}
std::cout << std::endl;
return 0;
}
