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

bool valid(int y, int x) {
  return 0 <= y && y < N && 0 <= x && x < N;
}

int main() {
  cin >> N;

  vector<string> board(N);
  for (int i = 0; i < N; ++i) {
    cin >> board[i];
  }

  int dir[] = { -1, 0, 1, 0, -1 };
  vi ans;

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (board[i][j] == '0') continue;

      int count = 0;

      queue<pii> que;
      que.push({ i, j });
      board[i][j] = '0';
      ++count;

      while (!que.empty()) {
        auto t = que.front();
        que.pop();

        int cy = t.first;
        int cx = t.second;

        for (int i = 0; i < 4; ++i) {
          int ny = cy + dir[i];
          int nx = cx + dir[i + 1];

          if (!valid(ny, nx)) continue;
          if (board[ny][nx] == '0') continue;

          que.push({ ny,nx });
          board[ny][nx] = '0';
          ++count;
        }
      }

      ans.push_back(count);
    }
  }

  sort(ans.begin(), ans.end());
  cout << ans.size() << '\n';
  for (int i = 0; i < ans.size(); ++i)
    cout << ans[i] << '\n';

  return 0;
}