#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

int N, M;
map<int, vector<pair<int, int>>> connect;
vector<int> dp;
int update;


void shortest(int cur) {
  auto r = connect[cur];

  if (dp[cur] == -1) return;

  for (int i = 0; i < r.size(); ++i) {
    int prev = r[i].first;
    int cost = r[i].second;
    int t = max(dp[cur], cost);

    if (dp[prev] == -1) {
      ++update;
      dp[prev] = t;
    }
    else {
      update += dp[prev] > t;
      dp[prev] = min(dp[prev], t);
    }
  }
}

bool isPrime(long long n) {
  if (n % 2 == 0) return false;
  for (long long i = 2; i < n; ++i) {
    if (i * i > n) break;
    if (n % i == 0) return false;
  }
  return true;
}

long long prime(long long n) {
  while (1) {
    if (isPrime(n)) return n;
    ++n;
  }
  return 0;
}

int main() {
  cin >> N >> M;

  for (int i = 0; i < M; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    connect[a].push_back({ b, c });
    connect[b].push_back({ a, c });
  }

  dp.resize(N + 1, -1);
  dp[N] = 0;

  while (1) {
    int prev = update;
    for (int i = N; i >= 1; --i)
      shortest(i);
    if (update == prev) break;
  }

  cout << prime(dp[1] + 1) << '\n';
  return 0;
}