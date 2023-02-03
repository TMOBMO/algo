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
  vector<int> lis(1);  // Longest Increasing Subsequence

  for (int i = 0; i < N; ++i) {
    cin >> A[i];
  }

  lis[0] = A[0];
  for (int i = 1; i < N; ++i) {
    auto it = lower_bound(lis.begin(), lis.end(), A[i]);
    if (it == lis.end()) lis.push_back(A[i]);
    else *it = A[i];
  }

  int ans = lis.size();

  cout << ans << '\n';
  return 0;
}

//int main() {
//  int N;
//  cin >> N;
//
//  vector<int> A(N);
//  vector<int> dp(N, 1);
//  for (int i = 0; i < N; ++i) {
//    cin >> A[i];
//  }
//
//  int ans = 1;
//  for (int i = 1; i < N; ++i) {
//    for (int j = 0; j < i; ++j) {
//      if (A[j] >= A[i]) continue;
//      dp[i] = max(dp[i], dp[j] + 1);
//    }
//    ans = max(ans, dp[i]);
//  }
//
//  cout << ans << '\n';
//  return 0;
//}