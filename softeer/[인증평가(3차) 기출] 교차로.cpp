#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

#define ID front().first
#define TIME front().second

queue<pair<int, int>> seq[4];
vector<int> answer;
int cur;
const int MAX = 10E8 + 3 * 10E4;

char right(char d) {
  return (d + 3) % 4;
}

bool isThere(char d) {
  if (seq[d].empty()) return false;
  return seq[d].TIME <= cur;
}

bool go(char d) {
  return isThere(d) && !isThere(right(d));
}

bool waiting(char d) {
  return isThere(d) && isThere(right(d));
}

void updateTime() {
  int val = MAX;
  for (int i = 0; i < 4; ++i) {
    if (seq[i].empty()) continue;
    if (seq[i].TIME <= cur) return;

    val = min(seq[i].TIME, val);
  }

  cur = val;
}

int limit(char d) {
  if (seq[right(d)].empty()) return MAX;
  return seq[right(d)].TIME;
}

void each(char d) {
  if (seq[d].TIME >= limit(d)) return;
  if (seq[d].TIME > cur) return;

  answer[seq[d].ID] = cur;
  seq[d].pop();
}

bool progress() {
  updateTime();

  int count = 0;
  bool pre_check[4];
  for (int i = 0; i < 4; ++i) {
    pre_check[i] = go(i);
    count += pre_check[i];
  }

  if (count == 0) return false;

  for (int i = 0; i < 4; ++i) {
    if (!pre_check[i]) continue;
    each(i);
  }

  ++cur;
  return true;
}

void solve() {
  while (1) {
    if (!progress()) return;
  }
}

int main() {
  int n;
  cin >> n;

  answer.resize(n, -1);

  for (int i = 0; i < n; ++i) {
    char dir;
    int t;

    cin >> t >> dir;
    seq[dir - 'A'].push({ i, t });
  }

  solve();

  for (int i = 0; i < n; ++i)
    cout << answer[i] << "\n";
  return 0;
}