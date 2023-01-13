#include <iostream>
#include <regex>
#include <vector>
#include <string>

using namespace std;

int H, W;

int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };
char dir[] = { '>', 'v', '<', '^' };

bool valid(int y, int x) {
  return 0 <= x && x < W && 0 <= y && y < H;
}

char checkStart(vector<string>& board, int y, int x) {
  if (!valid(y, x)) return false;
  if (board[y][x] != '#') return false;

  char d = 0;
  for (int i = 0; i < 4; ++i) {
    int ty = y + dy[i];
    int tx = x + dx[i];

    if (valid(ty, tx) && board[ty][tx] == '#') {
      if (d)
        return 0;
      d = dir[i];
    }
  }

  return d;
}

int dirIndex(char d) {
  for (int i = 0; i < 4; ++i)
    if (d == dir[i]) return i;
  return -1;
}

char turnDir(char cur, char next) {
  if (cur == next) return 0;
  if ((dirIndex(cur) + 1) % 4 == dirIndex(next)) return 'R';
  return 'L';
}

int main() {
  cin >> H >> W;
  vector<string> board(H);
  for (int i = 0; i < H; ++i)
    cin >> board[i];

  // find start
  char d = 0;
  int y, x;
  int total = 0;
  for (int i = 0; i < H; ++i) {
    for (int j = 0; j < W; ++j) {
      if (board[i][j] == '#')
        ++total;

      if (d) continue;

      d = checkStart(board, i, j);
      if (d) {
        y = i;
        x = j;
      }
    }
  }

  cout << y + 1 << " " << x + 1 << "\n";
  cout << d << "\n";

  string ans = "";
  board[y][x] = '@';
  --total;
  while (total) {
    int i = dirIndex(d);
    ans += 'A';

    for (int j = 0; j < 2; ++j) {
      y = y + dy[i];
      x = x + dx[i];
      board[y][x] = '@';
      --total;
    }

    for (i = 0; i < 4; ++i) {
      int ty = y + dy[i];
      int tx = x + dx[i];

      if (valid(ty, tx) && board[ty][tx] == '#') {
        char turn = turnDir(d, dir[i]);
        if (turn) ans += turn;
        d = dir[i];
        break;
      }
    }
  }

  cout << ans << "\n";
  return 0;
}