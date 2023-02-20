#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
  int N, M;
  cin >> N >> M;

  vector<int> W(N + 1);
  for (int i = 1; i <= N; ++i) cin >> W[i];

  vector<int> list(N + 1, 1);
  int ans = N;
  for (int i = 0; i < M; ++i) {
    int a, b;
    cin >> a >> b;

    if (W[a] >= W[b]) {
      ans -= list[b] == 1;
      list[b] = 0;
    }

    if (W[a] <= W[b]) {
      ans -= list[a] == 1;
      list[a] = 0;
    }
  }

  cout << ans << '\n';
  return 0;
}