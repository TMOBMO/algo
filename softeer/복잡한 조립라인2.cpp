#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

int main() {
  int K, N;
  cin >> K >> N;

  vector<vector<int>> work(N, vector<int>(K));
  vector<int> move(N);

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < K; ++j) {
      cin >> work[i][j];
    }

    if (i != N - 1) cin >> move[i];
  }

  for (int i = 1; i < N; ++i) {
    int prev_min = 0;

    for (int j = 1; j < K; ++j)
      if (work[i - 1][prev_min] > work[i - 1][j]) prev_min = j;

    prev_min = work[i - 1][prev_min];

    for (int j = 0; j < K; ++j) {
      int prev = work[i - 1][j];
      work[i][j] += min(prev, prev_min + move[i - 1]);
    }
  }

  int ans = work[N - 1][0];
  for (int i = 1; i < K; ++i)
    ans = min(ans, work[N - 1][i]);

  cout << ans << '\n';
  return 0;
}