#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int N, K;
  cin >> N >> K;

  vector<int> sum(N + 1);
  for (int i = 1; i <= N; ++i) {
    int t;
    cin >> t;
    sum[i] += t + sum[i - 1];
  }

  for (int i = 0; i < K; ++i) {
    int s, e;
    cin >> s >> e;
    float ans = (sum[e] - sum[s - 1]);
    ans /= (e - s + 1);
    printf("%.2f\n", ans);
  }

  return 0;
}