#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string.h>

using namespace std;

int main() {
  int P, N;
  cin >> P >> N;

  vector<int> A(N);
  for (int i = 0; i < N; ++i) cin >> A[i];

  int M = 1e9 + 7;
  long long ans = 0;
  for (int i = 0; i < N; ++i) {
    ans *= P;
    ans += A[i];
    ans %= M;
  }

  cout << ans << '\n';
  return 0;
}