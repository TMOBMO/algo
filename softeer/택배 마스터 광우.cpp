#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N, M, K;
vector<int> W;
int ans = 0;


int f(vector<int> w) {
  int result = 0;
  int cur = 0;
  for (int i = 0; i < K; ++i) {
    int m = 0;
    while (1) {
      if (m + w[cur] > M) break;
      m += w[cur++];
      cur %= N;
    }
    result += m;
  }
  return result;
}

void solve(int cur, vector<int>& w, vector<bool>& visit) {
  if (cur == N) {
    ans = min(ans, f(w));
    return;
  }

  for (int i = 0; i < N; ++i) {
    if (visit[i]) continue;
    w[cur] = W[i];
    visit[i] = true;
    solve(cur + 1, w, visit);
    visit[i] = false;
  }
}

int main() {
  cin >> N >> M >> K;
  W.resize(N);

  for (int i = 0; i < N; ++i)
    cin >> W[i];

  ans = 1e9;
  vector<int> w(N);
  vector<bool> visit(N);
  solve(0, w, visit);
  cout << ans << '\n';
  return 0;
}