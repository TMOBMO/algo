#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

vi f(vi& records) {
  int N = records.size();
  vi sorted = records;
  sort(sorted.begin(), sorted.end());

  map<int, int> table;
  int prev = 1001;
  for (int i = 0; i < N; ++i) {
    if (sorted[i] == prev) continue;
    table[sorted[i]] = i + 1;
    prev = sorted[i];
  }

  vi ans;
  for (int i = 0; i < N; ++i) {
    ans.push_back(table[records[i]]);
  }
  return ans;
}

int main() {
  int N;
  cin >> N;

  vvi input = vvi(2, vi(N, 0));

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < N; ++j) {
      cin >> input[0][j];
      input[0][j] = -input[0][j];
      input[1][j] += input[0][j];
    }
    vi ans = f(input[0]);
    for (int a : ans) cout << a << " ";
    cout << '\n';
  }

  vi ans = f(input[1]);
  for (int a : ans) cout << a << " ";
  cout << '\n';

  return 0;
}