#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string.h>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

int N;
int ans;
int board[45][15];
vi history;


bool valid(int cy, int cx, int n) {
  return 0 <= cy && cy < n && 0 <= cx && cx < N;
}

void arrange(int grid[45][15], int depth, map<int, int>& columns) {
  if (depth >= 3) return;

  for (auto t : columns) {
    int cy = t.second;
    int cx = t.first;

    int ny = cy;
    for (int k = cy + 1; k < 3 * N; ++k) {
      if (grid[k][cx] == 0) continue;
      grid[ny++][cx] = grid[k][cx];
      grid[k][cx] = 0;
    }
  }
}

bool isWorst(int grid[45][15], int depth) {
  int dir[] = { 0, 1, 0, -1 };
  int limit = 4 - depth;

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      for (int k = 0; k < 3; ++k) {
        int nx = j + dir[k + 1];

        for (int t = 0; t < limit; ++t) {
          int ny = i + dir[k] + t;
          if (!valid(ny, nx, 3 * N)) continue;
          if (grid[i][j] == grid[ny][nx])
            return false;
        }
      }
    }
  }

  return true;
}

void solve(int grid[45][15], int depth, int result);

void f(bool visit[15][15], int grid[45][15], int cy, int cx, int depth, int result) {
  queue<pii> que;
  que.push({ cy, cx });
  visit[cy][cx] = true;
  int color = grid[cy][cx];
  grid[cy][cx] = 0;
  history[depth - 1] = color;
  map<int, int> columns;
  columns[cx] = cy;

  int count = 1;
  int left = cx, right = cx, top = cy, bottom = cy;

  int dir[] = { -1, 0, 1, 0, -1 };

  while (!que.empty()) {
    auto t = que.front();
    que.pop();

    for (int i = 0; i < 4; ++i) {
      int ny = t.first + dir[i];
      int nx = t.second + dir[i + 1];
      if (!valid(ny, nx, N)) continue;
      if (grid[ny][nx] != color) continue;

      que.push({ ny, nx });
      grid[ny][nx] = 0;
      visit[ny][nx] = true;
      ++count;
      left = min(left, nx);
      right = max(right, nx);
      top = max(top, ny);
      bottom = min(bottom, ny);
      if (!columns.count(nx) || columns[nx] > ny)
        columns[nx] = ny;
    }
  }

  result += count + (right - left + 1) * (top - bottom + 1);

  arrange(grid, depth, columns);

  solve(grid, depth + 1, result);
}

void solve(int grid[45][15], int depth, int result) {
  if (depth >= 4) {
    ans = max(ans, result);
    return;
  }

  if (isWorst(grid, depth)) {
    ans = max(ans, result + (4 - depth) * 2);
    return;
  }

  if (ans >= N * N * 2 * (4 - depth) + result)
    return;

  int next_grid[45][15] = { 0, };
  bool visit[15][15] = { 0, };

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (visit[i][j]) continue;

      memcpy(next_grid, grid, sizeof(next_grid));
      f(visit, next_grid, i, j, depth, result);
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> N;
  history.resize(3);

  for (int i = 3 * N - 1; i >= 0; --i) {
    for (int j = 0; j < N; ++j) {
      cin >> board[i][j];
    }
  }

  // how to pass the worst-case?

  /*if (colors.size() == 3 * N * N) {
    cout << 6 << '\n';
    return 0;
  }*/

  solve(board, 1, 0);
  cout << ans << '\n';
  return 0;
}