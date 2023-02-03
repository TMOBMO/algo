#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
  int N;
  cin >> N;

  vector<pair<int, int>> entry(N);
  for (int i = 0; i < N; ++i)
    cin >> entry[i].first >> entry[i].second;

  auto comp = [](pair<int, int> a, pair<int, int> b) {
    if (a.second == b.second) return a.first < b.first;
    return a.second > b.second;
  };

  priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> pq(entry.begin(), entry.end(), comp);
  int ans = 0;
  int prev_end = 0;

  while (!pq.empty()) {
    auto t = pq.top(); pq.pop();
    if (prev_end > t.first) continue;
    prev_end = t.second;
    ++ans;
  }

  cout << ans << '\n';
  return 0;
}