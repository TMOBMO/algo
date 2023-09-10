#include <string>
#include <vector>

using namespace std;

vector<int> solution(string command) {
  int dirY[] = { 1, 0, -1, 0 };
  int dirX[] = { 0, 1, 0, -1 };
  int cy = 0, cx = 0;
  int dir = 0, i = 0;

  while (i < command.size()) {
    switch (command[i++]) {
    case 'R':
      dir = (dir + 1) % 4;
      break;
    case 'L':
      dir = (dir + 3) % 4;
      break;
    case 'G':
      cy += dirY[dir % 4];
      cx += dirX[dir % 4];
      break;
    case 'B':
      cy -= dirY[dir % 4];
      cx -= dirX[dir % 4];
      break;
    }
  }
  return { cx, cy };
}