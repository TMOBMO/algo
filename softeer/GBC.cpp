#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int N, M;
  cin >> N >> M;

  vector<pair<int, int>> A(N);
  vector<pair<int, int>> B(M);

  for (int i = 0; i < N; ++i) {
    cin >> A[i].first;
    cin >> A[i].second;
    if (i == 0) continue;
    A[i].first += A[i - 1].first;
  }

  for (int i = 0; i < M; ++i) {
    cin >> B[i].first;
    cin >> B[i].second;
    if (i == 0) continue;
    B[i].first += B[i - 1].first;
  }

  vector<pair<int, int>> C;  // for debug
  int a = 0, b = 0, n = 0, m = 0, ans = 0;

  while (a != 100 || b != 100) {
    a = A[n].first;
    b = B[m].first;

    int c1 = min(a, b);
    int c2 = B[m].second - A[n].second;
    C.push_back({ c1, c2 });

    ans = max(ans, c2);

    if (a < b) ++n;
    else if (a > b) ++m;
    else ++n, ++m;
  }

  cout << ans << '\n';
  return 0;
}