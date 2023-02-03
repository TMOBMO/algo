#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string.h>

using namespace std;

int main() {
  int N;
  cin >> N;

  vector<int> A(N);
  vector<int> lis(1), lds(1);  // Longest Increasing Subsequece
  vector<int> toRight(N), toLeft(N);

  for (int i = 0; i < N; ++i)
    cin >> A[i];

  lis[0] = A[0];
  toRight[0] = 1;
  for (int i = 1; i < N; ++i) {
    vector<int>::iterator it = lower_bound(lis.begin(), lis.end(), A[i]);
    if (it == lis.end()) {
      toRight[i] = it - lis.begin() + 1;
      lis.push_back(A[i]);
    }
    else {
      *it = A[i];
      toRight[i] = it - lis.begin() + 1;
    }
  }

  lds[0] = A[N - 1];
  toLeft[N - 1] = 1;
  for (int i = N - 2; i >= 0; --i) {
    auto it = lower_bound(lds.begin(), lds.end(), A[i]);
    if (it == lds.end()) {
      toLeft[i] = it - lds.begin() + 1;
      lds.push_back(A[i]);
    }
    else {
      *it = A[i];
      toLeft[i] = it - lds.begin() + 1;
    }
  }

  int ans = 0;
  for (int i = 0; i < N; ++i)
    ans = max(ans, toRight[i] + toLeft[i] - 1);

  cout << ans << '\n';
  return 0;
}