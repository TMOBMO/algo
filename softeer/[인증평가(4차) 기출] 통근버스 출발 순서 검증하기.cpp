#include<iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char** argv)
{
  int N;
  cin >> N;
  vector<int> in(N);
  vector<int> pos(N);
  for (int i = 0; i < N; ++i) {
    cin >> in[i];
    --in[i];
    pos[in[i]] = i;
  }

  long long ans = 0;
  for (int i = 0; i < N - 2; ++i) {
    int cur = in[i];

    vector<int> k_pos;
    for (int k = 0; k < cur; ++k) {
      if (pos[k] < i) continue;
      k_pos.push_back(pos[k]);
    }

    k_pos.push_back(10000);
    sort(k_pos.begin(), k_pos.end());

    for (int j = cur + 1; j < N; ++j) {
      if (pos[j] < i) continue;

      int left = 0;
      int right = k_pos.size() - 1;

      while (left < right) {
        int m = (left + right) / 2;
        if (pos[j] < k_pos[m]) right = m;
        else left = m + 1;
      }

      ans += k_pos.size() - 1 - right;
    }
  }

  cout << ans << '\n';
  return 0;
}