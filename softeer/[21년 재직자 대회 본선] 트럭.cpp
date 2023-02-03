#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string.h>

using namespace std;

bool comp(pair<int, int> a, pair<int, int> b) {
  if (a.first == b.first) return a.second > b.second;
  return a.first < b.first;
}

bool comp2(pair<int, int> a, pair<int, int> b) {
  if (a.first == b.first) return a.second < b.second;
  return a.first < b.first;
}

int main() {
  int N;
  cin >> N;

  map<int, int> SP_map;

  for (int i = 0; i < N; ++i) {
    int a, s, p;
    cin >> a;

    vector<pair<int, int>> SP_i(a);
    for (int j = 0; j < a; ++j)
      cin >> SP_i[j].first >> SP_i[j].second;

    sort(SP_i.begin(), SP_i.end(), comp);

    int prev = 0;
    for (int j = 0; j < a; ++j) {
      if (SP_i[j].second <= prev) continue;
      SP_map[SP_i[j].first] += SP_i[j].second - prev;
      prev = SP_i[j].second;
    }
  }

  vector<pair<int, int>> SP_table(SP_map.begin(), SP_map.end());
  int prev = SP_table[0].second;
  for (int i = 1; i < SP_table.size(); ++i) {
    SP_table[i].second += prev;
    prev = SP_table[i].second;
  }

  int M;
  cin >> M;

  vector<int> Q(M);
  for (int i = 0; i < M; ++i)
    cin >> Q[i];

  for (auto q : Q) {
    int ans = -1;

    int left = 0;
    int right = SP_table.size();

    while (left != right) {
      int m = left + (right - left) / 2;
      if (SP_table[m].second < q) left = m + 1;
      else right = m;
    }

    if (right < SP_table.size())
      ans = SP_table[right].first;

    cout << ans << ' ';
  }

  return 0;
}