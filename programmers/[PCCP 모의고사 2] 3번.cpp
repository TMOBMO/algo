#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> menu, vector<int> order, int k) {
  queue<vector<int>> que;
  int start = 0;
  int last = menu[order[0]];
  int last_end = last;
  size_t n = 1;
  que.push({ start, last_end });

  for (int i = 1; i < order.size(); ++i) {
    start = k * i;
    last_end = max(last_end, start) + menu[order[i]];

    while (!que.empty()) {
      if (start < que.front()[1]) break;
      que.pop();
    }
    que.push({ start, last_end });
    n = max(n, que.size());
  }
  return n;
}

int main() {
  //solution({ 5, 12, 30 }, {1, 2, 0, 1}, 10);
  //solution({ 5, 12, 30 }, { 2, 1, 0, 0, 0, 1, 0 }, 10);
  solution({ 5 }, {0, 0, 0, 0, 0}, 5);
}