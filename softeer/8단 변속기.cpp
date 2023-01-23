#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string.h>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

int main() {
  int prev;
  cin >> prev;

  string ans = "";

  for (int i = 0; i < 7; ++i) {
    int cur;
    cin >> cur;

    if (ans == "mixed") continue;

    if ((cur - prev) * (cur - prev) != 1) ans = "mixed";
    else if (cur - prev == 1) ans = "ascending";
    else if (cur - prev == -1) ans = "descending";

    prev = cur;
  }

  cout << ans << '\n';
  return 0;
}