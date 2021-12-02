#include <fstream>
#include <iostream>
#include <vector>

int getIncrease(std::vector<int> &vec) {
  int counter = 0;
  for (auto i = 0; i < vec.size() - 1; i++)
    if (vec.at(i) < vec.at(i + 1))
      ++counter;
  return counter;
}

int windowIncrease(std::vector<int> &vec) {
  std::vector<int> sums;
  for (auto i = 0; i < vec.size() - 2; ++i) {
    auto val = vec[i] + vec[i + 1] + vec[i + 2];
    sums.push_back(val);
  }
  return getIncrease(sums);
}

int main() {
  std::vector<int> vec;
  std::fstream inFile("input");
  while (inFile) {
    int val;
    if (!(inFile >> val))
      break;
    vec.push_back(val);
  }
  inFile.close();
  std::cout << getIncrease(vec) << "\n";
  std::cout << windowIncrease(vec) << "\n";
  return 0;
}
