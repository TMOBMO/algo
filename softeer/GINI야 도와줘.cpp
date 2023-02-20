#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string.h>
#include <functional>

using namespace std;

using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

int R, C;
int dir[] = { -1, 0, 1, 0, -1 };
int ans;

vector<vector<char>> grid;
queue<pii> cur;
queue<pii> shower;

bool valid(int y, int x) {
  return 0 <= y && y < R && 0 <= x && x < C;
}

bool update(queue<pii> &que, std::function<bool(int a, int b)> f) {
  int K = que.size();
  for (int k = 0; k < K; ++k) {
    auto t = que.front(); que.pop();
    int cy = t.first;
    int cx = t.second;

    for (int i = 0; i < 4; ++i) {
      int ny = cy + dir[i];
      int nx = cx + dir[i + 1];
      if (!valid(ny, nx)) continue;
      if (f(ny, nx)) return true;
    }
  }
  return false;
}

int main() {
  cin >> R >> C;

  vector<vector<char>> board(R, vector<char>(C));
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      cin >> board[i][j];
      if (board[i][j] == 'W') {
        board[i][j] = 'C';
        cur.push({ i, j });
      }
      if (board[i][j] == '*')
        shower.push({ i, j });
    }
  }

  grid = board;

  auto shower_helper = [](int ny, int nx) {
    char next = grid[ny][nx];
    if (next == 'X' || next == '*' || next == 'H')
      return false;
    grid[ny][nx] = '*';
    shower.push({ ny, nx });
    return false;
  };

  auto cur_helper = [](int ny, int nx) {
    char next = grid[ny][nx];
    if (next == 'H')
      return true;
    if (next != '.')
      return false;
    grid[ny][nx] = 'C';
    cur.push({ ny, nx });
    return false;
  };

  while (!cur.empty()) {
    ++ans;

    update(shower, shower_helper);
    if (update(cur, cur_helper)) {
      cout << ans << '\n';
      return 0;
    }
  }

  cout << "FAIL\n";
  return 0;
}