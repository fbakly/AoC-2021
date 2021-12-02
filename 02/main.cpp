#include <fstream>
#include <iostream>

struct Pos2D {
  int x;
  int y;
  int aim;
};

void processCommand(struct Pos2D &pos, std::string command, int val, bool p2) {
  if (!(command.compare("forward"))) {
    pos.x += val;
    if (p2)
      pos.y += (pos.aim * val);
  } else if (!(command.compare("up"))) {
    if (p2)
      pos.aim -= val;
    else
      pos.y -= val;
  } else if (!(command.compare("down"))) {
    if (p2)
      pos.aim += val;
    else
      pos.y += val;
  }
}

int main() {
  std::ifstream inFile("input");
  struct Pos2D pos, pos1{.x = 0, .y = 0, .aim = 0};
  std::string command;
  int val;

  while (inFile) {
    inFile >> command;
    if (!(inFile >> val))
      break;
    processCommand(pos, command, val, false);
    processCommand(pos1, command, val, true);
  }
  inFile.close();

  std::cout << pos.x * pos.y << "\n";
  std::cout << pos1.x * pos1.y << "\n";
  return 0;
}
