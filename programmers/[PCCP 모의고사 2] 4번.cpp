#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int dir[] = { -1, 0, 1, 0, -1 };
const int limit = 1e9;
const int jump = 1;
int n, m;

bool valid(int cy, int cx) {
  return 0 <= cy && cy < n && 0 <= cx && cx < m;
}

int solution(int x, int y, vector<vector<int>> hole) {
  n = y, m = x;
  vector<vector<vector<int>>> grid(2, vector<vector<int>>(n, vector<int>(m, limit)));

  for (int i = 0; i < hole.size(); ++i) {
    grid[0][hole[i][1] - 1][hole[i][0] - 1] = -1;
    grid[1][hole[i][1] - 1][hole[i][0] - 1] = -1;
  }

  queue<vector<int>> que;
  que.push({ 0, 0, jump });  // y, x, jump
  grid[0][0][0] = 0;
  grid[1][0][0] = 0;

  while (!que.empty()) {
    auto cur = que.front(); que.pop();
    int cy = cur[0];
    int cx = cur[1];
    int jump = cur[2];

    if (cy == n - 1 && cx == m - 1) return grid[0][n - 1][m - 1];

    for (int i = 0; i < 4; ++i) {
      int ny = cy + dir[i];
      int nx = cx + dir[i + 1];

      if (!valid(ny, nx)) continue;
      if (grid[jump][cy][cx] + 1 < grid[jump][ny][nx]) {
        grid[jump][ny][nx] = grid[jump][cy][cx] + 1;
        que.push({ ny, nx, jump });
      }

      ny += dir[i];
      nx += dir[i + 1];

      if (!jump || !valid(ny, nx)) continue;
      if (grid[jump][cy][cx] + 1 < grid[jump - 1][ny][nx]) {
        grid[jump - 1][ny][nx] = grid[jump][cy][cx] + 1;
        que.push({ ny, nx, jump - 1 });
      }
    }
  }

  return -1;
}

void main() {
  solution(5, 4, { {1, 4}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {3, 3}, {4, 1}, {4, 3}, {5, 3} });
  //solution(4, 4, { {2, 3}, {3, 3} });
}