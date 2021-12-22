#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int energyConsumption(std::vector<std::string> &lines) {
  int gamma = 0, epsilon = 0, binaryLen = lines.at(0).length();
  int half =
      (lines.size() % 2 == 0) ? lines.size() / 2 : (lines.size() / 2) + 1;

  for (int cPos = 0; cPos < binaryLen; ++cPos) {
    int ones = 0;
    for (int line = 0; line < lines.size(); ++line) {
      if (ones >= half) {
        gamma |= (1 << (binaryLen - cPos - 1));
        break;
      }
      if (lines.at(line).at(cPos) == '1')
        ones++;
    }
    if (ones < half)
      epsilon |= (1 << (binaryLen - cPos - 1));
  }
  return gamma * epsilon;
}

void filterLines(std::vector<std::string> &lines, int bitPos, bool common) {
  if (lines.size() <= 1)
    return;

  int ones = 0, half = (lines.size() % 2 == 0) ? lines.size() / 2
                                               : (lines.size() / 2) + 1;
  for (int line = 0; line < lines.size(); line++) {
    if (ones > half)
      break;
    if (lines.at(line).at(bitPos) == '1')
      ++ones;
  }
  if (ones >= half)
    lines.erase(std::remove_if(lines.begin(), lines.end(),
                               [common, bitPos](std::string x) {
                                 return common ? (x.at(bitPos) != '1')
                                               : (x.at(bitPos) != '0');
                               }),
                lines.end());
  else
    lines.erase(std::remove_if(lines.begin(), lines.end(),
                               [common, bitPos](std::string x) {
                                 return common ? (x.at(bitPos) != '0')
                                               : (x.at(bitPos) != '1');
                               }),
                lines.end());
  filterLines(lines, bitPos + 1, common);
}

int lifeSupplyRating(std::vector<std::string> lines) {
  int oxygen = 0, carbon = 0;
  std::vector<std::string> linesOxygen{lines}, linesCarbon{lines};

  filterLines(linesOxygen, 0, true);
  filterLines(linesCarbon, 0, false);

  oxygen = std::stoi(linesOxygen.at(0), nullptr, 2);
  carbon = std::stoi(linesCarbon.at(0), nullptr, 2);
  return oxygen * carbon;
}

int main() {
  std::ifstream inFile{"input"};
  std::vector<std::string> lines;

  while (inFile) {
    std::string line;
    if (!(inFile >> line))
      break;
    lines.emplace_back(line);
  }
  inFile.close();

  std::cout << "Power Consumption is " << energyConsumption(lines) << "\n";
  std::cout << "Life Supply Rating is: " << lifeSupplyRating(lines) << "\n";
}
