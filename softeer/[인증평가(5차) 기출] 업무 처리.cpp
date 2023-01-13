#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

using qi = queue<int>;
using vqi = vector<qi>;
using vvqi = vector<vqi>;

int main() {
  int H, K, R;
  cin >> H >> K >> R;

  vqi leaf(1 << H);
  for (int i = 0; i < (1 << H); ++i) {
    for (int j = 0; j < K; ++j) {
      int t;
      cin >> t;
      leaf[i].push(t);
    }
  }

  vvqi node(1 << H, vqi(2));
  int ans = 0;
  vector<int> history;

  for (int r = 1; r <= R; ++r) {
    for (int i = 1; i < (1 << H); ++i) {
      auto& cur = node[i][r % 2];
      if (cur.empty()) continue;

      int t = cur.front();
      cur.pop();

      if (i == 1) {
        ans += t;
        //history.push_back(t);
        continue;
      }

      node[i / 2][(i + 1) % 2].push(t);
    }

    for (int i = 0; i < (1 << H); ++i) {
      if (leaf[i].empty()) break;
      int t = leaf[i].front();
      leaf[i].pop();

      int j = (1 << H) + i;
      node[j / 2][(j + 1) % 2].push(t);
    }
  }

  cout << ans << '\n';
  return 0;
}